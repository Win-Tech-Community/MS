# Microsoft Developer Studio Project File - Name="Timeline" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Timeline - Win32 BoundsChecker
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Timeline.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Timeline.mak" CFG="Timeline - Win32 BoundsChecker"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Timeline - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Timeline - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Timeline - Win32 BoundsChecker" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Timeline - Win32 BBT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""$/Jazz/Timeline", VEYAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Timeline - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\Includes" /I "..\Shared" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 jazzcommond.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"LIBCD" /libpath:"..\libs\debug"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\Timeline.dll
TargetName=Timeline
InputPath=.\Debug\Timeline.dll
SOURCE="$(InputPath)"

"$(OutDir)\$(TargetName).sym" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if NOT %BUILD_MACHINE%x==YESx regsvr32 /s /c "$(TargetPath)" 
	mapsym -o "$(OutDir)\$(TargetName).sym" "$(OutDir)\$(TargetName).map" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Timeline - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\Includes" /I "..\Shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 jazzcommon.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"LIBC" /libpath:"..\libs\release"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Timeline.dll
TargetName=Timeline
InputPath=.\ReleaseMinSize\Timeline.dll
SOURCE="$(InputPath)"

"$(OutDir)\$(TargetName).sym" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if NOT %BUILD_MACHINE%x==YESx regsvr32 /s /c "$(TargetPath)" 
	mapsym -o "$(OutDir)\$(TargetName).sym" "$(OutDir)\$(TargetName).map" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Timeline - Win32 BoundsChecker"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Timeline___Win32_BoundsChecker"
# PROP BASE Intermediate_Dir "Timeline___Win32_BoundsChecker"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "BoundsChecker"
# PROP Intermediate_Dir "BoundsChecker"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\Includes" /I "..\Shared" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fr /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "..\Includes" /I "..\Shared" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jazzcommond.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /pdbtype:sept /libpath:"..\libs\debug"
# ADD LINK32 jazzcommond.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /libpath:"..\libs\debug"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\BoundsChecker
TargetPath=.\BoundsChecker\Timeline.dll
TargetName=Timeline
InputPath=.\BoundsChecker\Timeline.dll
SOURCE="$(InputPath)"

"$(OutDir)\$(TargetName).sym" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if NOT %BUILD_MACHINE%x==YESx regsvr32 /s /c "$(TargetPath)" 
	mapsym -o "$(OutDir)\$(TargetName).sym" "$(OutDir)\$(TargetName).map" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Timeline - Win32 BBT"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Timeline___Win32_BBT"
# PROP BASE Intermediate_Dir "Timeline___Win32_BBT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BBT"
# PROP Intermediate_Dir "BBT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\Includes" /I "..\Shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\Includes" /I "..\Shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jazzcommon.lib ConductorGUID.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"LIBC" /libpath:"..\libs\release"
# ADD LINK32 jazzcommon.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"LIBC" /libpath:"..\libs\BBT" /libpath:"..\..\BBTLibs" /debugtype:cv,fixup /opt:ref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\BBT
TargetPath=.\BBT\Timeline.dll
TargetName=Timeline
InputPath=.\BBT\Timeline.dll
SOURCE="$(InputPath)"

"$(OutDir)\$(TargetName).sym" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if NOT %BUILD_MACHINE%x==YESx regsvr32 /s /c "$(TargetPath)" 
	mapsym -o "$(OutDir)\$(TargetName).sym" "$(OutDir)\$(TargetName).map" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Timeline - Win32 Debug"
# Name "Timeline - Win32 Release MinSize"
# Name "Timeline - Win32 BoundsChecker"
# Name "Timeline - Win32 BBT"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ContextMenuHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\RiffStrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TempoMapMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Timeline.cpp
# End Source File
# Begin Source File

SOURCE=.\Timeline.def
# End Source File
# Begin Source File

SOURCE=.\Timeline.rc

!IF  "$(CFG)" == "Timeline - Win32 Debug"

!ELSEIF  "$(CFG)" == "Timeline - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Timeline - Win32 BoundsChecker"

!ELSEIF  "$(CFG)" == "Timeline - Win32 BBT"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TimelineCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\TimelineDataObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeStripMgr.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ContextMenuHandler.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\Shared\RiffStrm.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TempoMapMgr.h
# End Source File
# Begin Source File

SOURCE=.\TimelineCtl.h
# End Source File
# Begin Source File

SOURCE=.\TimelineDataObject.h
# End Source File
# Begin Source File

SOURCE=.\TimelineDraw.h
# End Source File
# Begin Source File

SOURCE=.\TimeStripMgr.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\musictime.bmp
# End Source File
# Begin Source File

SOURCE=.\musictimedown.bmp
# End Source File
# Begin Source File

SOURCE=.\realtime.bmp
# End Source File
# Begin Source File

SOURCE=.\realtimedown.bmp
# End Source File
# Begin Source File

SOURCE=.\zoomin.bmp
# End Source File
# Begin Source File

SOURCE=.\zoomout.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\IStrip.d
# End Source File
# Begin Source File

SOURCE=.\IStripMgr.d
# End Source File
# Begin Source File

SOURCE=.\ITimelineEdit.d
# End Source File
# Begin Source File

SOURCE=.\TimelineCtl.rgs
# End Source File
# Begin Source File

SOURCE=.\TimeStripMgr.rgs
# End Source File
# End Target
# End Project
