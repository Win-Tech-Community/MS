//---------------------------------------------------------------------------
//
// file.cpp - This file contains the class functions for File
//
//				The File class simply calls the Windows file functions.
//				It is purely a wrapper.
//
//				The mmFile Class is a wrapper for the Win32 Memory Mapped
//				file functionality.  It is used exactly the same as above class.
//
//	Honor Bound -- FASA Interactive Technologies
//
//	Copyright (c) 1995 FASA Interactive Technologies
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Include files
#include "std.h"
#include <sys/stat.h>

#ifndef FILE_H
#include "file.h"
#endif
#include <io.h>

#include "utilities.h"


// putting the paths here....
char* g_pScenePath = "d:\\media\\";

//-----------------
// Static Variables
unsigned long File::lastError = NO_ERR;
bool		  File::logFileTraffic = FALSE;

File* fileTrafficLog = NULL;
char CDInstallPath[1024];
void EnterWindowMode();
void EnterFullScreenMode();
void __stdcall ExitGameOS();

extern char FileMissingString[];
extern char CDMissingString[];
extern char MissingTitleString[];

#undef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE	-1
//---------------------------------------------------------------------------
void createTrafficLog (void)
{
	if (fileTrafficLog && fileTrafficLog->isOpen())
		return;

	fileTrafficLog = new File;
	fileTrafficLog->create("filetraffic.log");
}

//---------------------------------------------------------------------------
// Global Functions
long fileExists (char* fName)
{
	struct _stat st;
	if (_stat(fName,&st) != -1)
	{
		return 1;
	}

/*	long fastFileHandle = -1;
	FastFile*	fastFile = FastFileFind(fName,fastFileHandle);
	if (fastFile)
		return 2;*/

	return 0;
}

//---------------------------------------------------------------------------
long fileExistsOnCD (char* fName)
{
	//Just add the CD path here and see if its there.
	char bigPath[2048];
	strcpy(bigPath,CDInstallPath);
	strcat(bigPath,fName);

	struct _stat st;
	if (_stat(bigPath,&st) != -1)
	{
		return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------
bool file1OlderThan2 (char* file1, char* file2)
{
	if ((fileExists(file1) == 1) && (fileExists(file2) == 1))
	{
		struct _stat st1, st2;
		_stat(file1,&st1);
		_stat(file2,&st2);
		
		if (st1.st_mtime < st2.st_mtime)
			return true;
	}

	return false;
}


//---------------------------------------------------------------------------
File::File (void)
{
	fileName = NULL;
	fileMode = NOMODE;
	handle = -1;
	length = 0;
	logicalPosition = 0;
	bufferResult = 0;

	parent = NULL;
	parentOffset = 0;
	physicalLength = 0;

	childList = NULL;
	numChildren = 0;

	inRAM = FALSE;
	fileImage = NULL;

//	fastFile = NULL;
}
			
//---------------------------------------------------------------------------
inline void File::setup (void)
{
	logicalPosition = 0;
	
	//----------------------------------------------------------------------
	//This is only called from an open with a filename, not a file pointer.
	// ie. It assumes we are the parent.
	if (isOpen())
		length = fileSize();
	else
		length = 0;

	parent = NULL;
	parentOffset = 0;
	physicalLength = length;
	
	childList = NULL;
	numChildren = 0;
}

//---------------------------------------------------------------------------
File::~File (void)
{
	close();
}

//---------------------------------------------------------------------------
bool File::eof (void)
{
	return (logicalPosition >= getLength());
}

//---------------------------------------------------------------------------
long File::open (const char* fName, FileMode _mode, long numChild)
{
	ASSERT( !isOpen() );
	//-------------------------------------------------------------
	long fNameLength = strlen(fName);
	
	fileName = new char[fNameLength+1];
	ASSERT(fileName != NULL);
		
	strncpy(fileName,fName,fNameLength+1);
	fileMode = _mode;
	_fmode = _O_BINARY;

	_strlwr(fileName);

	if (fileMode == CREATE)
	{
		handle = _creat(fileName,_S_IWRITE);
		if (handle == INVALID_HANDLE_VALUE)
		{
			lastError = errno;
			return lastError;
		}
	}
    else if ( fileMode == MC2_APPEND )
    {
        handle = _open(fileName, _O_APPEND | _O_WRONLY );
        if (handle == INVALID_HANDLE_VALUE)
		{
			lastError = errno;
			return lastError;
		}
    }
	else
	{
		//----------------------------------------------------------------
		//-- First, see if file is in normal place.  Useful for patches!!
		handle = _open(fileName,_O_RDONLY);


        if (handle == INVALID_HANDLE_VALUE)
        {
            char errorStr[255];
            sprintf( errorStr, "couldn't find file %s", fileName );
            DbgPrint( errorStr );
            ASSERT( !errorStr );
 //           TRACE( errorStr );
            return 2;
        }

		//------------------------------------------
		//-- Next, see if file is in fastFile.
		/*if (handle == INVALID_HANDLE_VALUE)
		{
			lastError = errno;

			fastFile = FastFileFind(fileName,fastFileHandle);
			if (!fastFile)
			{
				//Not in main installed directory and not in fastfile.  Look on CD.

				char actualPath[2048];
				strcpy(actualPath,CDInstallPath);
				strcat(actualPath,fileName);
				handle = _open(actualPath,_O_RDONLY);
				if (handle == INVALID_HANDLE_VALUE)
				{
					bool openFailed = false;
					bool alreadyFullScreen = (Environment.fullScreen != 0);
					while (handle == INVALID_HANDLE_VALUE)
					{
						openFailed = true;

						//OK, check to see if the CD is actually present.
						// Do this by checking for tgl.fst on the CD Path.
						// If its there, the CD is present BUT the file is missing.
						// MANY files in MechCommander 2 are LEGALLY missing!
						// Tell it to the art staff.
						char testCDPath[2048];
						strcpy(testCDPath,CDInstallPath);
						strcat(testCDPath,"tgl.fst");

						DWORD findCD = fileExists(testCDPath);
						if (findCD == 1)	//File exists. CD is in drive.  Return 2 to indicate file not found.
							return 2;

						EnterWindowMode();
		
						char data[2048];
						sprintf(data,FileMissingString,fileName,CDMissingString);
						DWORD result1 = MessageBox(NULL,data,MissingTitleString,MB_OKCANCEL | MB_ICONWARNING);
						if (result1 == IDCANCEL)
						{
							ExitGameOS();
							return (2);		//File not found.  Never returns though!
						}
		
						handle = _open(actualPath,_O_RDONLY);
					}
		
					if (openFailed && (Environment.fullScreen == 0) && alreadyFullScreen)
						EnterFullScreenMode();
				}
				else
				{
					if (logFileTraffic && (handle != INVALID_HANDLE_VALUE))
					{
						if (!fileTrafficLog)
						{
							createTrafficLog();
						}

						char msg[300];
						sprintf(msg,"CFHandle  Length: %010d    File: %s",fileSize(),fileName);
						fileTrafficLog->writeLine(msg);
					}

					setup();

					//------------------------------------------------------------
					// NEW FUNCTIONALITY!!!
					// 
					// Each file may have a number of files open as children which
					// use the parent's handle for reads and writes.  This would
					// allow us to open a packet file and read a packet as a fitIni
					// or allow us to write a packet as a fit ini and so forth.
					//
					// It also allows us to use the packet file extensions as tree
					// files to avoid the ten thousand file syndrome.
					//
					// There is now an open which takes a FilePtr and a size.
					maxChildren = numChild;
					childList = (FilePtr *)systemHeap->Malloc(sizeof(FilePtr) * maxChildren);

					if (!childList)
					{
						return(NO_RAM_FOR_CHILD_LIST);
					}

					numChildren = 0;
					for (long i=0;i<(long)maxChildren;i++)
					{
						childList[i] = NULL;
					}	

					return (NO_ERR);
				}
			}

			if (logFileTraffic)
			{
				if (!fileTrafficLog)
				{
					createTrafficLog();
				}
	
				char msg[300];
				sprintf(msg,"FASTF     Length: %010d    File: %s",fileSize(),fileName);
				fileTrafficLog->writeLine(msg);
			}

			//---------------------------------------------------------------------
			//-- FastFiles are all compressed.  Must read in entire chunk into RAM
			//-- Then close fastfile!!!!!
			inRAM = TRUE;

			fileImage = (unsigned char *)malloc(fileSize());
			if (fileImage)
			{
				fastFile->readFast(fastFileHandle,fileImage,fileSize());

				physicalLength = getLength();
				//------------------------------------
				//-- Image is in RAM.  Shut the file.
				//fastFile->closeFast(fastFileHandle);
				//fastFile = NULL;
				//fastFileHandle = -1;

				logicalPosition = 0;
			}

			return NO_ERR;
		}*/
		else
		{
			if (logFileTraffic && (handle != INVALID_HANDLE_VALUE))
			{
				if (!fileTrafficLog)
				{
					createTrafficLog();
				}
	
				char msg[300];
				sprintf(msg,"CFHandle  Length: %010d    File: %s",fileSize(),fileName);
				fileTrafficLog->writeLine(msg);
			}

			setup();
	
			//------------------------------------------------------------
			// NEW FUNCTIONALITY!!!
			// 
			// Each file may have a number of files open as children which
			// use the parent's handle for reads and writes.  This would
			// allow us to open a packet file and read a packet as a fitIni
			// or allow us to write a packet as a fit ini and so forth.
			//
			// It also allows us to use the packet file extensions as tree
			// files to avoid the ten thousand file syndrome.
			//
			// There is now an open which takes a FilePtr and a size.
			maxChildren = numChild;
			childList = new File*[maxChildren];
			
			if (!childList)
			{
				return(NO_RAM_FOR_CHILD_LIST);
			}
		
			numChildren = 0;
			for (long i=0;i<(long)maxChildren;i++)
			{
				childList[i] = NULL;
			}	
	
			return (NO_ERR);
		}
	}
	
	return(NO_ERR);
}
		
//---------------------------------------------------------------------------
long File::open (File* _parent, unsigned long fileSize, long numChild)
{
	if (_parent/* && (_parent->fastFile == NULL)*/)
	{
		parent = _parent;
		if (parent->getFileMode() != READ)
		{
			return(CANT_WRITE_TO_CHILD);
		}
		
		physicalLength = fileSize;
		parentOffset = parent->getLogicalPosition();
		logicalPosition = 0;

		//-------------------------------------------------------------
		fileName = parent->getFilename();
		fileMode = parent->getFileMode();
		
		handle = parent->getFileHandle();
		
		if (logFileTraffic)
		{
			if (!fileTrafficLog)
			{
				createTrafficLog();
			}
		
			char msg[300];
			sprintf(msg,"CHILD     Length: %010d    File: %s",fileSize,_parent->getFilename());
			fileTrafficLog->writeLine(msg);
		}

		long result = parent->addChild(this);
		if (result != NO_ERR)
			return(result);

		//------------------------------------------------------------
		// NEW FUNCTIONALITY!!!
		// 
		// Each file may have a number of files open as children which
		// use the parent's handle for reads and writes.  This would
		// allow us to open a packet file and read a packet as a fitIni
		// or allow us to write a packet as a fit ini and so forth.
		//
		// It also allows us to use the packet file extensions as tree
		// files to avoid the ten thousand file syndrome.
		//
		// There is now an open which takes a File* and a size.
		// 
		// IF a numChild parameter is passed in as -1, we want this file in RAM!!
		// This means NO CHILDREN!!!!!!!!!!!!!
		if (numChild != -1)
		{
			maxChildren = numChild;
			childList = new File*[maxChildren];
			
			ASSERT(childList != NULL);

			numChildren = 0;
			for (long i=0;i<(long)maxChildren;i++)
			{
				childList[i] = NULL;
			}	
		}
		else
		{
			maxChildren = 0;
			inRAM = TRUE;
			unsigned long result = 0;

			fileImage = new BYTE[fileSize];
			if (!fileImage)
				inRAM = FALSE;

/*			if (_parent->getFileClass() == PACKETFILE)
			{
				result = ((PacketFile*)_parent)->readPacket(((PacketFile*)_parent)->getCurrentPacket(),fileImage);
			}
			else*/
			{
				result = _read(handle,fileImage,fileSize);
				if (result != fileSize)
					lastError = errno;
			}
		}
	}
	else
	{
		return(PARENT_NULL);
	}
	
	return(NO_ERR);
}

long File::open(const char* buffer, int bufferLength )
{
	if ( buffer && bufferLength > 0 )
	{	
		fileImage = (unsigned char*)buffer;
		physicalLength = bufferLength;
		logicalPosition = 0;
		fileMode = RDWRITE;
		inRAM = true;
	}
	else// fail on NULL
	{
		return FILE_NOT_OPEN;
	}

	return NO_ERR;


}

//---------------------------------------------------------------------------
long File::create (const char* fName)
{
	return (open(fName,CREATE));
}

long File::createWithCase( char* fName )
{
	ASSERT( !isOpen() );
	//-------------------------------------------------------------
	long fNameLength = strlen(fName);
	
	fileName = new char[fNameLength+1];
	ASSERT(fileName != NULL);
		
	strncpy(fileName,fName,fNameLength+1);
	fileMode = CREATE;
	_fmode = _O_BINARY;

	handle = _creat(fileName,_S_IWRITE);
	if (handle == INVALID_HANDLE_VALUE)
	{
		lastError = errno;
		return lastError;
	}

	return 0;
}
//---------------------------------------------------------------------------
long File::addChild (File* child)
{
	if (maxChildren)
	{
		for (long i=0;i < (long)maxChildren;i++)
		{
			if (childList[i] == NULL)
			{
				childList[i] = child;
				return NO_ERR;
			}
		}
	}

	return(TOO_MANY_CHILDREN);
}

//---------------------------------------------------------------------------
void File::removeChild (File* child)
{
	if (maxChildren)
	{
		if (childList)
		{
			for (long i=0;i < (long)maxChildren;i++)
			{
				if (childList[i] == child)
				{
					childList[i] = NULL;
					break;
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
void File::close (void)
{
	//------------------------------------------------------------------------
	// First, close us if we are the parent.  Otherwise, just NULL the handle
	// DO NOT CALL CLOSE IF WE ARE A CHILD!!
	//
	// The actual stored filename is also in the parent.  Everyone else just has
	// pointer and, as such, only the parent frees the memory.

	bool bFast = false;

	if ((parent == NULL) && (fileName != NULL))
	{
		delete fileName;
	}

	fileName = NULL;
	length = 0;

	if (isOpen())
	{
		if ((parent == NULL) && (handle != NULL) && (-1 != handle))
			_close(handle);
			
		handle = NULL;

/*		if (fastFile)
		{
   			fastFile->closeFast(fastFileHandle);
			bFast = true; // save that it was a fast file
		}

		fastFile = NULL;			//DO NOT DELETE THE FASTFILE!!!!!!!!!!!!!
		fastFileHandle = -1;*/
	}
	
	//---------------------------------------------------------------------
	// Check if we have any children and close them.  This will set their
	// handle to NULL and their filename to NULL.  It will also close any
	// of THEIR children.
	if (maxChildren)
	{
		if (childList)
		{
			for (long i=0;i<(long)maxChildren;i++)
			{
				if (childList[i])
					childList[i]->close();
			}
		}

		if (childList)
			delete childList;
	}
	
	if (parent != NULL)
		parent->removeChild(this);

	childList = NULL;
	numChildren = 0;

	if (inRAM && (bFast || parent)) // don't want to delete memFiles
	{
		if (fileImage)
			free(fileImage);
		fileImage = NULL;
		inRAM = FALSE;
	}
}

//---------------------------------------------------------------------------
void File::deleteFile (void)
{
	//--------------------------------------------------------------
	// Must be the ultimate parent to delete this file.  Close will
	// make sure all of the children close themselves.
	if (isOpen() && (parent == NULL))
		close();
}

long newPosition = 0;
//---------------------------------------------------------------------------
long File::seek (long pos, long from)
{
	switch (from)
	{
		case SEEK_SET:
			if (pos > (long)getLength())
			{
				return READ_PAST_EOF_ERR;
			}
			break;

		case SEEK_END:
			if ((abs(pos) > (long)getLength()) || (pos > 0))
			{
				return READ_PAST_EOF_ERR;
			}
			break;

		case SEEK_CUR:
			if (pos+logicalPosition > getLength())
			{
				return READ_PAST_EOF_ERR;
			}
			break;
	}

	if (inRAM && fileImage)
	{
		if (parent)
		{
			switch (from)
			{
				case SEEK_SET:
					newPosition = pos;
					break;

				case SEEK_END:
					newPosition = getLength()+parentOffset;
					newPosition += pos;
					break;

				case SEEK_CUR:
					newPosition += pos;
					break;
			}
		}
		else
		{
			switch (from)
			{
				case SEEK_SET:
					newPosition = pos;
					break;

				case SEEK_END:
					newPosition = getLength() + pos;
					break;

				case SEEK_CUR:
					newPosition += pos;
					break;
			}
		}

		if (newPosition == -1)
		{
			return (INVALID_SEEK_ERR);
		}

		logicalPosition = newPosition;

	}
//	else if (fastFile)
//	{
//		newPosition = fastFile->seekFast(fastFileHandle,pos,from);
//		logicalPosition = newPosition;
//	}
	else
	{
		if (parent)
		{
			switch (from)
			{
				case SEEK_SET:
					_lseek(handle,pos+parentOffset,SEEK_SET);
					newPosition = pos;
					break;

				case SEEK_END:
					_lseek(handle,getLength()+parentOffset,SEEK_SET);
					_lseek(handle,pos,SEEK_CUR);
					newPosition = getLength() + pos;
					break;

				case SEEK_CUR:
					_lseek(handle,pos,SEEK_CUR);
					newPosition = logicalPosition + pos;
					break;
			}
		}
		else
		{
			newPosition = _lseek(handle,pos,from);
		}

		if (newPosition == -1)
		{
			return (INVALID_SEEK_ERR);
		}

		logicalPosition = newPosition;
	}

	return (NO_ERR);
}

//---------------------------------------------------------------------------
long File::read (unsigned long pos, BYTE* buffer, long length)
{
	long result = 0;

	if (inRAM && fileImage)
	{
		char *readAddress = ((char *)fileImage)+pos;
		memcpy((char *)buffer,readAddress,length);
		return(length);
	}
/*	else if (fastFile)
	{
		if (logicalPosition != pos)
			fastFile->seekFast(fastFileHandle,pos);

		result = fastFile->readFast(fastFileHandle,buffer,length);
	}*/
	else
	{
		if (isOpen())
		{
			if (logicalPosition != pos)
				seek(pos);

			result = _read(handle,buffer,length);
			if (result != length)
				lastError = errno;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
		
	return(result);
}

//---------------------------------------------------------------------------
unsigned char File::readByte (void)
{
	unsigned char value = 0;
	long result = 0;

	if (inRAM && fileImage)
	{
		char *readAddress = (char*)fileImage+logicalPosition;
		memcpy((char *)&value,readAddress,sizeof(value));
		logicalPosition += sizeof(value);
	}
/*	else if (fastFile)
	{
		result = fastFile->readFast(fastFileHandle,(char *)&value,sizeof(value));
		logicalPosition += sizeof(value);
	}*/
	else
	{
		if (isOpen())
		{
			result = _read(handle,(&value),sizeof(value));
			logicalPosition += sizeof(value);
			
			if (result != sizeof(value))
				lastError = errno;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}

	return value;
}

//---------------------------------------------------------------------------
short File::readWord (void)
{
	short value = 0;
	long result =0;

	if (inRAM && fileImage)
	{
		char *readAddress = (char*)fileImage+logicalPosition;
		memcpy((char *)(&value),readAddress,sizeof(value));
		logicalPosition += sizeof(value);
	}
/*	else if (fastFile)
	{
		result = fastFile->readFast(fastFileHandle,(char *)&value,sizeof(value));
		logicalPosition += sizeof(value);
	}*/
	else
	{
		if (isOpen())
		{
			result = _read(handle,(&value),sizeof(value));
			logicalPosition += sizeof(value);
			
			if (result != sizeof(value))
				lastError = errno;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}

	return value;
}

//---------------------------------------------------------------------------
short File::readShort (void)
{
	return (readWord());
}

//---------------------------------------------------------------------------
long File::readLong (void)
{
	long value = 0;
	unsigned long result = 0;

	if (inRAM && fileImage)	
	{
		char *readAddress = (char*)fileImage+logicalPosition;
		memcpy((char *)(&value),readAddress,sizeof(value));
		logicalPosition += sizeof(value);
	}
/*	else if (fastFile)
	{
		result = fastFile->readFast(fastFileHandle,(char *)&value,sizeof(value));
		logicalPosition += sizeof(value);
	}*/
	else
	{
		if (isOpen())
		{
			result = _read(handle,(&value),sizeof(value));
			logicalPosition += sizeof(value);

			if (result != sizeof(value))
				lastError = errno;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	
	return value;
}

bool isNAN(float *pFloat)
{
	/* We're assuming ansi/ieee 754 floating point representation. See http://www.research.microsoft.com/~hollasch/cgindex/coding/ieeefloat.html. */
	BYTE *byteArray = (BYTE *)pFloat;
	if ((0x7f == (0x7f & byteArray[3])) && (0x80 == (0x80 & byteArray[2]))) {
		if (0x80 == (0x80 & byteArray[3])) {
			/* if the mantissa is a 1 followed by all zeros in this case then it is technically
			"Indeterminate" rather than an NaN, but we'll just count it as a NaN here. */
			return true;
		} else {
			return true;
		}
	}
	return false;
}

float File::readFloat( void )
{
	float value = 0;
	unsigned long result = 0;

	if (inRAM && fileImage)	
	{
		char *readAddress = (char*)fileImage+logicalPosition;
		memcpy((char *)(&value),readAddress,sizeof(value));
		logicalPosition += sizeof(value);
	}
/*	else if (fastFile)
	{
		result = fastFile->readFast(fastFileHandle,(char *)&value,sizeof(value));
		logicalPosition += sizeof(value);
	}*/
	else
	{
		if (isOpen())
		{
			result = _read(handle,(&value),sizeof(value));
			logicalPosition += sizeof(value);

			if (result != sizeof(value))
				lastError = errno;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}

	if (isNAN(&value)) {
		ASSERT(false);
		value = 1.0/*arbitrary value that seems safe*/;
	}
	return value;
}

//---------------------------------------------------------------------------
long File::readString (BYTE* buffer)
{
	long last = 0;

	if (isOpen())
	{
		for(;;)
		{
			byte ch = readByte();

			buffer[last] = ch;

			if (ch)
				++last;
			else
				break;
		}
	}
	else
	{
		lastError = FILE_NOT_OPEN;
	}

	return last;
}

//---------------------------------------------------------------------------
long File::readWideString (TCHAR* buffer)
{
	long last = 0;

	if (isOpen())
	{
		for(;;)
		{
			short ch = readShort();

			buffer[last] = ch;

			if (ch)
				++last;
			else
				break;
		}
	}
	else
	{
		lastError = FILE_NOT_OPEN;
	}

	return last;
}


//---------------------------------------------------------------------------
long File::read (BYTE* buffer, long length)
{
	long result = 0;
	
	if (inRAM && fileImage)
	{
		char *readAddress = (char *)fileImage+logicalPosition;
		memcpy((char *)buffer,readAddress,length);
		logicalPosition += length;
		return(length);
	}
/*	else if (fastFile)
	{
		result = fastFile->readFast(fastFileHandle,buffer,length);
		logicalPosition += result;
	}*/
	else
	{
		if (isOpen())
		{
			result = _read(handle,buffer,length);
			if (result != length)
				lastError = errno;
			else
				logicalPosition += result;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	
	return result;
}

//---------------------------------------------------------------------------
/*long File::readRAW (unsigned long * &buffer, UserHeapPtr heap)
{
	long result = 0;
	
/*	if (fastFile && heap && fastFile->isLZCompressed())
	{
		long lzSizeNeeded = fastFile->lzSizeFast(fastFileHandle);
		buffer = new unsigned long[lzSizeNeeded];

		result = fastFile->readFastRAW(fastFileHandle,buffer,lzSizeNeeded);
		logicalPosition += result;
	}
	
	return result;
}*/

//---------------------------------------------------------------------------
long File::readLine (BYTE* buffer, long maxLength)
{
	long i = 0;
	
	if (inRAM && fileImage)
	{
		if (isOpen())
		{
			unsigned char *readAddress = (unsigned char *)fileImage+logicalPosition;

			while ((i<maxLength) && ((i+logicalPosition) < fileSize()) && readAddress[i]!='\r' )
				i++;

			memcpy( buffer, readAddress, i );

			buffer[i++]=0;

			logicalPosition+=i;

			if ( logicalPosition > fileSize() )
				return READ_PAST_EOF_ERR;

			if( readAddress[i]=='\n' )
				logicalPosition+=1;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
/*	else if (fastFile)
	{
		long bytesread;
		bytesread = fastFile->readFast(fastFileHandle,buffer,maxLength);

		if (maxLength > bytesread)
			maxLength = bytesread;

		while ((i<maxLength) && (buffer[i]!='\r'))
			i++;

		buffer[i++]=0;
		logicalPosition += i;

		if( buffer[i]=='\n' )
			logicalPosition+=1;

		fastFile->seekFast(fastFileHandle,logicalPosition);
	}*/
	else
	{
		if (isOpen())
		{
			long bytesread;
			bytesread = _read(handle,buffer,maxLength);
			if( maxLength > bytesread )
				maxLength=bytesread;

			while( i<maxLength && buffer[i]!='\r' )
				i++;

			buffer[i++]=0;

			logicalPosition+=i;

			if( buffer[i]=='\n' )
				logicalPosition+=1;

			seek(logicalPosition);
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	return i;
}

//---------------------------------------------------------------------------
long File::readLineEx (BYTE* buffer, long maxLength)
{
	long i = 0;
	
	if (inRAM && fileImage)
	{
		if (isOpen())
		{
			unsigned char *readAddress = (unsigned char *)fileImage+logicalPosition;

			while( i<maxLength && readAddress[i]!='\n' )
				i++;

			i++;									//Include Newline
			memcpy( buffer, readAddress, i );

			buffer[i++]=0;

			logicalPosition+=(i-1);
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
/*	else if (fastFile)
	{
		long bytesread;
		bytesread = fastFile->readFast(fastFileHandle,buffer,maxLength);

		if (maxLength > bytesread)
			maxLength = bytesread;

		while ((i<maxLength) && (buffer[i]!='\n'))
			i++;

		i++;					//Include Newline
		buffer[i++]=0;
		logicalPosition += (i-1);

		fastFile->seekFast(fastFileHandle,logicalPosition);
	}*/
	else
	{
		if (isOpen())
		{
			long bytesread = _read(handle,buffer,maxLength);
			if( maxLength > bytesread )
				maxLength=bytesread;

			while( i<maxLength && buffer[i]!='\n' )
				i++;

			i++;
			buffer[i++]=0;

			logicalPosition+= (i-1);

			seek(logicalPosition);
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	return i;
}

//---------------------------------------------------------------------------
long File::write (unsigned long pos, BYTE* buffer, long bytes)
{
	unsigned long result = 0;

	if (parent == NULL)	
	{
		if (isOpen())
		{
			if (logicalPosition != pos)
				seek(pos);

			if ( inRAM )
			{
				if ( logicalPosition + bytes > physicalLength )
					return BAD_WRITE_ERR;
				memcpy( fileImage + logicalPosition, buffer, bytes );
				result = bytes;

			}
			else
			{
				result = _write(handle,buffer,bytes);
				if (result != length)
					lastError = errno;
			}
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}
	
	return(result);
}

//---------------------------------------------------------------------------
long File::writeByte (byte value)
{
	long result = 0;

	if (parent == NULL)
	{
		if (isOpen())	
		{
			if ( inRAM )
			{
				if ( logicalPosition + sizeof(byte) > physicalLength )
					return BAD_WRITE_ERR;
				memcpy( fileImage + logicalPosition, &value, sizeof( byte ) );
				result = sizeof( byte );				
			}
			else
				result = _write(handle,(&value),sizeof(value));
			if (result == sizeof(value))
			{
				logicalPosition += sizeof(value);
				result = NO_ERR;
			}
			else
			{
				result = BAD_WRITE_ERR;
			}
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}
	
	return(result);
}

//---------------------------------------------------------------------------
long File::writeWord (short value)
{
	unsigned long result = 0;
	
	if (parent == NULL)
	{
		if (isOpen())
		{
			if ( inRAM )
			{
				if ( logicalPosition + sizeof( short ) > physicalLength )
					return BAD_WRITE_ERR;
				memcpy( fileImage + logicalPosition, &value, sizeof( short ) );
				result = sizeof( value );				
			}
			else
				result = _write(handle,(&value),sizeof(value));

			if (result == sizeof(value))
			{
				logicalPosition += sizeof(value);
				result = NO_ERR;
			}
			else
			{
				result = BAD_WRITE_ERR;
			}
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}

	return(result);
}

//---------------------------------------------------------------------------
long File::writeShort (short value)
{
	long result = writeWord(value);
	return(result);
}

//---------------------------------------------------------------------------
long File::writeLong (long value)
{
	unsigned long result = 0;
	
	if (parent == NULL)
	{
		if (isOpen())
		{
			if ( inRAM )
			{
				if ( logicalPosition + sizeof( value ) > physicalLength )
					return BAD_WRITE_ERR;
				memcpy( fileImage + logicalPosition, &value, sizeof( value ) );
				result = sizeof( value );				
			}
			else
				result = _write(handle,(&value),sizeof(value));

			if (result == sizeof(value))
			{
				logicalPosition += sizeof(value);
				result = NO_ERR;	
			}
			else
			{
				result = BAD_WRITE_ERR;
			}
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}

	return(result);
}

//---------------------------------------------------------------------------
long File::writeFloat (float value)
{
	unsigned long result = 0;

	ASSERT(!isNAN(&value));
	if (parent == NULL)
	{
		if (isOpen())
		{
			if ( inRAM )
			{
				if ( logicalPosition + sizeof( value ) > physicalLength )
					return BAD_WRITE_ERR;
				memcpy( fileImage + logicalPosition, &value, sizeof( value ) );
				result = sizeof( value );				
			}
			else
				result = _write(handle,(&value),sizeof(float));

			if (result == sizeof(float))
			{
				logicalPosition += sizeof(float);
				result = NO_ERR;	
			}
			else
			{
				result = BAD_WRITE_ERR;
			}
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}

	return(result);
}

//---------------------------------------------------------------------------

long File::writeString (char *buffer)
{
	long result = -1;
	
	if (parent == NULL)
	{
		if (isOpen())
		{
			char *ch = buffer;

			for(; *ch; ++ch)
				writeByte((byte)* ch);

            writeByte(*ch);
			
			return ch - buffer;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}
	
	return(result);
}

//---------------------------------------------------------------------------

long File::writeWideString (TCHAR *buffer)
{
	long result = -1;

    if ( !buffer )
        return -1;
	
	if (parent == NULL)
	{
		if (isOpen())
		{
			TCHAR *ch = buffer;

			for(; *ch; ++ch)
				writeShort((short)* ch);

            writeShort(*ch); // need that NULL
			
			return ch - buffer;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}
	
	return(result);
}

//---------------------------------------------------------------------------
long File::writeLine (char *buffer)
{
	long result = -1;
	
	if (parent == NULL)
	{
		if (isOpen())
		{
			char *ch = buffer;

			for(; *ch; ++ch)
				writeByte((byte)* ch);

			writeByte('\r');
			writeByte('\n');
			
			return ch - buffer;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}
	
	return(result);
}

//---------------------------------------------------------------------------
long File::write (BYTE* buffer, long bytes)
{
	long result = 0;
	
	if (parent == NULL)
	{
		if (isOpen())
		{
			if ( inRAM )
			{
				if ( logicalPosition + bytes > physicalLength )
					return BAD_WRITE_ERR;
				memcpy( fileImage + logicalPosition, buffer, bytes );
				result = bytes;
			}
			else
			{
				result = _write(handle,buffer,bytes);
				if (result != bytes)
				{
					lastError = errno;
					return result;
				}
			}

			logicalPosition += result;
		}
		else
		{
			lastError = FILE_NOT_OPEN;
		}
	}
	else
	{
		lastError = CANT_WRITE_TO_CHILD;
	}
	
	return result;
}

//---------------------------------------------------------------------------
bool File::isOpen (void)
{
	return ((handle != NULL && handle != -1) || (fileImage != NULL));
}

//---------------------------------------------------------------------------
char* File::getFilename (void)
{
	return (fileName);
}

//---------------------------------------------------------------------------
long File::getFileMTime (void)
{
	long mTime = 0;

	if (isOpen())
	{
		struct _stat st;
		_fstat(handle,&st);
		mTime = st.st_mtime;

		//Time\Date Stamp is WAY out of line.
		// Return January 1, 1970
		if (mTime == -1)
			mTime = 0;
	}

	return mTime;
}

//---------------------------------------------------------------------------
unsigned long File::getLength (void)
{
/*	if (fastFile && (length == 0))
	{
		length = fastFile->sizeFast(fastFileHandle);
	}
	else*/
    if ((length == 0) && (parent || inRAM))
	{
		length = physicalLength;
	}
	else if (isOpen() && ((length == 0) || (fileMode > READ) && !inRAM))
	{
		/* _fstat() was being used to get the length of the file, but it was wrong. It was
		   not giving the *logical* size, which is what we want. */
		length = _filelength(handle);
	}

	return length;
}

//---------------------------------------------------------------------------
unsigned long File::fileSize (void)
{
	return getLength();
}

//---------------------------------------------------------------------------
unsigned long File::getNumLines (void)
{
	unsigned long currentPos = logicalPosition;
	unsigned long numLines = 0;

	seek(0);
	for (unsigned long i=0;i<getLength();i++)
	{
		unsigned char check1 = readByte();
		if (check1 == '\n')
			numLines++;
	}	
	
	seek(currentPos);

	return numLines;
}

//---------------------------------------------------------------------------
void File::seekEnd (void)
{
	seek(0,SEEK_END);
}

//---------------------------------------------------------------------------
void File::skip (long bytesToSkip)
{
	if (bytesToSkip)
	{
		seek(logicalPosition+bytesToSkip);
	}
}
//---------------------------------------------------------------------------

