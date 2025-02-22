# Microsoft Developer Studio Generated NMAKE File, Based on sunlight.dsp
!IF "$(CFG)" == ""
CFG=sunlight - Win32 Release
!MESSAGE No configuration specified. Defaulting to sunlight - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "sunlight - Win32 Release" && "$(CFG)" !=\
 "sunlight - Win32 Hybrid" && "$(CFG)" != "sunlight - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sunlight.mak" CFG="sunlight - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sunlight - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sunlight - Win32 Hybrid" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sunlight - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sunlight - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\maxsdk\plugin\Sunlight.dlo"

!ELSE 

ALL : "..\..\..\maxsdk\plugin\Sunlight.dlo"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CITYLIST.OBJ"
	-@erase "$(INTDIR)\COMPASS.OBJ"
	-@erase "$(INTDIR)\GEOLOC.OBJ"
	-@erase "$(INTDIR)\sunlight.obj"
	-@erase "$(INTDIR)\sunlight.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Sunlight.exp"
	-@erase "$(OUTDIR)\Sunlight.lib"
	-@erase "..\..\..\maxsdk\plugin\Sunlight.dlo"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\sunlight.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sunlight.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:"0x055C0000" /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\Sunlight.pdb" /machine:I386\
 /def:".\sunlight.def" /out:"..\..\..\maxsdk\plugin\Sunlight.dlo"\
 /implib:"$(OUTDIR)\Sunlight.lib" /release 
DEF_FILE= \
	".\sunlight.def"
LINK32_OBJS= \
	"$(INTDIR)\CITYLIST.OBJ" \
	"$(INTDIR)\COMPASS.OBJ" \
	"$(INTDIR)\GEOLOC.OBJ" \
	"$(INTDIR)\sunlight.obj" \
	"$(INTDIR)\sunlight.res" \
	"..\..\lib\core.lib" \
	"..\..\lib\geom.lib" \
	"..\..\lib\gfx.lib" \
	"..\..\lib\mesh.lib" \
	"..\..\lib\maxutil.lib"

"..\..\..\maxsdk\plugin\Sunlight.dlo" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sunlight - Win32 Hybrid"

OUTDIR=.\Hybrid
INTDIR=.\Hybrid

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\maxsdk\plugin\Sunlight.dlo"

!ELSE 

ALL : "..\..\..\maxsdk\plugin\Sunlight.dlo"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CITYLIST.OBJ"
	-@erase "$(INTDIR)\COMPASS.OBJ"
	-@erase "$(INTDIR)\GEOLOC.OBJ"
	-@erase "$(INTDIR)\sunlight.obj"
	-@erase "$(INTDIR)\sunlight.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Sunlight.exp"
	-@erase "$(OUTDIR)\Sunlight.lib"
	-@erase "$(OUTDIR)\Sunlight.pdb"
	-@erase "..\..\..\maxsdk\plugin\Sunlight.dlo"
	-@erase "..\..\..\maxsdk\plugin\Sunlight.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\sunlight.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Hybrid/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sunlight.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:"0x055C0000" /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\Sunlight.pdb" /debug /machine:I386\
 /def:".\sunlight.def" /out:"..\..\..\maxsdk\plugin\Sunlight.dlo"\
 /implib:"$(OUTDIR)\Sunlight.lib" 
DEF_FILE= \
	".\sunlight.def"
LINK32_OBJS= \
	"$(INTDIR)\CITYLIST.OBJ" \
	"$(INTDIR)\COMPASS.OBJ" \
	"$(INTDIR)\GEOLOC.OBJ" \
	"$(INTDIR)\sunlight.obj" \
	"$(INTDIR)\sunlight.res" \
	"..\..\lib\core.lib" \
	"..\..\lib\geom.lib" \
	"..\..\lib\gfx.lib" \
	"..\..\lib\mesh.lib" \
	"..\..\lib\maxutil.lib"

"..\..\..\maxsdk\plugin\Sunlight.dlo" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sunlight - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\maxsdk\plugin\Sunlight.dlo"

!ELSE 

ALL : "..\..\..\maxsdk\plugin\Sunlight.dlo"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CITYLIST.OBJ"
	-@erase "$(INTDIR)\COMPASS.OBJ"
	-@erase "$(INTDIR)\GEOLOC.OBJ"
	-@erase "$(INTDIR)\sunlight.obj"
	-@erase "$(INTDIR)\sunlight.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Sunlight.exp"
	-@erase "$(OUTDIR)\Sunlight.lib"
	-@erase "$(OUTDIR)\Sunlight.pdb"
	-@erase "..\..\..\maxsdk\plugin\Sunlight.dlo"
	-@erase "..\..\..\maxsdk\plugin\Sunlight.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\sunlight.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sunlight.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:"0x055C0000" /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\Sunlight.pdb" /debug /machine:I386\
 /def:".\sunlight.def" /out:"..\..\..\maxsdk\plugin\Sunlight.dlo"\
 /implib:"$(OUTDIR)\Sunlight.lib" 
DEF_FILE= \
	".\sunlight.def"
LINK32_OBJS= \
	"$(INTDIR)\CITYLIST.OBJ" \
	"$(INTDIR)\COMPASS.OBJ" \
	"$(INTDIR)\GEOLOC.OBJ" \
	"$(INTDIR)\sunlight.obj" \
	"$(INTDIR)\sunlight.res" \
	"..\..\lib\core.lib" \
	"..\..\lib\geom.lib" \
	"..\..\lib\gfx.lib" \
	"..\..\lib\mesh.lib" \
	"..\..\lib\maxutil.lib"

"..\..\..\maxsdk\plugin\Sunlight.dlo" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sunlight.res" /d "NDEBUG" 

!IF "$(CFG)" == "sunlight - Win32 Release" || "$(CFG)" ==\
 "sunlight - Win32 Hybrid" || "$(CFG)" == "sunlight - Win32 Debug"
SOURCE=.\CITYLIST.CPP
DEP_CPP_CITYL=\
	".\citylist.h"\
	

"$(INTDIR)\CITYLIST.OBJ" : $(SOURCE) $(DEP_CPP_CITYL) "$(INTDIR)"


SOURCE=.\COMPASS.CPP

!IF  "$(CFG)" == "sunlight - Win32 Release"

DEP_CPP_COMPA=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\compass.h"\
	".\verts.h"\
	

"$(INTDIR)\COMPASS.OBJ" : $(SOURCE) $(DEP_CPP_COMPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sunlight - Win32 Hybrid"

DEP_CPP_COMPA=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\compass.h"\
	".\verts.h"\
	

"$(INTDIR)\COMPASS.OBJ" : $(SOURCE) $(DEP_CPP_COMPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sunlight - Win32 Debug"

DEP_CPP_COMPA=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\compass.h"\
	".\verts.h"\
	

"$(INTDIR)\COMPASS.OBJ" : $(SOURCE) $(DEP_CPP_COMPA) "$(INTDIR)"


!ENDIF 

SOURCE=.\GEOLOC.CPP

!IF  "$(CFG)" == "sunlight - Win32 Release"

DEP_CPP_GEOLO=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\simpmod.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\citylist.h"\
	

"$(INTDIR)\GEOLOC.OBJ" : $(SOURCE) $(DEP_CPP_GEOLO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sunlight - Win32 Hybrid"

DEP_CPP_GEOLO=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\simpmod.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\citylist.h"\
	

"$(INTDIR)\GEOLOC.OBJ" : $(SOURCE) $(DEP_CPP_GEOLO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sunlight - Win32 Debug"

DEP_CPP_GEOLO=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\simpmod.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\citylist.h"\
	

"$(INTDIR)\GEOLOC.OBJ" : $(SOURCE) $(DEP_CPP_GEOLO) "$(INTDIR)"


!ENDIF 

SOURCE=.\sunlight.cpp

!IF  "$(CFG)" == "sunlight - Win32 Release"

DEP_CPP_SUNLI=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\decomp.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\autovis.H"\
	".\compass.h"\
	".\LIGHT.H"\
	".\sunclass.h"\
	".\suntypes.h"\
	

"$(INTDIR)\sunlight.obj" : $(SOURCE) $(DEP_CPP_SUNLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sunlight - Win32 Hybrid"

DEP_CPP_SUNLI=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\decomp.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\autovis.H"\
	".\compass.h"\
	".\LIGHT.H"\
	".\sunclass.h"\
	".\suntypes.h"\
	

"$(INTDIR)\sunlight.obj" : $(SOURCE) $(DEP_CPP_SUNLI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sunlight - Win32 Debug"

DEP_CPP_SUNLI=\
	"..\..\include\acolor.h"\
	"..\..\include\animtbl.h"\
	"..\..\include\appio.h"\
	"..\..\include\assert1.h"\
	"..\..\include\bitarray.h"\
	"..\..\include\box2.h"\
	"..\..\include\box3.h"\
	"..\..\include\buildver.h"\
	"..\..\include\channels.h"\
	"..\..\include\cmdmode.h"\
	"..\..\include\color.h"\
	"..\..\include\control.h"\
	"..\..\include\coreexp.h"\
	"..\..\include\custcont.h"\
	"..\..\include\dbgprint.h"\
	"..\..\include\decomp.h"\
	"..\..\include\dpoint3.h"\
	"..\..\include\euler.h"\
	"..\..\include\evuser.h"\
	"..\..\include\export.h"\
	"..\..\include\gencam.h"\
	"..\..\include\genhier.h"\
	"..\..\include\genlight.h"\
	"..\..\include\genshape.h"\
	"..\..\include\geom.h"\
	"..\..\include\geomlib.h"\
	"..\..\include\gfloat.h"\
	"..\..\include\gfx.h"\
	"..\..\include\gfxlib.h"\
	"..\..\include\gutil.h"\
	"..\..\include\hitdata.h"\
	"..\..\include\hold.h"\
	"..\..\include\impapi.h"\
	"..\..\include\impexp.h"\
	"..\..\include\imtl.h"\
	"..\..\include\inode.h"\
	"..\..\include\interval.h"\
	"..\..\include\ioapi.h"\
	"..\..\include\iparamb.h"\
	"..\..\include\ipoint2.h"\
	"..\..\include\ipoint3.h"\
	"..\..\include\lockid.h"\
	"..\..\include\log.h"\
	"..\..\include\matrix2.h"\
	"..\..\include\matrix3.h"\
	"..\..\include\Max.h"\
	"..\..\include\maxapi.h"\
	"..\..\include\maxcom.h"\
	"..\..\include\maxtess.h"\
	"..\..\include\maxtypes.h"\
	"..\..\include\mesh.h"\
	"..\..\include\meshlib.h"\
	"..\..\include\mouseman.h"\
	"..\..\include\mtl.h"\
	"..\..\include\namesel.h"\
	"..\..\include\nametab.h"\
	"..\..\include\object.h"\
	"..\..\include\objmode.h"\
	"..\..\include\patch.h"\
	"..\..\include\patchlib.h"\
	"..\..\include\patchobj.h"\
	"..\..\include\plugapi.h"\
	"..\..\include\plugin.h"\
	"..\..\include\point2.h"\
	"..\..\include\point3.h"\
	"..\..\include\point4.h"\
	"..\..\include\ptrvec.h"\
	"..\..\include\quat.h"\
	"..\..\include\ref.h"\
	"..\..\include\render.h"\
	"..\..\include\rtclick.h"\
	"..\..\include\sceneapi.h"\
	"..\..\include\snap.h"\
	"..\..\include\soundobj.h"\
	"..\..\include\stack.h"\
	"..\..\include\stack3.h"\
	"..\..\include\strbasic.h"\
	"..\..\include\strclass.h"\
	"..\..\include\tab.h"\
	"..\..\include\trig.h"\
	"..\..\include\triobj.h"\
	"..\..\include\units.h"\
	"..\..\include\utilexp.h"\
	"..\..\include\utillib.h"\
	"..\..\include\vedge.h"\
	"..\..\include\winutil.h"\
	".\autovis.H"\
	".\compass.h"\
	".\LIGHT.H"\
	".\sunclass.h"\
	".\suntypes.h"\
	

"$(INTDIR)\sunlight.obj" : $(SOURCE) $(DEP_CPP_SUNLI) "$(INTDIR)"


!ENDIF 

SOURCE=.\sunlight.RC

"$(INTDIR)\sunlight.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

