/*

Copyright (c) 2000 Microsoft Corporation

Module Name:

    ReadWriteFileGatherScatter.cpp

Abstract:

    

Author:

    Josh Poley (jpoley)

Environment:

    XBox

Revision History:
    04-21-2000  Created

Notes:

*/

#include "stdafx.h"
#include <winioctl.h>
#include "commontest.h"
#include "mutests.h"

static void SerializeTest(HANDLE hLog, char *variation, char* filename, DWORD size);
static void FillBuffer(FILE_SEGMENT_ELEMENT *aSegmentArray, DWORD size);
static BOOL CompareBuffer(FILE_SEGMENT_ELEMENT *aSegmentArray, FILE_SEGMENT_ELEMENT *bSegmentArray, DWORD size);

static FILE_SEGMENT_ELEMENT *rpages;
static FILE_SEGMENT_ELEMENT *wpages;

/*

Routine Description:

    Tests the ReadFileScatter / WriteFileGather APIs

Arguments:

    HANDLE hLog - handle to an XLOG object
    DWORD ThreadID - unique id of the thread - used to keep tests from 
        corrupting the same file

Return Value:

    

*/
DWORD MUTests::ReadWriteFileGatherScatter_Test(HANDLE hLog, DWORD ThreadID)
    {
    /*
    BOOL ReadFileScatter(
      HANDLE hFile,                          // handle to file 
      FILE_SEGMENT_ELEMENT aSegmentArray[ ], // array of buffer pointers
      DWORD nNumberOfBytesToRead,            // number of bytes to read
      LPDWORD lpReserved,                    // reserved; must be NULL
      LPOVERLAPPED lpOverlapped              // OVERLAPPED structure
    );

    BOOL WriteFileGather(
      HANDLE hFile,                          // handle to file
      FILE_SEGMENT_ELEMENT aSegmentArray[ ], // array of buffer pointers
      DWORD nNumberOfBytesToWrite,           // number of bytes to write
      LPDWORD lpReserved,                    // reserved; must be NULL
      LPOVERLAPPED lpOverlapped              // overlapped buffer
    );
    */
    xSetFunctionName(hLog, "ReadFileScatter/WriteFileGather");

    char lpFile1[80]; sprintf(lpFile1, "%ws:\\FSG01_%d.txt", BASE_DRIVE, ThreadID);
    char lpFile2[80]; sprintf(lpFile2, "%ws:\\FSG02_%d.txt", BASE_DRIVE, ThreadID);
    char lpFile3[80]; sprintf(lpFile3, "%ws:\\FSG03_%d.txt", BASE_DRIVE, ThreadID);

    HANDLE hFile = NULL;
    HANDLE hFile1 = NULL;
    HANDLE hFile2 = NULL;

    DWORD size;
    const size_t NUM_PAGES = 4000;
    size_t page;

    // Get the sector size
    char drivestuff[5];
    sprintf(drivestuff, "%s:\\", BASE_DRIVE);
    DWORD bytesPerSector = XGetDiskSectorSize(drivestuff);
    xLog(hLog, XLL_INFO, "BytesPerSector=   %lu", bytesPerSector);


    // Allocate the pages
    rpages = new FILE_SEGMENT_ELEMENT[NUM_PAGES];
    if(!rpages)
        {
        xStartVariation(hLog, "Initializing State");
        xLog(hLog, XLL_BLOCK, "Unable to allocate memory, all tests skipped");
        xEndVariation(hLog);
        DebugPrint("MUTESTS: Unable to allocate memory, all tests skipped\n");
        return -1;
        }
    wpages = new FILE_SEGMENT_ELEMENT[NUM_PAGES];
    if(!wpages)
        {
        delete[] rpages;
        xStartVariation(hLog, "Initializing State");
        xLog(hLog, XLL_BLOCK, "Unable to allocate memory, all tests skipped");
        xEndVariation(hLog);
        DebugPrint("MUTESTS: Unable to allocate memory, all tests skipped\n");
        return -1;
        }
    for(page=0; page<NUM_PAGES; page++)
        {
        rpages[page].Buffer = VirtualAlloc(NULL, PAGESIZE, MEM_COMMIT, PAGE_READWRITE);
        wpages[page].Buffer = VirtualAlloc(NULL, PAGESIZE, MEM_COMMIT, PAGE_READWRITE);
        if(!rpages[page].Buffer || !wpages[page].Buffer)
            {
            for(page=0; page<NUM_PAGES; page++)
                {
                VirtualFree(rpages[page].Buffer, 0, MEM_RELEASE);
                VirtualFree(wpages[page].Buffer, 0, MEM_RELEASE);
                }
            delete[] rpages;
            delete[] wpages;
            xStartVariation(hLog, "Initializing State");
            xLog(hLog, XLL_BLOCK, "Unable to VirtualAlloc memory, all tests skipped");
            xEndVariation(hLog);
            DebugPrint("MUTESTS: Unable to allocate memory, all tests skipped\n");
            return -1;
            }
        }


    DWORD time = GetTickCount();


    //////////////////////////////////////////////////////////////////////////
    // Straight line successes
    //////////////////////////////////////////////////////////////////////////

    // smallest block
    size = 1*bytesPerSector;
    FillBuffer(wpages, size);
    SerializeTest(hLog, "Read/Write 1 sector size", lpFile1, size);

    // next smallest block
    size = 2*bytesPerSector;
    FillBuffer(wpages, size);
    SerializeTest(hLog, "Read/Write 2 sector sizes", lpFile1, size);

    // 1 below standard page size (assuming 512 sector size)
    size = 7*bytesPerSector;
    FillBuffer(wpages, size);
    SerializeTest(hLog, "Read/Write 7 sector sizes", lpFile1, size);

    // page size
    size = PAGESIZE;
    FillBuffer(wpages, size);
    SerializeTest(hLog, "Read/Write PAGESIZE", lpFile1, size);

    // one above
    size = 9*bytesPerSector;
    FillBuffer(wpages, size);
    SerializeTest(hLog, "Read/Write 9 sector sizes", lpFile1, size);

    // unnatural number
    size = 11*bytesPerSector;
    FillBuffer(wpages, size);
    SerializeTest(hLog, "Read/Write 11 sector sizes", lpFile1, size);

    /*
    TESTCASE("Read/Write many sector sizes")
        {
        BUGGED(928, "ASSERTS in OS");
        } ENDTESTCASE;
    */

    // medium file
    size = 1024*bytesPerSector;
    FillBuffer(wpages, size);
    SerializeTest(hLog, "Read/Write 1024 sector sizes", lpFile1, size);

    // big sized file
    size = 1536*bytesPerSector; 
    FillBuffer(wpages, size);
    SerializeTest(hLog, "Read/Write 1536 sector sizes", lpFile1, size);



    //////////////////////////////////////////////////////////////////////////
    // Performance
    //////////////////////////////////////////////////////////////////////////
    TESTCASE("Performance")
        {
        xLog(hLog, XLL_INFO, "Test took %lu milliseconds to run", GetTickCount()-time);
        } ENDTESTCASE;


    // clean up
    for(page=0; page<NUM_PAGES; page++)
        {
        VirtualFree(rpages[page].Buffer, 0, MEM_RELEASE);
        VirtualFree(wpages[page].Buffer, 0, MEM_RELEASE);
        }
    delete[] rpages;
    delete[] wpages;

    return 0;
    }

static void SerializeTest(HANDLE hLog, char *variation, char* filename, DWORD size)
    {
    HANDLE hFile;
    OVERLAPPED overlap = {0, 0, 0, 0, 0};
    DWORD rSize, wSize;
    DWORD numPages = size/PAGESIZE+1;
    DWORD opTime, waitTime;
    DWORD error;

    FILE_SEGMENT_ELEMENT temp = wpages[numPages];
    wpages[numPages].Buffer = NULL;

    TESTCASE(variation)
        {
        //DebugPrint("%s\n", variation);
        hFile = CreateFile(filename, GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, NULL);
        if(hFile == INVALID_HANDLE_VALUE)
            {
            char wbuffer[1024];
            sprintf(wbuffer, "Unable to open file (ec: %ld)", GetLastError());
            BLOCKED(0, wbuffer);
            }

        // write the test data
        opTime = GetTickCount();
        if(WriteFileGather(hFile, wpages, size, NULL, &overlap) == FALSE && ((error=GetLastError()) == ERROR_IO_PENDING))
            TESTPASS(hLog, "WriteFileGather (ec: %ld)", error);
        else
            TESTFAIL(hLog, "WriteFileGather (ec: %ld)", error);
        opTime = GetTickCount()-opTime;

        // wait for the IO to complete
        waitTime = GetTickCount();
        if(GetOverlappedResult(hFile, &overlap, &wSize, (error==ERROR_IO_PENDING?TRUE:FALSE)) == TRUE)
            TESTPASS(hLog, "GetOverlappedResult[%ld] (ec: %ld)", wSize, GetLastError());
        else
            TESTFAIL(hLog, "GetOverlappedResult[%ld] (ec: %ld)", wSize, GetLastError());
        waitTime = GetTickCount()-waitTime;

        if(opTime > 2*waitTime)
            TESTFAIL(hLog, "Operation took longer than 2*wait: %lu, %lu", opTime, waitTime);

        // read the data back
        opTime = GetTickCount();
        if(ReadFileScatter(hFile, rpages, size, NULL, &overlap) == FALSE && ((error=GetLastError()) == ERROR_IO_PENDING))
            TESTPASS(hLog, "ReadFileScatter (ec: %ld)", error);
        else
            TESTFAIL(hLog, "ReadFileScatter (ec: %ld)", error);
        opTime = GetTickCount()-opTime;

        // wait for the IO to complete
        waitTime = GetTickCount();
        if(GetOverlappedResult(hFile, &overlap, &rSize, (error==ERROR_IO_PENDING?TRUE:FALSE)) == TRUE)
            TESTPASS(hLog, "GetOverlappedResult[%ld] (ec: %ld)", rSize, GetLastError());
        else
            TESTFAIL(hLog, "GetOverlappedResult[%ld] (ec: %ld)", rSize, GetLastError());
        waitTime = GetTickCount()-waitTime;

        if(opTime > 2*waitTime)
            TESTFAIL(hLog, "Operation took longer than 2*wait: %lu, %lu", opTime, waitTime);

        // compare the 2 buffers
        if(!(rSize == size && wSize == size))
            TESTFAIL(hLog, "Write Buffer[%d] != Read Buffer[%d]", wSize, rSize);
        else if(CompareBuffer(wpages, rpages, size) == FALSE)
            TESTFAIL(hLog, "Write Buffer[%d] != Read Buffer[%d]", wSize, rSize);
        else
            TESTPASS(hLog, "Write Buffer[%d] == Read Buffer[%d]", wSize, rSize);

        } ENDTESTCASE_CLEAN({ CloseHandle(hFile); DeleteFile(filename); });
    
    wpages[numPages] = temp;
    }


/*

Routine Description:

    Fills an array of buffers with data making sure data between calls is different

Arguments:

    FILE_SEGMENT_ELEMENT *aSegmentArray - array of buffers, each ptr must be 1 PAGESIZE
    DWORD size - total number of bytes to write

Return Value:

    none

*/
static void FillBuffer(FILE_SEGMENT_ELEMENT *aSegmentArray, DWORD size)
    {
    static bool hilo=false; // so we put different data in the buffer each time we use it
    for(DWORD i=0; i<size; i++)
        {

        ((char*)aSegmentArray[i/PAGESIZE].Buffer)[i%PAGESIZE] = (char) (hilo?i:~i);
        }
    hilo = !hilo;
    }

/*

Routine Description:

    Compares two buffer arrays

Arguments:

    FILE_SEGMENT_ELEMENT *aSegmentArray - array of buffers, each ptr must be 1 PAGESIZE
    FILE_SEGMENT_ELEMENT *bSegmentArray - array of buffers, each ptr must be 1 PAGESIZE
    DWORD size - total size of the data

Return Value:

    TRUE if they are ==
    FALSE if they are !=

*/
static BOOL CompareBuffer(FILE_SEGMENT_ELEMENT *aSegmentArray, FILE_SEGMENT_ELEMENT *bSegmentArray, DWORD size)
    {
    DWORD s;
    for(DWORD i=0; i<size; i+=PAGESIZE)
        {
        if(i + PAGESIZE > size) s = size - i;
        else s = PAGESIZE;

        if(memcmp(aSegmentArray[i/PAGESIZE].Buffer, bSegmentArray[i/PAGESIZE].Buffer, s) != 0) return FALSE;
        }

    return TRUE;
    }


/*
    TODO 
        Read() off of DVD (different sector size)
*/
