# GUI DLL build
#
# Usage:
#
# nmake /f gui.mk [all]             Build the DLL
# nmake /f gui.mk ssync             Ssync the files needed to build this DLL
# nmake /f gui.mk slmout            Check out the files that are built by this makefile
# nmake /f gui.mk slmin             Check in the files that are built by this makefile
# nmake /f gui.mk clean             Clean the project
# nmake /f gui.mk auto.dep			Generate dependencies file (auto.dep)
#
#
# Additional command line defines: * indicates default
#
# DEBUG=	[ 0* | 1 | 2 ]			Build debug (0), retail (1), or retail with debug info (2)
# BROWSE=	[ 0* | 1 ]				Build with browse information (1)
# PLATFORM= [ X86*, MIPS, ALPHA ]	Specify the platform
# DEPEND=   [ 0 | 1* ]				Indicate whether to include dependent projects (1) or not (0)
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
CAFE_INCLUDE=..\..\..\include
CAFE_TARGET=..
CAFE_GUI=.
CAFE_IDE=ide
CAFE_SYM=ide\sym
CAFE_SHL=ide\shl
CAFE_EDS=ide\eds
CAFE_PRJ=ide\prj
CAFE_DBG=ide\dbg
CAFE_TOOLSET=..
CAFE_LOG=..\..\log

EXEDIR=..\..\..\bin
LIBDIR=..\..\..\lib

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
TARGET=gui
CPP_FLAGS=-Zi -Od -DNDEBUG -MD
LINK_FLAGS=-incremental:no -debug
!elseif "$(DEBUG)" == "1"
OBJDIR=WinDebug
TARGET=guid
CPP_FLAGS=-Zi -Od -D_DEBUG -MDd
LINK_FLAGS=-incremental:yes -debug
!else
OBJDIR=WinRel
TARGET=gui
CPP_FLAGS=-Zi -O2 -DNDEBUG -MD
LINK_FLAGS=-incremental:no -debug
!endif

# ---------------------------------------------
# set up platform-specific defines
# ---------------------------------------------
!if "$(PLATFORM)" == "x86"
!if "$(DEBUG)" != "0"
!message GUI: MR enabled
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
CPP_FLAGS=$(CPP_FLAGS) -nologo -W3 -GR -GX -DWIN32 -D_WINDOWS -D_AFXDLL -D_MBCS -D_AFXEXT -DEXPORT_GUI -Fp$(OBJDIR)\$(TARGET).pch -Fo$(OBJDIR)^\ -Fd$(OBJDIR)\$(TARGET).pdb -c
CPP_CREATE_PCH_FLAGS=$(CPP_FLAGS) -Ycstdafx.h
CPP_FLAGS=$(CPP_FLAGS) -Yustdafx.h
LINK_FLAGS=$(LINK_FLAGS) -nologo -subsystem:windows -dll -out:$(EXEDIR)\$(TARGET).dll -pdb:$(EXEDIR)\$(TARGET).pdb -implib:$(LIBDIR)\$(TARGET).lib
RC_FLAGS=/l 0x409 /fo$(OBJDIR)\gui.res /dNDEBUG /d_AFXDLL
BSC_FLAGS=$(BSC_FLAGS) -nologo
# ---------------------------------------------
# set up V4Low flags
# ---------------------------------------------
!if "$(V4LOW)" == "1"
CPP_FLAGS=$(CPP_FLAGS) -DV4LOW
!endif

# ---------------------------------------------
# define objs
# ---------------------------------------------
OBJFILES= \
	$(OBJDIR)\coclip.obj   \
	$(OBJDIR)\imewrap.obj  \
	$(OBJDIR)\mstwrap.obj  \
	$(OBJDIR)\stdafx.obj   \
	$(OBJDIR)\testutil.obj \
	$(OBJDIR)\uwindow.obj  \
	$(OBJDIR)\udialog.obj  \
	$(OBJDIR)\guitarg.obj  \
	$(OBJDIR)\guiv1.obj    \
	$(OBJDIR)\umsgbox.obj

# ---------------------------------------------
# define sbrs
# ---------------------------------------------
SBRFILES= \
	$(OBJDIR)\coclip.sbr   \
	$(OBJDIR)\imewrap.sbr  \
	$(OBJDIR)\mstwrap.sbr  \
	$(OBJDIR)\stdafx.sbr   \
	$(OBJDIR)\testutil.sbr \
	$(OBJDIR)\uwindow.sbr  \
	$(OBJDIR)\udialog.sbr  \
	$(OBJDIR)\guitarg.sbr  \
	$(OBJDIR)\guiv1.sbr    \
	$(OBJDIR)\umsgbox.sbr


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
	@echo GUI: building dependencies...
# Target
	@cd $(CAFE_TARGET)
	@$(MAKE) -nologo -$(MAKEFLAGS) -f target.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND)
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# build target DLL
# ---------------------------------------------
$(EXEDIR)\$(TARGET).dll: $(OBJDIR) $(OBJDIR)\$(TARGET).pch $(OBJFILES)
	@echo GUI: linking DLL...
	@-if exist $(EXEDIR)\$(TARGET).dll attrib -r $(EXEDIR)\$(TARGET).dll
	@-if exist $(EXEDIR)\$(TARGET).pdb attrib -r $(EXEDIR)\$(TARGET).pdb
	@-if exist $(LIBDIR)\$(TARGET).lib attrib -r $(LIBDIR)\$(TARGET).lib
	@$(LINKER) @<<
		$(LINK_FLAGS) $(OBJFILES)
<<
# ---------------------------------------------
# build BSC
# ---------------------------------------------
!if "$(BROWSE)" == "1"
	@echo GUI: creating BSC...
	@$(BSC) @<<
		$(BSC_FLAGS) $(SBRFILES)
<<
!endif

# ---------------------------------------------
# object file targets
# ---------------------------------------------
!if exist(auto.dep)
!include auto.dep
!else
!message Note: no AUTO.DEP currently exists
!endif

# ---------------------------------------------
# create object file directory
# ---------------------------------------------
$(OBJDIR):
	@if not exist $(OBJDIR)\nul mkdir $(OBJDIR)

# ---------------------------------------------
# ssync
# ---------------------------------------------
ssync: ssync.depend
	@echo GUI: ssyncing DLL...
	-ssync -f
	@cd $(CAFE_INCLUDE)
	-ssync -fr
	@cd $(MAKEDIR)

# ---------------------------------------------
# dependency ssync
# ---------------------------------------------
ssync.depend:
!if "$(DEPEND)" == "1"
	@echo GUI: ssynching dependencies...
# Target
	@cd $(CAFE_TARGET)
	@$(MAKE) -nologo -$(MAKEFLAGS) -f target.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) ssync
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# slmout
# ---------------------------------------------
slmout: slmout.depend
	@echo GUI: checking out DLL...
	@cd $(EXEDIR)
	-out -f $(TARGET).dll $(TARGET).pdb
	@cd $(MAKEDIR)
	@cd $(LIBDIR)
	-out -f $(TARGET).lib
	@cd $(MAKEDIR)

# ---------------------------------------------
# dependency slmout
# ---------------------------------------------
slmout.depend:
!if "$(DEPEND)" == "1"
	@echo GUI: checking out dependencies...
# Target
	@cd $(CAFE_TARGET)
	@$(MAKE) -nologo -$(MAKEFLAGS) -f target.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) slmout
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# slmin
# ---------------------------------------------
slmin: slmin.depend
	@echo GUI: checking in DLL...
	@cd $(EXEDIR)
	-in -c "Automated check-in" -f $(TARGET).dll $(TARGET).pdb
	@cd $(MAKEDIR)
	@cd $(LIBDIR)
	-in -c "Automated check-in" -f $(TARGET).lib
	@cd $(MAKEDIR)

# ---------------------------------------------
# dependency slmin
# ---------------------------------------------
slmin.depend:
!if "$(DEPEND)" == "1"
	@echo GUI: checking in dependencies...
# Target
	@cd $(CAFE_TARGET)
	@$(MAKE) -nologo -$(MAKEFLAGS) -f target.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) slmin
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# clean
# ---------------------------------------------
clean: clean.depend
	@echo GUI: cleaning DLL...
	@-if exist $(OBJDIR)\*.obj erase $(OBJDIR)\*.obj
	@-if exist $(OBJDIR)\*.pch erase $(OBJDIR)\*.pch
	@-if exist $(OBJDIR)\*.sbr erase $(OBJDIR)\*.sbr
	@-if exist $(OBJDIR)\*.pdb erase $(OBJDIR)\*.pdb
	@-if exist $(OBJDIR)\*.res erase $(OBJDIR)\*.res
	@-if exist $(OBJDIR)\*.bsc erase $(OBJDIR)\*.bsc
	@-if exist $(OBJDIR)\*.idb erase $(OBJDIR)\*.idb
	@-if exist $(OBJDIR) rmdir $(OBJDIR)
	@-if exist $(EXEDIR)\$(TARGET).* erase $(EXEDIR)\$(TARGET).*
	@-if exist $(LIBDIR)\$(TARGET).* erase $(LIBDIR)\$(TARGET).*

# ---------------------------------------------
# dependency clean
# ---------------------------------------------
clean.depend:
!if "$(DEPEND)" == "1"
	@echo GUI: cleaning dependencies...
# Target
	@cd $(CAFE_TARGET)
	@$(MAKE) -nologo -$(MAKEFLAGS) -f target.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) clean
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# dependency generation
# ---------------------------------------------
auto.dep: auto.dep.depend
    @attrib -r auto.dep
    @mkdep  -I $(CAFE_INCLUDE) -P $$(OBJDIR)\ -s.obj -n *.cpp >auto.dep

# ---------------------------------------------
# dependencies for dependency generation
# ---------------------------------------------
auto.dep.depend: nul
!if "$(DEPEND)" == "1"
	@echo GUI: Updating dependency files...
# Target
	@cd $(CAFE_TARGET)
	@$(MAKE) -nologo -$(MAKEFLAGS) -f target.mk DEBUG=$(DEBUG) BROWSE=$(BROWSE) PLATFORM=$(PLATFORM) DEPEND=$(DEPEND) auto.dep
	@cd $(MAKEDIR)
!endif

# ---------------------------------------------
# PCH file generation
# ---------------------------------------------
$(OBJDIR)\$(TARGET).pch: stdafx.cpp stdafx.h
	@echo GUI: compiling...
	@$(CPP) $(CPP_CREATE_PCH_FLAGS) stdafx.cpp
