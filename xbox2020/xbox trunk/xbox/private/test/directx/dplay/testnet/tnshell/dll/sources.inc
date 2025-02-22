!IF 0

Copyright (c) 2000 Microsoft Corporation

Module Name:

    sources.

Abstract:

    This file specifies the target component being built and the list of
    sources files needed to build that component.  Also specifies optional
    compiler switches and libraries that are unique for the component being
    built.

Author:

    Tristan Jackson (tristanj)

!ENDIF

TARGETTYPE=DYNLINK
TARGETPATH=$(BASEDIR)\private\test\directx\dplay\testnet\bins

UMENTRY=_DllMainCRTStartup

C_DEFINES=$(C_DEFINES) -DXBOX

INCLUDES=\
    $(INCLUDES); \
    $(BASEDIR)\private\test\directx\dplay\testnet\tncontrl; \
    $(BASEDIR)\private\test\directx\dplay\testnet\tncommon; \
    $(BASEDIR)\private\windows\directx\dplay\inc; \
    $(BASEDIR)\private\test\inc; \
    ..\; \

SOURCES=\
    ..\tnshell.rc \
    ..\main.cpp  \
    ..\prefs.cpp  \
    ..\select.cpp  \

