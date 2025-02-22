# Microsoft Developer Studio Generated NMAKE File, Based on shape1.dsp
!IF "$(CFG)" == ""
CFG=shape1 - Win32 Debug Profiled
!MESSAGE No configuration specified. Defaulting to shape1 - Win32 Debug\
 Profiled.
!ENDIF 

!IF "$(CFG)" != "shape1 - Win32 Release" && "$(CFG)" != "shape1 - Win32 Debug"\
 && "$(CFG)" != "shape1 - Win32 Hybrid" && "$(CFG)" !=\
 "shape1 - Win32 Debug Profiled" && "$(CFG)" !=\
 "shape1 - Win32 Release Profiled"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "shape1.mak" CFG="shape1 - Win32 Debug Profiled"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "shape1 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "shape1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "shape1 - Win32 Hybrid" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "shape1 - Win32 Debug Profiled" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "shape1 - Win32 Release Profiled" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "shape1 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ELSE 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\shape.obj"
	-@erase "$(INTDIR)\shape1.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\shape1.exp"
	-@erase "$(OUTDIR)\shape1.lib"
	-@erase "..\..\..\..\maxsdk\plugin\shape1.dls"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\shape1.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\shape1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\shape1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /release /base:"0x08530000" /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\shape1.pdb" /machine:I386 /def:".\shape1.def"\
 /out:"..\..\..\..\maxsdk\plugin\shape1.dls" /implib:"$(OUTDIR)\shape1.lib" 
DEF_FILE= \
	".\shape1.def"
LINK32_OBJS= \
	"$(INTDIR)\shape.obj" \
	"$(INTDIR)\shape1.res" \
	"..\..\..\lib\core.lib" \
	"..\..\..\lib\geom.lib" \
	"..\..\..\lib\maxutil.lib"

"..\..\..\..\maxsdk\plugin\shape1.dls" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "shape1 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ELSE 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\shape.obj"
	-@erase "$(INTDIR)\shape1.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\shape1.exp"
	-@erase "$(OUTDIR)\shape1.lib"
	-@erase "$(OUTDIR)\shape1.pdb"
	-@erase "..\..\..\..\maxsdk\plugin\shape1.dls"
	-@erase "..\..\..\..\maxsdk\plugin\shape1.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /Zi /Od /I "..\..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\shape1.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\shape1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\shape1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:"0x08530000" /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\shape1.pdb" /debug /machine:I386\
 /def:".\shape1.def" /out:"..\..\..\..\maxsdk\plugin\shape1.dls"\
 /implib:"$(OUTDIR)\shape1.lib" 
DEF_FILE= \
	".\shape1.def"
LINK32_OBJS= \
	"$(INTDIR)\shape.obj" \
	"$(INTDIR)\shape1.res" \
	"..\..\..\lib\core.lib" \
	"..\..\..\lib\geom.lib" \
	"..\..\..\lib\maxutil.lib"

"..\..\..\..\maxsdk\plugin\shape1.dls" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "shape1 - Win32 Hybrid"

OUTDIR=.\Hybrid
INTDIR=.\Hybrid

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ELSE 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\shape.obj"
	-@erase "$(INTDIR)\shape1.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\shape1.exp"
	-@erase "$(OUTDIR)\shape1.lib"
	-@erase "$(OUTDIR)\shape1.pdb"
	-@erase "..\..\..\..\maxsdk\plugin\shape1.dls"
	-@erase "..\..\..\..\maxsdk\plugin\shape1.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /Gm /Zi /Od /I "..\..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\shape1.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Hybrid/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\shape1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\shape1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:"0x08530000" /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\shape1.pdb" /debug /machine:I386\
 /def:".\shape1.def" /out:"..\..\..\..\maxsdk\plugin\shape1.dls"\
 /implib:"$(OUTDIR)\shape1.lib" 
DEF_FILE= \
	".\shape1.def"
LINK32_OBJS= \
	"$(INTDIR)\shape.obj" \
	"$(INTDIR)\shape1.res" \
	"..\..\..\lib\core.lib" \
	"..\..\..\lib\geom.lib" \
	"..\..\..\lib\maxutil.lib"

"..\..\..\..\maxsdk\plugin\shape1.dls" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "shape1 - Win32 Debug Profiled"

OUTDIR=.\DbgProf
INTDIR=.\DbgProf

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ELSE 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\shape.obj"
	-@erase "$(INTDIR)\shape1.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\shape1.exp"
	-@erase "$(OUTDIR)\shape1.lib"
	-@erase "$(OUTDIR)\shape1.pdb"
	-@erase "..\..\..\..\maxsdk\plugin\shape1.dls"
	-@erase "..\..\..\..\maxsdk\plugin\shape1.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /Zi /Od /I "..\..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\shape1.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /Gh /c 
CPP_OBJS=.\DbgProf/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\shape1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\shape1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=..\..\..\..\maxsdk\lib\acap.lib COMCTL32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /base:"0x08530000" /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\shape1.pdb" /debug /machine:I386 /def:".\shape1.def"\
 /out:"..\..\..\..\maxsdk\plugin\shape1.dls" /implib:"$(OUTDIR)\shape1.lib" 
DEF_FILE= \
	".\shape1.def"
LINK32_OBJS= \
	"$(INTDIR)\shape.obj" \
	"$(INTDIR)\shape1.res" \
	"..\..\..\lib\core.lib" \
	"..\..\..\lib\geom.lib" \
	"..\..\..\lib\maxutil.lib"

"..\..\..\..\maxsdk\plugin\shape1.dls" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "shape1 - Win32 Release Profiled"

OUTDIR=.\RelProf
INTDIR=.\RelProf

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ELSE 

ALL : "..\..\..\..\maxsdk\plugin\shape1.dls"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\shape.obj"
	-@erase "$(INTDIR)\shape1.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\shape1.exp"
	-@erase "$(OUTDIR)\shape1.lib"
	-@erase "$(OUTDIR)\shape1.pdb"
	-@erase "..\..\..\..\maxsdk\plugin\shape1.dls"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /Zi /O2 /I "..\..\..\include" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\shape1.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /Gh /c 
CPP_OBJS=.\RelProf/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\shape1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\shape1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=..\..\..\..\maxsdk\lib\acap.lib COMCTL32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /release /base:"0x08530000" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\shape1.pdb" /debug /machine:I386 /def:".\shape1.def"\
 /out:"..\..\..\..\maxsdk\plugin\shape1.dls" /implib:"$(OUTDIR)\shape1.lib" 
DEF_FILE= \
	".\shape1.def"
LINK32_OBJS= \
	"$(INTDIR)\shape.obj" \
	"$(INTDIR)\shape1.res" \
	"..\..\..\lib\core.lib" \
	"..\..\..\lib\geom.lib" \
	"..\..\..\lib\maxutil.lib"

"..\..\..\..\maxsdk\plugin\shape1.dls" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "shape1 - Win32 Release" || "$(CFG)" == "shape1 - Win32 Debug"\
 || "$(CFG)" == "shape1 - Win32 Hybrid" || "$(CFG)" ==\
 "shape1 - Win32 Debug Profiled" || "$(CFG)" ==\
 "shape1 - Win32 Release Profiled"
SOURCE=.\shape.cpp

!IF  "$(CFG)" == "shape1 - Win32 Release"

DEP_CPP_SHAPE=\
	"..\..\..\include\acolor.h"\
	"..\..\..\include\animtbl.h"\
	"..\..\..\include\appio.h"\
	"..\..\..\include\assert1.h"\
	"..\..\..\include\bitarray.h"\
	"..\..\..\include\box2.h"\
	"..\..\..\include\box3.h"\
	"..\..\..\include\buildver.h"\
	"..\..\..\include\captypes.h"\
	"..\..\..\include\channels.h"\
	"..\..\..\include\cmdmode.h"\
	"..\..\..\include\color.h"\
	"..\..\..\include\control.h"\
	"..\..\..\include\coreexp.h"\
	"..\..\..\include\custcont.h"\
	"..\..\..\include\dbgprint.h"\
	"..\..\..\include\dpoint3.h"\
	"..\..\..\include\euler.h"\
	"..\..\..\include\evuser.h"\
	"..\..\..\include\export.h"\
	"..\..\..\include\gencam.h"\
	"..\..\..\include\genhier.h"\
	"..\..\..\include\genlight.h"\
	"..\..\..\include\genshape.h"\
	"..\..\..\include\geom.h"\
	"..\..\..\include\geomlib.h"\
	"..\..\..\include\gfloat.h"\
	"..\..\..\include\gfx.h"\
	"..\..\..\include\gfxlib.h"\
	"..\..\..\include\gutil.h"\
	"..\..\..\include\hitdata.h"\
	"..\..\..\include\hold.h"\
	"..\..\..\include\impapi.h"\
	"..\..\..\include\impexp.h"\
	"..\..\..\include\imtl.h"\
	"..\..\..\include\inode.h"\
	"..\..\..\include\interval.h"\
	"..\..\..\include\ioapi.h"\
	"..\..\..\include\iparamb.h"\
	"..\..\..\include\ipoint2.h"\
	"..\..\..\include\ipoint3.h"\
	"..\..\..\include\lockid.h"\
	"..\..\..\include\log.h"\
	"..\..\..\include\matrix2.h"\
	"..\..\..\include\matrix3.h"\
	"..\..\..\include\max.h"\
	"..\..\..\include\maxapi.h"\
	"..\..\..\include\maxcom.h"\
	"..\..\..\include\maxtess.h"\
	"..\..\..\include\maxtypes.h"\
	"..\..\..\include\mesh.h"\
	"..\..\..\include\meshlib.h"\
	"..\..\..\include\mouseman.h"\
	"..\..\..\include\mtl.h"\
	"..\..\..\include\nametab.h"\
	"..\..\..\include\object.h"\
	"..\..\..\include\objmode.h"\
	"..\..\..\include\omanapi.h"\
	"..\..\..\include\osnap.h"\
	"..\..\..\include\osnapapi.h"\
	"..\..\..\include\osnaphit.h"\
	"..\..\..\include\osnapmk.h"\
	"..\..\..\include\patch.h"\
	"..\..\..\include\patchlib.h"\
	"..\..\..\include\patchobj.h"\
	"..\..\..\include\plugapi.h"\
	"..\..\..\include\plugin.h"\
	"..\..\..\include\point2.h"\
	"..\..\..\include\point3.h"\
	"..\..\..\include\point4.h"\
	"..\..\..\include\polyshp.h"\
	"..\..\..\include\ptrvec.h"\
	"..\..\..\include\quat.h"\
	"..\..\..\include\ref.h"\
	"..\..\..\include\render.h"\
	"..\..\..\include\rtclick.h"\
	"..\..\..\include\sceneapi.h"\
	"..\..\..\include\shape.h"\
	"..\..\..\include\shphier.h"\
	"..\..\..\include\shpsels.h"\
	"..\..\..\include\snap.h"\
	"..\..\..\include\soundobj.h"\
	"..\..\..\include\spline3d.h"\
	"..\..\..\include\splshape.h"\
	"..\..\..\include\stack.h"\
	"..\..\..\include\stack3.h"\
	"..\..\..\include\strbasic.h"\
	"..\..\..\include\strclass.h"\
	"..\..\..\include\tab.h"\
	"..\..\..\include\trig.h"\
	"..\..\..\include\triobj.h"\
	"..\..\..\include\units.h"\
	"..\..\..\include\utilexp.h"\
	"..\..\..\include\utillib.h"\
	"..\..\..\include\vedge.h"\
	"..\..\..\include\winutil.h"\
	".\data.h"\
	

"$(INTDIR)\shape.obj" : $(SOURCE) $(DEP_CPP_SHAPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "shape1 - Win32 Debug"

DEP_CPP_SHAPE=\
	"..\..\..\include\acolor.h"\
	"..\..\..\include\animtbl.h"\
	"..\..\..\include\appio.h"\
	"..\..\..\include\assert1.h"\
	"..\..\..\include\bitarray.h"\
	"..\..\..\include\box2.h"\
	"..\..\..\include\box3.h"\
	"..\..\..\include\buildver.h"\
	"..\..\..\include\captypes.h"\
	"..\..\..\include\channels.h"\
	"..\..\..\include\cmdmode.h"\
	"..\..\..\include\color.h"\
	"..\..\..\include\control.h"\
	"..\..\..\include\coreexp.h"\
	"..\..\..\include\custcont.h"\
	"..\..\..\include\dbgprint.h"\
	"..\..\..\include\dpoint3.h"\
	"..\..\..\include\euler.h"\
	"..\..\..\include\evuser.h"\
	"..\..\..\include\export.h"\
	"..\..\..\include\gencam.h"\
	"..\..\..\include\genhier.h"\
	"..\..\..\include\genlight.h"\
	"..\..\..\include\genshape.h"\
	"..\..\..\include\geom.h"\
	"..\..\..\include\geomlib.h"\
	"..\..\..\include\gfloat.h"\
	"..\..\..\include\gfx.h"\
	"..\..\..\include\gfxlib.h"\
	"..\..\..\include\gutil.h"\
	"..\..\..\include\hitdata.h"\
	"..\..\..\include\hold.h"\
	"..\..\..\include\impapi.h"\
	"..\..\..\include\impexp.h"\
	"..\..\..\include\imtl.h"\
	"..\..\..\include\inode.h"\
	"..\..\..\include\interval.h"\
	"..\..\..\include\ioapi.h"\
	"..\..\..\include\iparamb.h"\
	"..\..\..\include\ipoint2.h"\
	"..\..\..\include\ipoint3.h"\
	"..\..\..\include\lockid.h"\
	"..\..\..\include\log.h"\
	"..\..\..\include\matrix2.h"\
	"..\..\..\include\matrix3.h"\
	"..\..\..\include\max.h"\
	"..\..\..\include\maxapi.h"\
	"..\..\..\include\maxcom.h"\
	"..\..\..\include\maxtess.h"\
	"..\..\..\include\maxtypes.h"\
	"..\..\..\include\mesh.h"\
	"..\..\..\include\meshlib.h"\
	"..\..\..\include\mouseman.h"\
	"..\..\..\include\mtl.h"\
	"..\..\..\include\nametab.h"\
	"..\..\..\include\object.h"\
	"..\..\..\include\objmode.h"\
	"..\..\..\include\omanapi.h"\
	"..\..\..\include\osnap.h"\
	"..\..\..\include\osnapapi.h"\
	"..\..\..\include\osnaphit.h"\
	"..\..\..\include\osnapmk.h"\
	"..\..\..\include\patch.h"\
	"..\..\..\include\patchlib.h"\
	"..\..\..\include\patchobj.h"\
	"..\..\..\include\plugapi.h"\
	"..\..\..\include\plugin.h"\
	"..\..\..\include\point2.h"\
	"..\..\..\include\point3.h"\
	"..\..\..\include\point4.h"\
	"..\..\..\include\polyshp.h"\
	"..\..\..\include\ptrvec.h"\
	"..\..\..\include\quat.h"\
	"..\..\..\include\ref.h"\
	"..\..\..\include\render.h"\
	"..\..\..\include\rtclick.h"\
	"..\..\..\include\sceneapi.h"\
	"..\..\..\include\shape.h"\
	"..\..\..\include\shphier.h"\
	"..\..\..\include\shpsels.h"\
	"..\..\..\include\snap.h"\
	"..\..\..\include\soundobj.h"\
	"..\..\..\include\spline3d.h"\
	"..\..\..\include\splshape.h"\
	"..\..\..\include\stack.h"\
	"..\..\..\include\stack3.h"\
	"..\..\..\include\strbasic.h"\
	"..\..\..\include\strclass.h"\
	"..\..\..\include\tab.h"\
	"..\..\..\include\trig.h"\
	"..\..\..\include\triobj.h"\
	"..\..\..\include\units.h"\
	"..\..\..\include\utilexp.h"\
	"..\..\..\include\utillib.h"\
	"..\..\..\include\vedge.h"\
	"..\..\..\include\winutil.h"\
	".\data.h"\
	

"$(INTDIR)\shape.obj" : $(SOURCE) $(DEP_CPP_SHAPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "shape1 - Win32 Hybrid"

DEP_CPP_SHAPE=\
	"..\..\..\include\acolor.h"\
	"..\..\..\include\animtbl.h"\
	"..\..\..\include\appio.h"\
	"..\..\..\include\assert1.h"\
	"..\..\..\include\bitarray.h"\
	"..\..\..\include\box2.h"\
	"..\..\..\include\box3.h"\
	"..\..\..\include\buildver.h"\
	"..\..\..\include\captypes.h"\
	"..\..\..\include\channels.h"\
	"..\..\..\include\cmdmode.h"\
	"..\..\..\include\color.h"\
	"..\..\..\include\control.h"\
	"..\..\..\include\coreexp.h"\
	"..\..\..\include\custcont.h"\
	"..\..\..\include\dbgprint.h"\
	"..\..\..\include\dpoint3.h"\
	"..\..\..\include\euler.h"\
	"..\..\..\include\evuser.h"\
	"..\..\..\include\export.h"\
	"..\..\..\include\gencam.h"\
	"..\..\..\include\genhier.h"\
	"..\..\..\include\genlight.h"\
	"..\..\..\include\genshape.h"\
	"..\..\..\include\geom.h"\
	"..\..\..\include\geomlib.h"\
	"..\..\..\include\gfloat.h"\
	"..\..\..\include\gfx.h"\
	"..\..\..\include\gfxlib.h"\
	"..\..\..\include\gutil.h"\
	"..\..\..\include\hitdata.h"\
	"..\..\..\include\hold.h"\
	"..\..\..\include\impapi.h"\
	"..\..\..\include\impexp.h"\
	"..\..\..\include\imtl.h"\
	"..\..\..\include\inode.h"\
	"..\..\..\include\interval.h"\
	"..\..\..\include\ioapi.h"\
	"..\..\..\include\iparamb.h"\
	"..\..\..\include\ipoint2.h"\
	"..\..\..\include\ipoint3.h"\
	"..\..\..\include\lockid.h"\
	"..\..\..\include\log.h"\
	"..\..\..\include\matrix2.h"\
	"..\..\..\include\matrix3.h"\
	"..\..\..\include\max.h"\
	"..\..\..\include\maxapi.h"\
	"..\..\..\include\maxcom.h"\
	"..\..\..\include\maxtess.h"\
	"..\..\..\include\maxtypes.h"\
	"..\..\..\include\mesh.h"\
	"..\..\..\include\meshlib.h"\
	"..\..\..\include\mouseman.h"\
	"..\..\..\include\mtl.h"\
	"..\..\..\include\nametab.h"\
	"..\..\..\include\object.h"\
	"..\..\..\include\objmode.h"\
	"..\..\..\include\omanapi.h"\
	"..\..\..\include\osnap.h"\
	"..\..\..\include\osnapapi.h"\
	"..\..\..\include\osnaphit.h"\
	"..\..\..\include\osnapmk.h"\
	"..\..\..\include\patch.h"\
	"..\..\..\include\patchlib.h"\
	"..\..\..\include\patchobj.h"\
	"..\..\..\include\plugapi.h"\
	"..\..\..\include\plugin.h"\
	"..\..\..\include\point2.h"\
	"..\..\..\include\point3.h"\
	"..\..\..\include\point4.h"\
	"..\..\..\include\polyshp.h"\
	"..\..\..\include\ptrvec.h"\
	"..\..\..\include\quat.h"\
	"..\..\..\include\ref.h"\
	"..\..\..\include\render.h"\
	"..\..\..\include\rtclick.h"\
	"..\..\..\include\sceneapi.h"\
	"..\..\..\include\shape.h"\
	"..\..\..\include\shphier.h"\
	"..\..\..\include\shpsels.h"\
	"..\..\..\include\snap.h"\
	"..\..\..\include\soundobj.h"\
	"..\..\..\include\spline3d.h"\
	"..\..\..\include\splshape.h"\
	"..\..\..\include\stack.h"\
	"..\..\..\include\stack3.h"\
	"..\..\..\include\strbasic.h"\
	"..\..\..\include\strclass.h"\
	"..\..\..\include\tab.h"\
	"..\..\..\include\trig.h"\
	"..\..\..\include\triobj.h"\
	"..\..\..\include\units.h"\
	"..\..\..\include\utilexp.h"\
	"..\..\..\include\utillib.h"\
	"..\..\..\include\vedge.h"\
	"..\..\..\include\winutil.h"\
	".\data.h"\
	

"$(INTDIR)\shape.obj" : $(SOURCE) $(DEP_CPP_SHAPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "shape1 - Win32 Debug Profiled"

DEP_CPP_SHAPE=\
	"..\..\..\include\acolor.h"\
	"..\..\..\include\animtbl.h"\
	"..\..\..\include\appio.h"\
	"..\..\..\include\assert1.h"\
	"..\..\..\include\bitarray.h"\
	"..\..\..\include\box2.h"\
	"..\..\..\include\box3.h"\
	"..\..\..\include\buildver.h"\
	"..\..\..\include\captypes.h"\
	"..\..\..\include\channels.h"\
	"..\..\..\include\cmdmode.h"\
	"..\..\..\include\color.h"\
	"..\..\..\include\control.h"\
	"..\..\..\include\coreexp.h"\
	"..\..\..\include\custcont.h"\
	"..\..\..\include\dbgprint.h"\
	"..\..\..\include\dpoint3.h"\
	"..\..\..\include\euler.h"\
	"..\..\..\include\evuser.h"\
	"..\..\..\include\export.h"\
	"..\..\..\include\gencam.h"\
	"..\..\..\include\genhier.h"\
	"..\..\..\include\genlight.h"\
	"..\..\..\include\genshape.h"\
	"..\..\..\include\geom.h"\
	"..\..\..\include\geomlib.h"\
	"..\..\..\include\gfloat.h"\
	"..\..\..\include\gfx.h"\
	"..\..\..\include\gfxlib.h"\
	"..\..\..\include\gutil.h"\
	"..\..\..\include\hitdata.h"\
	"..\..\..\include\hold.h"\
	"..\..\..\include\impapi.h"\
	"..\..\..\include\impexp.h"\
	"..\..\..\include\imtl.h"\
	"..\..\..\include\inode.h"\
	"..\..\..\include\interval.h"\
	"..\..\..\include\ioapi.h"\
	"..\..\..\include\iparamb.h"\
	"..\..\..\include\ipoint2.h"\
	"..\..\..\include\ipoint3.h"\
	"..\..\..\include\lockid.h"\
	"..\..\..\include\log.h"\
	"..\..\..\include\matrix2.h"\
	"..\..\..\include\matrix3.h"\
	"..\..\..\include\max.h"\
	"..\..\..\include\maxapi.h"\
	"..\..\..\include\maxcom.h"\
	"..\..\..\include\maxtess.h"\
	"..\..\..\include\maxtypes.h"\
	"..\..\..\include\mesh.h"\
	"..\..\..\include\meshlib.h"\
	"..\..\..\include\mouseman.h"\
	"..\..\..\include\mtl.h"\
	"..\..\..\include\nametab.h"\
	"..\..\..\include\object.h"\
	"..\..\..\include\objmode.h"\
	"..\..\..\include\omanapi.h"\
	"..\..\..\include\osnap.h"\
	"..\..\..\include\osnapapi.h"\
	"..\..\..\include\osnaphit.h"\
	"..\..\..\include\osnapmk.h"\
	"..\..\..\include\patch.h"\
	"..\..\..\include\patchlib.h"\
	"..\..\..\include\patchobj.h"\
	"..\..\..\include\plugapi.h"\
	"..\..\..\include\plugin.h"\
	"..\..\..\include\point2.h"\
	"..\..\..\include\point3.h"\
	"..\..\..\include\point4.h"\
	"..\..\..\include\polyshp.h"\
	"..\..\..\include\ptrvec.h"\
	"..\..\..\include\quat.h"\
	"..\..\..\include\ref.h"\
	"..\..\..\include\render.h"\
	"..\..\..\include\rtclick.h"\
	"..\..\..\include\sceneapi.h"\
	"..\..\..\include\shape.h"\
	"..\..\..\include\shphier.h"\
	"..\..\..\include\shpsels.h"\
	"..\..\..\include\snap.h"\
	"..\..\..\include\soundobj.h"\
	"..\..\..\include\spline3d.h"\
	"..\..\..\include\splshape.h"\
	"..\..\..\include\stack.h"\
	"..\..\..\include\stack3.h"\
	"..\..\..\include\strbasic.h"\
	"..\..\..\include\strclass.h"\
	"..\..\..\include\tab.h"\
	"..\..\..\include\trig.h"\
	"..\..\..\include\triobj.h"\
	"..\..\..\include\units.h"\
	"..\..\..\include\utilexp.h"\
	"..\..\..\include\utillib.h"\
	"..\..\..\include\vedge.h"\
	"..\..\..\include\winutil.h"\
	".\data.h"\
	

"$(INTDIR)\shape.obj" : $(SOURCE) $(DEP_CPP_SHAPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "shape1 - Win32 Release Profiled"

DEP_CPP_SHAPE=\
	"..\..\..\include\acolor.h"\
	"..\..\..\include\animtbl.h"\
	"..\..\..\include\appio.h"\
	"..\..\..\include\assert1.h"\
	"..\..\..\include\bitarray.h"\
	"..\..\..\include\box2.h"\
	"..\..\..\include\box3.h"\
	"..\..\..\include\buildver.h"\
	"..\..\..\include\captypes.h"\
	"..\..\..\include\channels.h"\
	"..\..\..\include\cmdmode.h"\
	"..\..\..\include\color.h"\
	"..\..\..\include\control.h"\
	"..\..\..\include\coreexp.h"\
	"..\..\..\include\custcont.h"\
	"..\..\..\include\dbgprint.h"\
	"..\..\..\include\dpoint3.h"\
	"..\..\..\include\euler.h"\
	"..\..\..\include\evuser.h"\
	"..\..\..\include\export.h"\
	"..\..\..\include\gencam.h"\
	"..\..\..\include\genhier.h"\
	"..\..\..\include\genlight.h"\
	"..\..\..\include\genshape.h"\
	"..\..\..\include\geom.h"\
	"..\..\..\include\geomlib.h"\
	"..\..\..\include\gfloat.h"\
	"..\..\..\include\gfx.h"\
	"..\..\..\include\gfxlib.h"\
	"..\..\..\include\gutil.h"\
	"..\..\..\include\hitdata.h"\
	"..\..\..\include\hold.h"\
	"..\..\..\include\impapi.h"\
	"..\..\..\include\impexp.h"\
	"..\..\..\include\imtl.h"\
	"..\..\..\include\inode.h"\
	"..\..\..\include\interval.h"\
	"..\..\..\include\ioapi.h"\
	"..\..\..\include\iparamb.h"\
	"..\..\..\include\ipoint2.h"\
	"..\..\..\include\ipoint3.h"\
	"..\..\..\include\lockid.h"\
	"..\..\..\include\log.h"\
	"..\..\..\include\matrix2.h"\
	"..\..\..\include\matrix3.h"\
	"..\..\..\include\max.h"\
	"..\..\..\include\maxapi.h"\
	"..\..\..\include\maxcom.h"\
	"..\..\..\include\maxtess.h"\
	"..\..\..\include\maxtypes.h"\
	"..\..\..\include\mesh.h"\
	"..\..\..\include\meshlib.h"\
	"..\..\..\include\mouseman.h"\
	"..\..\..\include\mtl.h"\
	"..\..\..\include\nametab.h"\
	"..\..\..\include\object.h"\
	"..\..\..\include\objmode.h"\
	"..\..\..\include\omanapi.h"\
	"..\..\..\include\osnap.h"\
	"..\..\..\include\osnapapi.h"\
	"..\..\..\include\osnaphit.h"\
	"..\..\..\include\osnapmk.h"\
	"..\..\..\include\patch.h"\
	"..\..\..\include\patchlib.h"\
	"..\..\..\include\patchobj.h"\
	"..\..\..\include\plugapi.h"\
	"..\..\..\include\plugin.h"\
	"..\..\..\include\point2.h"\
	"..\..\..\include\point3.h"\
	"..\..\..\include\point4.h"\
	"..\..\..\include\polyshp.h"\
	"..\..\..\include\ptrvec.h"\
	"..\..\..\include\quat.h"\
	"..\..\..\include\ref.h"\
	"..\..\..\include\render.h"\
	"..\..\..\include\rtclick.h"\
	"..\..\..\include\sceneapi.h"\
	"..\..\..\include\shape.h"\
	"..\..\..\include\shphier.h"\
	"..\..\..\include\shpsels.h"\
	"..\..\..\include\snap.h"\
	"..\..\..\include\soundobj.h"\
	"..\..\..\include\spline3d.h"\
	"..\..\..\include\splshape.h"\
	"..\..\..\include\stack.h"\
	"..\..\..\include\stack3.h"\
	"..\..\..\include\strbasic.h"\
	"..\..\..\include\strclass.h"\
	"..\..\..\include\tab.h"\
	"..\..\..\include\trig.h"\
	"..\..\..\include\triobj.h"\
	"..\..\..\include\units.h"\
	"..\..\..\include\utilexp.h"\
	"..\..\..\include\utillib.h"\
	"..\..\..\include\vedge.h"\
	"..\..\..\include\winutil.h"\
	".\data.h"\
	

"$(INTDIR)\shape.obj" : $(SOURCE) $(DEP_CPP_SHAPE) "$(INTDIR)"


!ENDIF 

SOURCE=.\shape1.rc
DEP_RSC_SHAPE1=\
	".\toolmask.bmp"\
	".\uitools.bmp"\
	

"$(INTDIR)\shape1.res" : $(SOURCE) $(DEP_RSC_SHAPE1) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

