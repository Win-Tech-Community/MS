# Microsoft Developer Studio Project File - Name="block" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=block - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "block.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "block.mak" CFG="block - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "block - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "block - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "block - Win32 Hybrid" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "block - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /Fd"block.pdb" /c
# ADD CPP /nologo /G6 /MD /W3 /O2 /Ob0 /I "..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /FD /Fd"block.pdb" /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /base:"0x2b260000" /subsystem:windows /dll /machine:I386 /out:"..\..\..\..\maxsdk\plugin\block.dlc" /release

!ELSEIF  "$(CFG)" == "block - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /Fd"block.pdb" /c
# ADD CPP /nologo /G6 /MDd /W3 /Gm /ZI /Od /I "..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FD /Fd"block.pdb" /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /base:"0x2b260000" /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\..\maxsdk\plugin\block.dlc"

!ELSEIF  "$(CFG)" == "block - Win32 Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\block___W"
# PROP BASE Intermediate_Dir ".\block___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Hybrid"
# PROP Intermediate_Dir ".\Hybrid"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"block.h" /Fd"block.pdb" /c
# ADD CPP /nologo /G6 /MD /W3 /Gm /ZI /Od /I "..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FD /Fd"block.pdb" /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\maxsdk\plugin\block.dlc"
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /base:"0x2b260000" /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\..\maxsdk\plugin\block.dlc"

!ENDIF 

# Begin Target

# Name "block - Win32 Release"
# Name "block - Win32 Debug"
# Name "block - Win32 Hybrid"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\block.cpp
# ADD CPP /Yc"block.h"
# End Source File
# Begin Source File

SOURCE=.\block.def
# End Source File
# Begin Source File

SOURCE=.\blockcontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\masterblock.cpp
# End Source File
# Begin Source File

SOURCE=.\slave.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\lib\core.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\lib\expr.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\lib\geom.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\lib\gfx.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\lib\maxutil.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\lib\mesh.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\lib\Paramblk2.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\block.H
# End Source File
# Begin Source File

SOURCE=.\masterblock.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\control.rc
# End Source File
# End Group
# End Target
# End Project
