# Microsoft Developer Studio Generated NMAKE File, Based on PMAlpha.dsp
!IF "$(CFG)" == ""
CFG=pmalpha - Win32 Release
!MESSAGE No configuration specified. Defaulting to pmalpha - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "pmalpha - Win32 Release" && "$(CFG)" !=\
 "pmalpha - Win32 Debug" && "$(CFG)" != "pmalpha - Win32 Hybrid"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PMAlpha.mak" CFG="pmalpha - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pmalpha - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pmalpha - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pmalpha - Win32 Hybrid" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "pmalpha - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\maxsdk\plugin\alpha.flt"

!ELSE 

ALL : "..\..\..\..\maxsdk\plugin\alpha.flt"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\pmalpha.obj"
	-@erase "$(INTDIR)\pmalpha.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\alpha.exp"
	-@erase "$(OUTDIR)\alpha.lib"
	-@erase "..\..\..\..\maxsdk\plugin\alpha.flt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\PMAlpha.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pmalpha.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PMAlpha.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /release /base:"0x07900000" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\alpha.pdb" /machine:I386 /def:".\pmalpha.def"\
 /out:"..\..\..\..\maxsdk\plugin\alpha.flt" /implib:"$(OUTDIR)\alpha.lib" 
DEF_FILE= \
	".\pmalpha.def"
LINK32_OBJS= \
	"$(INTDIR)\pmalpha.obj" \
	"$(INTDIR)\pmalpha.res" \
	"..\..\..\Lib\BMM.lib" \
	"..\..\..\Lib\core.lib" \
	"..\..\..\Lib\flt.lib" \
	"..\..\..\lib\geom.lib" \
	"..\..\..\Lib\maxutil.lib"

"..\..\..\..\maxsdk\plugin\alpha.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pmalpha - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\maxsdk\plugin\alpha.flt"

!ELSE 

ALL : "..\..\..\..\maxsdk\plugin\alpha.flt"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\pmalpha.obj"
	-@erase "$(INTDIR)\pmalpha.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\alpha.exp"
	-@erase "$(OUTDIR)\alpha.lib"
	-@erase "$(OUTDIR)\alpha.pdb"
	-@erase "..\..\..\..\maxsdk\plugin\alpha.flt"
	-@erase "..\..\..\..\maxsdk\plugin\alpha.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /Zi /Od /I "..\..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\PMAlpha.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pmalpha.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PMAlpha.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /base:"0x07900000" /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\alpha.pdb" /debug /machine:I386 /def:".\pmalpha.def"\
 /out:"..\..\..\..\maxsdk\plugin\alpha.flt" /implib:"$(OUTDIR)\alpha.lib" 
DEF_FILE= \
	".\pmalpha.def"
LINK32_OBJS= \
	"$(INTDIR)\pmalpha.obj" \
	"$(INTDIR)\pmalpha.res" \
	"..\..\..\Lib\BMM.lib" \
	"..\..\..\Lib\core.lib" \
	"..\..\..\Lib\flt.lib" \
	"..\..\..\lib\geom.lib" \
	"..\..\..\Lib\maxutil.lib"

"..\..\..\..\maxsdk\plugin\alpha.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pmalpha - Win32 Hybrid"

OUTDIR=.\Hybrid
INTDIR=.\Hybrid

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\maxsdk\plugin\alpha.flt"

!ELSE 

ALL : "..\..\..\..\maxsdk\plugin\alpha.flt"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\pmalpha.obj"
	-@erase "$(INTDIR)\pmalpha.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\alpha.exp"
	-@erase "$(OUTDIR)\alpha.lib"
	-@erase "$(OUTDIR)\alpha.pdb"
	-@erase "..\..\..\..\maxsdk\plugin\alpha.flt"
	-@erase "..\..\..\..\maxsdk\plugin\alpha.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MD /W3 /Gm /Zi /Od /I "..\..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\PMAlpha.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Hybrid/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pmalpha.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PMAlpha.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /base:"0x07900000" /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\alpha.pdb" /debug /machine:I386 /def:".\pmalpha.def"\
 /out:"..\..\..\..\maxsdk\plugin\alpha.flt" /implib:"$(OUTDIR)\alpha.lib" 
DEF_FILE= \
	".\pmalpha.def"
LINK32_OBJS= \
	"$(INTDIR)\pmalpha.obj" \
	"$(INTDIR)\pmalpha.res" \
	"..\..\..\Lib\BMM.lib" \
	"..\..\..\Lib\core.lib" \
	"..\..\..\Lib\flt.lib" \
	"..\..\..\lib\geom.lib" \
	"..\..\..\Lib\maxutil.lib"

"..\..\..\..\maxsdk\plugin\alpha.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "pmalpha - Win32 Release" || "$(CFG)" ==\
 "pmalpha - Win32 Debug" || "$(CFG)" == "pmalpha - Win32 Hybrid"
SOURCE=.\pmalpha.cpp

!IF  "$(CFG)" == "pmalpha - Win32 Release"

DEP_CPP_PMALP=\
	"..\..\..\include\acolor.h"\
	"..\..\..\include\animtbl.h"\
	"..\..\..\include\appio.h"\
	"..\..\..\include\assert1.h"\
	"..\..\..\include\bitarray.h"\
	"..\..\..\include\bitmap.h"\
	"..\..\..\include\bmmlib.h"\
	"..\..\..\include\box2.h"\
	"..\..\..\include\box3.h"\
	"..\..\..\include\buildver.h"\
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
	"..\..\..\include\filters.h"\
	"..\..\..\include\fltapi.h"\
	"..\..\..\include\fltlib.h"\
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
	"..\..\..\include\linklist.h"\
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
	"..\..\..\include\palutil.h"\
	"..\..\..\include\patch.h"\
	"..\..\..\include\patchlib.h"\
	"..\..\..\include\patchobj.h"\
	"..\..\..\include\plugapi.h"\
	"..\..\..\include\plugin.h"\
	"..\..\..\include\point2.h"\
	"..\..\..\include\point3.h"\
	"..\..\..\include\point4.h"\
	"..\..\..\include\ptrvec.h"\
	"..\..\..\include\quat.h"\
	"..\..\..\include\ref.h"\
	"..\..\..\include\render.h"\
	"..\..\..\include\rtclick.h"\
	"..\..\..\include\sceneapi.h"\
	"..\..\..\include\snap.h"\
	"..\..\..\include\soundobj.h"\
	"..\..\..\include\stack.h"\
	"..\..\..\include\stack3.h"\
	"..\..\..\include\strbasic.h"\
	"..\..\..\include\strclass.h"\
	"..\..\..\include\tab.h"\
	"..\..\..\include\trig.h"\
	"..\..\..\include\triobj.h"\
	"..\..\..\include\tvnode.h"\
	"..\..\..\include\units.h"\
	"..\..\..\include\utilexp.h"\
	"..\..\..\include\utillib.h"\
	"..\..\..\include\vedge.h"\
	"..\..\..\include\winutil.h"\
	".\pmalpha.h"\
	

"$(INTDIR)\pmalpha.obj" : $(SOURCE) $(DEP_CPP_PMALP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmalpha - Win32 Debug"

DEP_CPP_PMALP=\
	"..\..\..\include\acolor.h"\
	"..\..\..\include\animtbl.h"\
	"..\..\..\include\appio.h"\
	"..\..\..\include\assert1.h"\
	"..\..\..\include\bitarray.h"\
	"..\..\..\include\bitmap.h"\
	"..\..\..\include\bmmlib.h"\
	"..\..\..\include\box2.h"\
	"..\..\..\include\box3.h"\
	"..\..\..\include\buildver.h"\
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
	"..\..\..\include\filters.h"\
	"..\..\..\include\fltapi.h"\
	"..\..\..\include\fltlib.h"\
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
	"..\..\..\include\linklist.h"\
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
	"..\..\..\include\palutil.h"\
	"..\..\..\include\patch.h"\
	"..\..\..\include\patchlib.h"\
	"..\..\..\include\patchobj.h"\
	"..\..\..\include\plugapi.h"\
	"..\..\..\include\plugin.h"\
	"..\..\..\include\point2.h"\
	"..\..\..\include\point3.h"\
	"..\..\..\include\point4.h"\
	"..\..\..\include\ptrvec.h"\
	"..\..\..\include\quat.h"\
	"..\..\..\include\ref.h"\
	"..\..\..\include\render.h"\
	"..\..\..\include\rtclick.h"\
	"..\..\..\include\sceneapi.h"\
	"..\..\..\include\snap.h"\
	"..\..\..\include\soundobj.h"\
	"..\..\..\include\stack.h"\
	"..\..\..\include\stack3.h"\
	"..\..\..\include\strbasic.h"\
	"..\..\..\include\strclass.h"\
	"..\..\..\include\tab.h"\
	"..\..\..\include\trig.h"\
	"..\..\..\include\triobj.h"\
	"..\..\..\include\tvnode.h"\
	"..\..\..\include\units.h"\
	"..\..\..\include\utilexp.h"\
	"..\..\..\include\utillib.h"\
	"..\..\..\include\vedge.h"\
	"..\..\..\include\winutil.h"\
	".\pmalpha.h"\
	

"$(INTDIR)\pmalpha.obj" : $(SOURCE) $(DEP_CPP_PMALP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pmalpha - Win32 Hybrid"

DEP_CPP_PMALP=\
	"..\..\..\include\acolor.h"\
	"..\..\..\include\animtbl.h"\
	"..\..\..\include\appio.h"\
	"..\..\..\include\assert1.h"\
	"..\..\..\include\bitarray.h"\
	"..\..\..\include\bitmap.h"\
	"..\..\..\include\bmmlib.h"\
	"..\..\..\include\box2.h"\
	"..\..\..\include\box3.h"\
	"..\..\..\include\buildver.h"\
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
	"..\..\..\include\filters.h"\
	"..\..\..\include\fltapi.h"\
	"..\..\..\include\fltlib.h"\
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
	"..\..\..\include\linklist.h"\
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
	"..\..\..\include\palutil.h"\
	"..\..\..\include\patch.h"\
	"..\..\..\include\patchlib.h"\
	"..\..\..\include\patchobj.h"\
	"..\..\..\include\plugapi.h"\
	"..\..\..\include\plugin.h"\
	"..\..\..\include\point2.h"\
	"..\..\..\include\point3.h"\
	"..\..\..\include\point4.h"\
	"..\..\..\include\ptrvec.h"\
	"..\..\..\include\quat.h"\
	"..\..\..\include\ref.h"\
	"..\..\..\include\render.h"\
	"..\..\..\include\rtclick.h"\
	"..\..\..\include\sceneapi.h"\
	"..\..\..\include\snap.h"\
	"..\..\..\include\soundobj.h"\
	"..\..\..\include\stack.h"\
	"..\..\..\include\stack3.h"\
	"..\..\..\include\strbasic.h"\
	"..\..\..\include\strclass.h"\
	"..\..\..\include\tab.h"\
	"..\..\..\include\trig.h"\
	"..\..\..\include\triobj.h"\
	"..\..\..\include\tvnode.h"\
	"..\..\..\include\units.h"\
	"..\..\..\include\utilexp.h"\
	"..\..\..\include\utillib.h"\
	"..\..\..\include\vedge.h"\
	"..\..\..\include\winutil.h"\
	".\pmalpha.h"\
	

"$(INTDIR)\pmalpha.obj" : $(SOURCE) $(DEP_CPP_PMALP) "$(INTDIR)"


!ENDIF 

SOURCE=.\pmalpha.rc

"$(INTDIR)\pmalpha.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

