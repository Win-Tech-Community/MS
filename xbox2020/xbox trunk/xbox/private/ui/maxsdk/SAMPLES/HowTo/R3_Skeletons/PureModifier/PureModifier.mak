# Microsoft Developer Studio Generated NMAKE File, Based on PureModifier.dsp
!IF "$(CFG)" == ""
CFG=PureModifier - Win32 Hybrid
!MESSAGE No configuration specified. Defaulting to PureModifier - Win32 Hybrid.
!ENDIF 

!IF "$(CFG)" != "PureModifier - Win32 Release" && "$(CFG)" != "PureModifier - Win32 Debug" && "$(CFG)" != "PureModifier - Win32 Hybrid"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PureModifier.mak" CFG="PureModifier - Win32 Hybrid"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PureModifier - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PureModifier - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PureModifier - Win32 Hybrid" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "PureModifier - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\..\plugin\PureModifier_skeleton.dlm"


CLEAN :
	-@erase "$(INTDIR)\Plugin.obj"
	-@erase "$(INTDIR)\PureEdit.obj"
	-@erase "$(INTDIR)\PureModifier.obj"
	-@erase "$(INTDIR)\PureModifier.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PureModifier_skeleton.exp"
	-@erase "$(OUTDIR)\PureModifier_skeleton.lib"
	-@erase "..\..\..\..\plugin\PureModifier_skeleton.dlm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /GX /O2 /I "..\..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PUREMODIFIER_EXPORTS" /Fp"$(INTDIR)\PureModifier.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\PureModifier.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PureModifier.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=maxutil.lib paramblk2.lib core.lib geom.lib gfx.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x08A60000" /dll /incremental:no /pdb:"$(OUTDIR)\PureModifier_skeleton.pdb" /machine:I386 /def:".\Plugin.def" /out:"..\..\..\..\plugin\PureModifier_skeleton.dlm" /implib:"$(OUTDIR)\PureModifier_skeleton.lib" /libpath:"..\..\..\..\lib" /release 
DEF_FILE= \
	".\Plugin.def"
LINK32_OBJS= \
	"$(INTDIR)\Plugin.obj" \
	"$(INTDIR)\PureEdit.obj" \
	"$(INTDIR)\PureModifier.obj" \
	"$(INTDIR)\PureModifier.res"

"..\..\..\..\plugin\PureModifier_skeleton.dlm" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PureModifier - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\..\plugin\PureModifier_skeleton.dlm"


CLEAN :
	-@erase "$(INTDIR)\Plugin.obj"
	-@erase "$(INTDIR)\PureEdit.obj"
	-@erase "$(INTDIR)\PureModifier.obj"
	-@erase "$(INTDIR)\PureModifier.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\PureModifier_skeleton.exp"
	-@erase "$(OUTDIR)\PureModifier_skeleton.lib"
	-@erase "$(OUTDIR)\PureModifier_skeleton.pdb"
	-@erase "..\..\..\..\plugin\PureModifier_skeleton.dlm"
	-@erase "..\..\..\..\plugin\PureModifier_skeleton.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PUREMODIFIER_EXPORTS" /Fp"$(INTDIR)\PureModifier.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\PureModifier.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PureModifier.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=maxutil.lib paramblk2.lib core.lib geom.lib gfx.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x08A60000" /dll /incremental:yes /pdb:"$(OUTDIR)\PureModifier_skeleton.pdb" /debug /machine:I386 /def:".\Plugin.def" /out:"..\..\..\..\plugin\PureModifier_skeleton.dlm" /implib:"$(OUTDIR)\PureModifier_skeleton.lib" /pdbtype:sept /libpath:"..\..\..\..\lib" 
DEF_FILE= \
	".\Plugin.def"
LINK32_OBJS= \
	"$(INTDIR)\Plugin.obj" \
	"$(INTDIR)\PureEdit.obj" \
	"$(INTDIR)\PureModifier.obj" \
	"$(INTDIR)\PureModifier.res"

"..\..\..\..\plugin\PureModifier_skeleton.dlm" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PureModifier - Win32 Hybrid"

OUTDIR=.\Hybrid
INTDIR=.\Hybrid

ALL : "..\..\..\..\plugin\PureModifier_skeleton.dlm"


CLEAN :
	-@erase "$(INTDIR)\Plugin.obj"
	-@erase "$(INTDIR)\PureEdit.obj"
	-@erase "$(INTDIR)\PureModifier.obj"
	-@erase "$(INTDIR)\PureModifier.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\PureModifier_skeleton.exp"
	-@erase "$(OUTDIR)\PureModifier_skeleton.lib"
	-@erase "$(OUTDIR)\PureModifier_skeleton.pdb"
	-@erase "..\..\..\..\plugin\PureModifier_skeleton.dlm"
	-@erase "..\..\..\..\plugin\PureModifier_skeleton.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PUREMODIFIER_EXPORTS" /Fp"$(INTDIR)\PureModifier.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\PureModifier.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PureModifier.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=maxutil.lib paramblk2.lib core.lib geom.lib gfx.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x08A60000" /dll /incremental:yes /pdb:"$(OUTDIR)\PureModifier_skeleton.pdb" /debug /machine:I386 /def:".\Plugin.def" /out:"..\..\..\..\plugin\PureModifier_skeleton.dlm" /implib:"$(OUTDIR)\PureModifier_skeleton.lib" /pdbtype:sept /libpath:"..\..\..\..\lib" 
DEF_FILE= \
	".\Plugin.def"
LINK32_OBJS= \
	"$(INTDIR)\Plugin.obj" \
	"$(INTDIR)\PureEdit.obj" \
	"$(INTDIR)\PureModifier.obj" \
	"$(INTDIR)\PureModifier.res"

"..\..\..\..\plugin\PureModifier_skeleton.dlm" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("PureModifier.dep")
!INCLUDE "PureModifier.dep"
!ELSE 
!MESSAGE Warning: cannot find "PureModifier.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PureModifier - Win32 Release" || "$(CFG)" == "PureModifier - Win32 Debug" || "$(CFG)" == "PureModifier - Win32 Hybrid"
SOURCE=.\Plugin.cpp

"$(INTDIR)\Plugin.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PureEdit.cpp

"$(INTDIR)\PureEdit.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PureModifier.cpp

"$(INTDIR)\PureModifier.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PureModifier.rc

"$(INTDIR)\PureModifier.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

