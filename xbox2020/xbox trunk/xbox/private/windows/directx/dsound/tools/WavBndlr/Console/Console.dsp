# Microsoft Developer Studio Project File - Name="Console" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=Console - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Console.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Console.mak" CFG="Console - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Console - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "Console - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Console"
# PROP Scc_LocalPath "."

!IF  "$(CFG)" == "Console - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f Console.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Console.exe"
# PROP BASE Bsc_Name "Console.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "d:\xbox\public\tools\razzle.cmd build -Z"
# PROP Rebuild_Opt "-c"
# PROP Target_File "WavBndlr.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "Console - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Console___Win32_Debug"
# PROP BASE Intermediate_Dir "Console___Win32_Debug"
# PROP BASE Cmd_Line "NMAKE /f Console.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Console.exe"
# PROP BASE Bsc_Name "Console.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Console___Win32_Debug"
# PROP Intermediate_Dir "Console___Win32_Debug"
# PROP Cmd_Line "d:\xbox\public\tools\razzle.cmd build -Z"
# PROP Rebuild_Opt "-c"
# PROP Target_File "WavBndlr.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "Console - Win32 Release"
# Name "Console - Win32 Debug"

!IF  "$(CFG)" == "Console - Win32 Release"

!ELSEIF  "$(CFG)" == "Console - Win32 Debug"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\console.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\sources
# End Source File
# End Target
# End Project
