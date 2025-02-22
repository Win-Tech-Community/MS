# Microsoft Developer Studio Project File - Name="TechCertGame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 60000
# ** DO NOT EDIT **

# TARGTYPE "Xbox Application" 0x0b01

CFG=TechCertGame - Xbox Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TechCertGame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TechCertGame.mak" CFG="TechCertGame - Xbox Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TechCertGame - Xbox Release" (based on "Xbox Application")
!MESSAGE "TechCertGame - Xbox Debug" (based on "Xbox Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

!IF  "$(CFG)" == "TechCertGame - Xbox Release"


# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Zvc6 /O2 /D "WIN32" /D "_USE_XGMATH" /D "_XBOX" /D "NDEBUG" /YX /FD /G6 /c
# ADD CPP /nologo /W3 /GX /Zvc6 /O2 /I "..\..\Common\include" /D "WIN32" /D "_USE_XGMATH" /D "_XBOX" /D "NDEBUG" /YX /FD /G6 /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 xapilib.lib d3d8.lib d3dx8.lib xgraphics.lib dsound.lib dmusic.lib xboxkrnl.lib /nologo /incremental:no /machine:I386 /subsystem:xbox  /opt:ref /fixed:no /debugtype:vc6
# ADD LINK32 xapilib.lib d3d8.lib d3dx8.lib xgraphics.lib dsound.lib dmusic.lib xboxkrnl.lib  /nologo /incremental:no /machine:I386 /subsystem:xbox  /opt:ref /fixed:no /debugtype:vc6
XBE=imagebld.exe
# ADD BASE XBE /nologo /stack:0x10000
# ADD XBE /nologo /testid:"0xffff0109" /testname:"TechCertGame" /stack:0x10000 /INITFLAGS:0x00000000 /TITLEIMAGE:titleimage.xbx  /DEFAULTSAVEIMAGE:saveimage.xbx /out:"Release/TechCertGame.xbe"
XBCP=xbecopy.exe
# ADD BASE XBCP /NOLOGO
# ADD XBCP /NOLOGO
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=xbcp -r -y -d -t -f media\*.* $(RemoteDir)\media
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TechCertGame - Xbox Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Zvc6 /Od /D "WIN32" /D "_USE_XGMATH" /D "_XBOX" /D "_DEBUG" /YX /FD /G6 /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Zvc6 /Od /I "..\..\Common\include" /D "WIN32" /D "_USE_XGMATH" /D "_XBOX" /D "_DEBUG" /YX /FD /G6 /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 xapilibd.lib d3d8d.lib d3dx8d.lib xgraphicsd.lib dsoundd.lib dmusicd.lib xboxkrnl.lib /nologo /incremental:no /debug /machine:I386 /subsystem:xbox  /fixed:no /debugtype:vc6
# ADD LINK32 xapilibd.lib d3d8d.lib d3dx8d.lib xgraphicsd.lib dsoundd.lib dmusicd.lib xboxkrnl.lib  /nologo /incremental:no /debug /machine:I386 /subsystem:xbox  /fixed:no /debugtype:vc6
XBE=imagebld.exe
# ADD BASE XBE /nologo /stack:0x10000 /debug
# ADD XBE /nologo /testid:"0xffff0109" /testname:"TechCertGame" /stack:0x10000 /debug /INITFLAGS:0x00000000 /TITLEIMAGE:titleimage.xbx  /DEFAULTSAVEIMAGE:saveimage.xbx /out:"Debug/TechCertGame.xbe"
XBCP=xbecopy.exe
# ADD BASE XBCP /NOLOGO
# ADD XBCP /NOLOGO
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=xbcp -r -y -d -t -f media\*.* $(RemoteDir)\media
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "TechCertGame - Xbox Release"
# Name "TechCertGame - Xbox Debug"
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\src\XBApp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\XBFont.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\XBHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\XBInput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\XBMesh.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\XBResource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\XBUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\XbConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\XbMemUnit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\XbSavedGame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\XbSound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\XbStorageDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\XbStopWatch.cpp
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter "*.rdf"
# Begin Source File

SOURCE=.\font.rdf

!IF  "$(CFG)" == "TechCertGame - Xbox Release"

# Begin Custom Build
ProjDir=.
InputPath=.\font.rdf
InputName=font

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TechCertGame - Xbox Debug"

# Begin Custom Build
ProjDir=.
InputPath=.\font.rdf
InputName=font

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\font12.rdf

!IF  "$(CFG)" == "TechCertGame - Xbox Release"

# Begin Custom Build
ProjDir=.
InputPath=.\font12.rdf
InputName=font12

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TechCertGame - Xbox Debug"

# Begin Custom Build
ProjDir=.
InputPath=.\font12.rdf
InputName=font12

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\font16.rdf

!IF  "$(CFG)" == "TechCertGame - Xbox Release"

# Begin Custom Build
ProjDir=.
InputPath=.\font16.rdf
InputName=font16

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TechCertGame - Xbox Debug"

# Begin Custom Build
ProjDir=.
InputPath=.\font16.rdf
InputName=font16

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\font9.rdf

!IF  "$(CFG)" == "TechCertGame - Xbox Release"

# Begin Custom Build
ProjDir=.
InputPath=.\font9.rdf
InputName=font9

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TechCertGame - Xbox Debug"

# Begin Custom Build
ProjDir=.
InputPath=.\font9.rdf
InputName=font9

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\LoadSaveResource.rdf

!IF  "$(CFG)" == "TechCertGame - Xbox Release"

# Begin Custom Build
ProjDir=.
InputPath=.\LoadSaveResource.rdf
InputName=LoadSaveResource

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TechCertGame - Xbox Debug"

# Begin Custom Build
ProjDir=.
InputPath=.\LoadSaveResource.rdf
InputName=LoadSaveResource

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\MenuResource.rdf

!IF  "$(CFG)" == "TechCertGame - Xbox Release"

# Begin Custom Build
ProjDir=.
InputPath=.\MenuResource.rdf
InputName=MenuResource

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TechCertGame - Xbox Debug"

# Begin Custom Build
ProjDir=.
InputPath=.\MenuResource.rdf
InputName=MenuResource

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\Xboxdings_24.rdf

!IF  "$(CFG)" == "TechCertGame - Xbox Release"

# Begin Custom Build
ProjDir=.
InputPath=.\Xboxdings_24.rdf
InputName=Xboxdings_24

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TechCertGame - Xbox Debug"

# Begin Custom Build
ProjDir=.
InputPath=.\Xboxdings_24.rdf
InputName=Xboxdings_24

BuildCmds= \
    bundler $(InputPath)

"$(ProjDir)\Media\$(InputName).xpr" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# End Source File
# End Group
# Begin Source File

SOURCE=.\App.cpp

# End Source File
# Begin Source File
SOURCE=.\Controller.cpp

# End Source File
# Begin Source File
SOURCE=.\Demo.cpp

# End Source File
# Begin Source File
SOURCE=.\CXFont.cpp

# End Source File
# Begin Source File
SOURCE=.\Splash.cpp

# End Source File
# Begin Source File
SOURCE=.\StartScreen.cpp

# End Source File
# Begin Source File
SOURCE=.\Game.cpp

# End Source File
# Begin Source File
SOURCE=.\File.cpp

# End Source File
# Begin Source File
SOURCE=.\Menu.cpp

# End Source File
# Begin Source File
SOURCE=.\LoadSave.cpp

# End Source File
# Begin Source File
SOURCE=.\MenuOptions.cpp

# End Source File
# Begin Source File
SOURCE=.\HeightField.cpp

# End Source File
# Begin Source File
SOURCE=.\Light.cpp

# End Source File
# Begin Source File
SOURCE=.\Mesh.cpp

# End Source File
# Begin Source File
SOURCE=.\PhysicsObject.cpp

# End Source File
# Begin Source File
SOURCE=.\PhysicsSystem.cpp

# End Source File
# Begin Source File
SOURCE=.\Polyhedron.cpp

# End Source File
# Begin Source File
SOURCE=.\Shader.cpp

# End Source File
# Begin Source File
SOURCE=.\Text.cpp

# End Source File
# Begin Source File
SOURCE=.\Vehicle.cpp

# End Source File
# Begin Source File
SOURCE=.\Globals.cpp

# End Source File
# Begin Source File
SOURCE=.\Math3d.cpp

# End Source File
# Begin Source File
SOURCE=.\MusicManager.cpp

# End Source File
# Begin Source File
SOURCE=.\SoundEffect.cpp

# End Source File
# End Target
# End Project

