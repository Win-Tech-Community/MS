!IFDEF NVIA64
RMLIBDIR=$(BUILD_TREE)\drivers\resman\arch\nvalloc\winnt4\lib\nv4\ia64
!ELSE
RMLIBDIR=$(BUILD_TREE)\drivers\resman\arch\nvalloc\winnt4\lib\nv4\i386
!ENDIF

!IF "$(BUILD_DDK_VER)"!="nt5"
RMLIBDIR=$(RMLIBDIR)\$(DDKBUILDENV)
!ENDIF

$(RMLIBDIR)\nv10kern.lib:           \
        $(RMLIBDIR)\dacnv10.lib     \
        $(RMLIBDIR)\dmanv10.lib     \
        $(RMLIBDIR)\fbnv10.lib      \
        $(RMLIBDIR)\fifonv10.lib    \
        $(RMLIBDIR)\grnv10.lib      \
        $(RMLIBDIR)\halnv10.lib     \
        $(RMLIBDIR)\mcnv10.lib      \
        $(RMLIBDIR)\modnv10.lib     \
        $(RMLIBDIR)\mpnv10.lib      \
        $(RMLIBDIR)\vidnv10.lib
                $(LIBRARIAN) $**
