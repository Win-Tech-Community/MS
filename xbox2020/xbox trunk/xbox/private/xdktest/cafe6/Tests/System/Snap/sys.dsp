# Microsoft Developer Studio Project File - Name="sys" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=sys - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sys.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sys.mak" CFG="sys - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sys - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "sys - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "sys - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f sys.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "sys.exe"
# PROP BASE Bsc_Name "sys.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f sys.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "sys.exe"
# PROP Bsc_Name "sys.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "sys - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f sys.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "sys.exe"
# PROP BASE Bsc_Name "sys.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f sys.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "sys.exe"
# PROP Bsc_Name "sys.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "sys - Win32 Release"
# Name "sys - Win32 Debug"

!IF  "$(CFG)" == "sys - Win32 Release"

!ELSEIF  "$(CFG)" == "sys - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\bin\sys.stf
# End Source File
# Begin Source File

SOURCE=.\bin\sysd.stf
# End Source File
# End Target
# End Project
