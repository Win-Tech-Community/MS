# Microsoft Developer Studio Project File - Name="DMStyle" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DMStyle - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dmstyle.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dmstyle.mak" CFG="DMStyle - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DMStyle - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DMStyle - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "dmstyle"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DMStyle - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gz /MT /W3 /GR /GX /O2 /I "..\shared" /I "..\..\..\..\public\sdk\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\VERINFO" /d "NDEBUG" /d "WINNT"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "DMStyle - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gz /MTd /W3 /ZI /Od /I "..\shared" /I "..\..\..\..\public\sdk\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "DBG" /D DMUSIC_INTERNAL=1 /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\VERINFO" /d "_DEBUG" /d "WINNT"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\dmstyle.dll
InputPath=.\Debug\dmstyle.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "DMStyle - Win32 Release"
# Name "DMStyle - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\audtrk.cpp
# End Source File
# Begin Source File

SOURCE=.\chordtrk.cpp
# End Source File
# Begin Source File

SOURCE=.\cmmdtrk.cpp
# End Source File
# Begin Source File

SOURCE=.\debug.cpp
# End Source File
# Begin Source File

SOURCE=.\dmsect.cpp
# End Source File
# Begin Source File

SOURCE=.\dmstydll.cpp
# End Source File
# Begin Source File

SOURCE=.\dmstyle.cpp
# End Source File
# Begin Source File

SOURCE=.\dmstyle.def
# End Source File
# Begin Source File

SOURCE=.\dmstyle.rc
# End Source File
# Begin Source File

SOURCE=.\dmstyle2.cpp
# End Source File
# Begin Source File

SOURCE=.\FileIO.cpp
# End Source File
# Begin Source File

SOURCE=.\filter.cpp
# End Source File
# Begin Source File

SOURCE=.\MGenTrk.cpp
# End Source File
# Begin Source File

SOURCE=.\MotifTrk.cpp
# End Source File
# Begin Source File

SOURCE=.\mutetrk.cpp
# End Source File
# Begin Source File

SOURCE=..\shared\oledll.cpp
# End Source File
# Begin Source File

SOURCE=.\ptrntrk.cpp
# End Source File
# Begin Source File

SOURCE=.\sources
# End Source File
# Begin Source File

SOURCE=.\Str.cpp
# End Source File
# Begin Source File

SOURCE=.\styletrk.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\aariff.h
# End Source File
# Begin Source File

SOURCE=.\audtrk.h
# End Source File
# Begin Source File

SOURCE=.\chordtrk.h
# End Source File
# Begin Source File

SOURCE=.\cmmdtrk.h
# End Source File
# Begin Source File

SOURCE=.\debug.h
# End Source File
# Begin Source File

SOURCE=..\dmband\dmbndtrk.h
# End Source File
# Begin Source File

SOURCE=.\dmsect.h
# End Source File
# Begin Source File

SOURCE=.\dmstyle.h
# End Source File
# Begin Source File

SOURCE=.\dmstylep.h
# End Source File
# Begin Source File

SOURCE=.\iostru.h
# End Source File
# Begin Source File

SOURCE=.\motiftrk.h
# End Source File
# Begin Source File

SOURCE=.\mutetrk.h
# End Source File
# Begin Source File

SOURCE=..\shared\oledll.h
# End Source File
# Begin Source File

SOURCE=.\ptrntrk.h
# End Source File
# Begin Source File

SOURCE=.\score.h
# End Source File
# Begin Source File

SOURCE=.\sjdefs.h
# End Source File
# Begin Source File

SOURCE=.\str.h
# End Source File
# Begin Source File

SOURCE=.\styletrk.h
# End Source File
# Begin Source File

SOURCE=.\timesig.h
# End Source File
# Begin Source File

SOURCE=.\tlist.h
# End Source File
# Begin Source File

SOURCE=..\shared\validp.h
# End Source File
# End Group
# End Target
# End Project
