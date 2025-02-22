# InfoView DLL build
#
# Usage:
#
# nmake /f InfoView.mk [all]             Build the DLL
# nmake /f InfoView.mk ssync             Ssync the files needed to build this DLL
# nmake /f InfoView.mk slmout            Check out the files that are built by this makefile
# nmake /f InfoView.mk slmin             Check in the files that are built by this makefile
# nmake /f InfoView.mk clean             Clean the project
#
#
# Additional command line defines: * indicates default
#
# DEBUG=        [ 0* | 1 | 2 ]                  Build debug (0), retail (1), or retail with debug info (2)
# BROWSE=       [ 0* | 1 ]                              Build with browse information (1)
# PLATFORM= [ X86*, MIPS, ALPHA ]       Specify the platform
# DEPEND=   [ 0 | 1* ]                          Indicate whether to include dependent projects (1) or not (0)
# EXEDIR=   directory for DLL           Specify the directory for the DLL
#

# ---------------------------------------------
# ensure all defines are defined
# ---------------------------------------------
!ifndef DEBUG
!message DEBUG not defined; defaulting to DEBUG=0
DEBUG=0
!endif
!ifndef BROWSE
!message BROWSE not defined; defaulting to BROWSE=0
BROWSE=0
!endif
!ifndef DEPEND
!message DEPEND not defined; defaulting to DEPEND=1
DEPEND=1
!endif
!ifndef PLATFORM
!ifndef PROCESSOR_ARCHITECTURE
!message PLATFORM or PROCESSOR_ARCHITECTURE not defined; defaulting to PLATFORM=x86
PLATFORM=x86
!else
PLATFORM=$(PROCESSOR_ARCHITECTURE)
!endif
!endif
!ifndef V4LOW
!message V4LOW not defined; defaulting to V4LOW=0
V4LOW=0
!endif

# ---------------------------------------------
# define relative CAFE directories
# ---------------------------------------------
CAFE_INCLUDE=..\..\include
CAFE_TARGET=..\..\support
CAFE_GUI=..\..\support\guitools
CAFE_IDE=..\..\support\guitools\ide
CAFE_SYM=..\..\support\guitools\ide\sym
CAFE_SHL=..\..\support\guitools\ide\shl
CAFE_EDS=..\..\support\guitools\ide\eds
CAFE_PRJ=..\..\support\guitools\ide\prj
CAFE_DBG=..\..\support\guitools\ide\dbg
CAFE_TOOLSET=..\..\support
CAFE_SUBSUITE=..\..\subsuite

# ---------------------------------------------
# define toolset
# ---------------------------------------------
COMPILER=cl.exe
LINKER=link.exe
RC=rc.exe
BSC=bscmake.exe

# ---------------------------------------------
# set up debug/retail defines
# ---------------------------------------------
# OPTIMIZATIONS ARE TURNED OFF IN RETAIL SINCE WE GOT UTC COMPILER. (RANDOM GPFS) 

!if "$(DEBUG)" == "0"
OBJDIR=WinRel
TARGET=InfoView
CPP_FLAGS=-Od -DNDEBUG -MD
LINK_FLAGS=-incremental:no
!elseif "$(DEBUG)" == "1"
OBJDIR=WinDebug
TARGET=InfoViewd
CPP_FLAGS=-Zi -Od -D_DEBUG -MDd
LINK_FLAGS=-incremental:yes -debug
!else
OBJDIR=WinRel
TARGET=InfoView
CPP_FLAGS=-Zi -O2 -DNDEBUG -MD
LINK_FLAGS=-incremental:no -debug
!endif

!ifndef EXEDIR
EXEDIR=$(OBJDIR)
!endif

# ---------------------------------------------
# set up platform-specific defines
# ---------------------------------------------
!if "$(PLATFORM)" == "x86"
!if "$(DEBUG)" != "0"
!message InfoView: MR enabled
CPP_FLAGS=$(CPP_FLAGS) -Gm
!endif
!endif

# ---------------------------------------------
# set up browse info defines
# ---------------------------------------------
!if "$(BROWSE)" == "0"
BSC_FLAGS=
!else
CPP_FLAGS=$(CPP_FLAGS) -FR$(OBJDIR)^\
BSC_FLAGS=-o$(OBJDIR)\$(TARGET).bsc
!endif

# ---------------------------------------------
# set up toolset flags
# ---------------------------------------------
CPP_FLAGS=$(CPP_FLAGS) -nologo -W3 -GR -GX -DWIN32 -D_WINDOWS -D_AFXDLL -D_MBCS -D_AFXEXT -Fp$(OBJDIR)\$(TARGET).pch -Fo$(OBJDIR)^\ -Fd$(OBJDIR)\$(TARGET).pdb -c
CPP_CREATE_PCH_FLAGS=$(CPP_FLAGS) -Ycstdafx.h
CPP_FLAGS=$(CPP_FLAGS) -Yustdafx.h

LINK_FLAGS=$(LINK_FLAGS) -nologo -subsystem:windows -dll -out:$(EXEDIR)\$(TARGET).dll -pdb:$(EXEDIR)\$(TARGET).pdb
RC_FLAGS=/l 0x409 /fo$(OBJDIR)\ivrsc.res /dNDEBUG /d_AFXDLL
BSC_FLAGS=$(BSC_FLAGS) -nologo

# ---------------------------------------------
# set up V4Low flags
# ---------------------------------------------
!if "$(V4LOW)" == "1"
CPP_FLAGS=$(CPP_FLAGS) -DV4LOW
!endif


# ---------------------------------------------
# define objs			NEW_SNIFF_CHANGE_THIS
# ---------------------------------------------
OBJFILES= \
	$(OBJDIR)\sniff.obj    \
	$(OBJDIR)\stdafx.obj   \
	$(OBJDIR)\ivutil.obj   \
	$(OBJDIR)\dlgwalk.obj  \
	$(OBJDIR)\f1lookup.obj \
	$(OBJDIR)\fts.obj      \
	$(OBJDIR)\generic.obj  \
	$(OBJDIR)\ivrsc.res    \

# ---------------------------------------------
# define sbrs			NEW_SNIFF_CHANGE_THIS
# ---------------------------------------------
SBRFILES= \
	$(OBJDIR)\sniff.sbr    \
	$(OBJDIR)\stdafx.sbr   \
	$(OBJDIR)\ivutil.sbr   \
	$(OBJDIR)\dlgwalk.sbr  \
	$(OBJDIR)\f1lookup.sbr \
	$(OBJDIR)\fts.sbr      \
	$(OBJDIR)\generic.sbr  \


# ---------------------------------------------
# ---------------------------------------------
# rules
# ---------------------------------------------

.c{$(OBJDIR)}.obj:
   @$(COMPILER) -FIstdafx.h -FIW32Repl.h $(CPP_FLAGS) $<

.cpp{$(OBJDIR)}.obj:
   @$(COMPILER) -FIstdafx.h -FIW32Repl.h $(CPP_FLAGS) $<

.cxx{$(OBJDIR)}.obj:
   @$(COMPILER) -FIstdafx.h -FIW32Repl.h $(CPP_FLAGS) $<


# ---------------------------------------------
# ---------------------------------------------
# targets
# ---------------------------------------------

all: dependencies $(EXEDIR)\$(TARGET).dll

# ---------------------------------------------
# build dependencies
# ---------------------------------------------
dependencies:
!if "$(DEPEND)" == "1"
	@echo InfoView: building dependencies...
# SubSuite LIB
	@cd $(CAFE_SUBSUITE)
	@$(MAKE) -nologo -f subsuite.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND)
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# build target DLL
# ---------------------------------------------
$(EXEDIR)\$(TARGET).dll: $(OBJDIR) $(OBJFILES)
	@echo InfoView: linking DLL...
	@-if exist $(EXEDIR)\$(TARGET).dll attrib -r $(EXEDIR)\$(TARGET).dll
	@-if exist $(EXEDIR)\$(TARGET).pdb attrib -r $(EXEDIR)\$(TARGET).pdb
	@-if exist $(EXEDIR)\$(TARGET).lib attrib -r $(EXEDIR)\$(TARGET).lib
	@-if exist $(EXEDIR)\$(TARGET).exp attrib -r $(EXEDIR)\$(TARGET).exp

	@$(LINKER) @<<
		$(LINK_FLAGS) $(OBJFILES)
<<
# ---------------------------------------------
# build BSC
# ---------------------------------------------
!if "$(BROWSE)" == "1"
	@echo InfoView: creating BSC...
	@$(BSC) @<<
		$(BSC_FLAGS) $(SBRFILES)
<<
!endif

# ---------------------------------------------
# object file targets	NEW_SNIFF_CHANGE_THIS
# ---------------------------------------------

$(OBJDIR)\dlgwalk.obj:        \
	dlgwalk.cpp               \
	dlgwalk.h                 \
	stdafx.h                  \
	$(OBJDIR)\stdafx.obj

$(OBJDIR)\f1lookup.obj:       \
	f1lookup.cpp              \
	f1lookup.h                \
	stdafx.h                  \
	$(OBJDIR)\stdafx.obj

$(OBJDIR)\FTS.obj:            \
	FTS.cpp                   \
	FTS.h                     \
	stdafx.h                  \
	$(OBJDIR)\stdafx.obj

$(OBJDIR)\generic.obj:        \
	generic.cpp               \
	generic.h                 \
	stdafx.h                  \
	$(OBJDIR)\stdafx.obj

$(OBJDIR)\ivutil.obj:         \
	ivutil.cpp                \
	ivutil.h                  \
	stdafx.h                  \
	$(OBJDIR)\stdafx.obj

$(OBJDIR)\sniff.obj:          \
	sniff.cpp                 \
	sniff.h                   \
	stdafx.h                  \
	$(CAFE_INCLUDE)\dllmain.h \
	$(OBJDIR)\stdafx.obj

$(OBJDIR)\stdafx.obj:          \
	stdafx.cpp                 \
	stdafx.h                   \
	$(CAFE_INCLUDE)\test.h     \
	$(CAFE_INCLUDE)\subsuite.h \
	$(CAFE_INCLUDE)\support.h
	@echo InfoView: compiling DLL...
	@$(CPP) $(CPP_CREATE_PCH_FLAGS) stdafx.cpp

# ---------------------------------------------
# create object file directory
# ---------------------------------------------
$(OBJDIR):
	@if not exist $(OBJDIR)\nul mkdir $(OBJDIR)

# ---------------------------------------------
# ssync
# ---------------------------------------------
ssync: ssync.depend
	@echo InfoView: ssyncing DLL...
	-ssync -f
	@cd $(CAFE_INCLUDE)
	-ssync -fr
	@cd $(MAKEDIR)

# ---------------------------------------------
# dependency ssync
# ---------------------------------------------
ssync.depend:
!if "$(DEPEND)" == "1"
	@echo InfoView: ssynching dependencies...
# SubSuite LIB
	@cd $(CAFE_SUBSUITE)
	@$(MAKE) -nologo -f subsuite.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) ssync
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# slmout
# ---------------------------------------------
slmout: slmout.depend
	@echo InfoView: checking out DLL...
	@cd $(EXEDIR)
	-out -f $(TARGET).dll
	@cd $(MAKEDIR)

# ---------------------------------------------
# dependency slmout
# ---------------------------------------------
slmout.depend:
!if "$(DEPEND)" == "1"
	@echo InfoView: checking out dependencies...
	@cd $(CAFE_SUBSUITE)
	@$(MAKE) -nologo -f subsuite.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) slmout
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# slmin
# ---------------------------------------------
slmin: slmin.depend
	@echo InfoView: checking in DLL...
	@cd $(EXEDIR)
	-in -f $(TARGET).dll
	@cd $(MAKEDIR)

# ---------------------------------------------
# dependency slmin
# ---------------------------------------------
slmin.depend:
!if "$(DEPEND)" == "1"
	@echo InfoView: checking in dependencies...
	@cd $(CAFE_SUBSUITE)
	@$(MAKE) -nologo -f subsuite.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) slmin
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# clean
# ---------------------------------------------
clean: clean.depend
	@echo InfoView: cleaning DLL...
	@-if exist $(OBJDIR)\*.obj erase $(OBJDIR)\*.obj
	@-if exist $(OBJDIR)\*.pch erase $(OBJDIR)\*.pch
	@-if exist $(OBJDIR)\*.sbr erase $(OBJDIR)\*.sbr
	@-if exist $(OBJDIR)\*.pdb erase $(OBJDIR)\*.pdb
	@-if exist $(OBJDIR)\*.res erase $(OBJDIR)\*.res
	@-if exist $(OBJDIR)\*.bsc erase $(OBJDIR)\*.bsc
	@-if exist $(OBJDIR)\*.ilk erase $(OBJDIR)\*.ilk
	@-if exist $(OBJDIR)\*.lib erase $(OBJDIR)\*.lib
	@-if exist $(OBJDIR)\*.exp erase $(OBJDIR)\*.exp
	@-if exist $(OBJDIR)\*.sym erase $(OBJDIR)\*.sym
	@-if exist $(OBJDIR)\*.dll erase $(OBJDIR)\*.dll
	@-if exist $(OBJDIR)\*.log erase $(OBJDIR)\*.log
	@-if exist $(OBJDIR)\*.txt erase $(OBJDIR)\*.txt
	@-if exist $(OBJDIR)\*.idb erase $(OBJDIR)\*.idb
	@-if exist $(OBJDIR) rmdir $(OBJDIR)
	@-if exist $(EXEDIR)\$(TARGET).dll erase $(EXEDIR)\$(TARGET).dll

# ---------------------------------------------
# dependency clean
# ---------------------------------------------
clean.depend:
!if "$(DEPEND)" == "1"
	@echo InfoView: cleaning dependencies...
	@cd $(CAFE_SUBSUITE)
	@$(MAKE) -nologo -f subsuite.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) clean
	@cd $(MAKEDIR)
!endif
