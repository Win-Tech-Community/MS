# Microsoft Developer Studio Project File - Name="StyleRefStripMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=StyleRefStripMgr - Win32 BoundsChecker
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StyleRefStripMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StyleRefStripMgr.mak" CFG="StyleRefStripMgr - Win32 BoundsChecker"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StyleRefStripMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StyleRefStripMgr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StyleRefStripMgr - Win32 BoundsChecker" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StyleRefStripMgr - Win32 BBT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""$/Jazz/StyleRefStripMgr", UFYAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StyleRefStripMgr - Win32 Debug"

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
# ADD LINK32 JazzCommond.lib DMUSProdGUID.lib DMUSProdGUIDPrivate.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"LIBCD" /libpath:"..\libs\debug"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\StyleRefStripMgr.dll
TargetName=StyleRefStripMgr
InputPath=.\Debug\StyleRefStripMgr.dll
SOURCE="$(InputPath)"

"$(OutDir)\$(TargetName).sym" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if NOT %BUILD_MACHINE%x==YESx regsvr32 /s /c "$(TargetPath)" 
	mapsym -o "$(OutDir)\$(TargetName).sym" "$(OutDir)\$(TargetName).map" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "StyleRefStripMgr - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /Ob2 /I "..\Includes" /I "..\Shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 JazzCommon.lib DMUSProdGUID.lib DMUSProdGUIDPrivate.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"LIBC" /libpath:"..\libs\release"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=.\Release\StyleRefStripMgr.dll
TargetName=StyleRefStripMgr
InputPath=.\Release\StyleRefStripMgr.dll
SOURCE="$(InputPath)"

"$(OutDir)\$(TargetName).sym" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if NOT %BUILD_MACHINE%x==YESx regsvr32 /s /c "$(TargetPath)" 
	mapsym -o "$(OutDir)\$(TargetName).sym" "$(OutDir)\$(TargetName).map" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "StyleRefStripMgr - Win32 BoundsChecker"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "StyleRefStripMgr___Win32_BoundsChecker"
# PROP BASE Intermediate_Dir "StyleRefStripMgr___Win32_BoundsChecker"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "BoundsChecker"
# PROP Intermediate_Dir "BoundsChecker"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Includes" /I "..\Shared" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Includes" /I "..\Shared" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\libs\debug\JazzCommond.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /pdbtype:sept
# ADD LINK32 JazzCommond.lib DMUSProdGUID.lib DMUSProdGUIDPrivate.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /libpath:"..\libs\debug"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\BoundsChecker
TargetPath=.\BoundsChecker\StyleRefStripMgr.dll
TargetName=StyleRefStripMgr
InputPath=.\BoundsChecker\StyleRefStripMgr.dll
SOURCE="$(InputPath)"

"$(OutDir)\$(TargetName).sym" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if NOT %BUILD_MACHINE%x==YESx regsvr32 /s /c "$(TargetPath)" 
	mapsym -o "$(OutDir)\$(TargetName).sym" "$(OutDir)\$(TargetName).map" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "StyleRefStripMgr - Win32 BBT"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "StyleRefStripMgr___Win32_BBT"
# PROP BASE Intermediate_Dir "StyleRefStripMgr___Win32_BBT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BBT"
# PROP Intermediate_Dir "BBT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /O2 /Ob2 /I "..\Includes" /I "..\Shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /Ob2 /I "..\Includes" /I "..\Shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 JazzCommon.lib DMUSProdGUID.lib DMUSProdGUIDPrivate.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"LIBC" /libpath:"..\libs\release"
# ADD LINK32 JazzCommon.lib DMUSProdGUID.lib DMUSProdGUIDPrivate.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"LIBC" /libpath:"..\..\BBTLibs" /libpath:"..\libs\release" /debugtype:cv,fixup /opt:ref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\BBT
TargetPath=.\BBT\StyleRefStripMgr.dll
TargetName=StyleRefStripMgr
InputPath=.\BBT\StyleRefStripMgr.dll
SOURCE="$(InputPath)"

"$(OutDir)\$(TargetName).sym" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if NOT %BUILD_MACHINE%x==YESx regsvr32 /s /c "$(TargetPath)" 
	mapsym -o "$(OutDir)\$(TargetName).sym" "$(OutDir)\$(TargetName).map" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "StyleRefStripMgr - Win32 Debug"
# Name "StyleRefStripMgr - Win32 Release"
# Name "StyleRefStripMgr - Win32 BoundsChecker"
# Name "StyleRefStripMgr - Win32 BBT"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DialogEditSeed.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupBitsPPG.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\GroupBitsPPG.rc

!IF  "$(CFG)" == "StyleRefStripMgr - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StyleRefStripMgr - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StyleRefStripMgr - Win32 BoundsChecker"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StyleRefStripMgr - Win32 BBT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropPageStyleRef.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPageVarSeed.cpp
# End Source File
# Begin Source File

SOURCE=.\PropStyleRef.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\RiffStrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StyleRefIO.cpp
# End Source File
# Begin Source File

SOURCE=.\StyleRefMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\StyleRefStrip.cpp
# End Source File
# Begin Source File

SOURCE=.\StyleRefStripMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\StyleRefStripMgr.def
# End Source File
# Begin Source File

SOURCE=.\StyleRefStripMgr.rc
# End Source File
# Begin Source File

SOURCE=..\Shared\TrackFlagsPPG.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DialogEditSeed.h
# End Source File
# Begin Source File

SOURCE=.\GroupBitsPPG.h
# End Source File
# Begin Source File

SOURCE=..\Shared\GroupBitsPPGresource.h
# End Source File
# Begin Source File

SOURCE=..\Shared\MusicTimeConverter.h
# End Source File
# Begin Source File

SOURCE=.\PropPageMgr.h
# End Source File
# Begin Source File

SOURCE=.\PropPageStyleRef.h
# End Source File
# Begin Source File

SOURCE=.\PropPageVarSeed.h
# End Source File
# Begin Source File

SOURCE=.\PropStyleRef.h
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

SOURCE=.\StyleRefIO.h
# End Source File
# Begin Source File

SOURCE=.\StyleRefMgr.h
# End Source File
# Begin Source File

SOURCE=..\Shared\TrackFlagsPPG.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\StyleRefMgr.rgs
# End Source File
# End Target
# End Project
# Section StyleRefStripMgr : {CDD09F86-E73C-11D0-89AB-00A0C9054129}
# 	2:21:DefaultSinkHeaderFile:keysocx.h
# 	2:16:DefaultSinkClass:CKeysOCX
# End Section
# Section StyleRefStripMgr : {CDD09F84-E73C-11D0-89AB-00A0C9054129}
# 	2:5:Class:CKeysOCX
# 	2:10:HeaderFile:keysocx.h
# 	2:8:ImplFile:keysocx.cpp
# End Section
