!include ..\..\..\..\sources.inc

TARGETNAME=textr6
TARGETTYPE=LIBRARY
TARGETPATH=$(TEST_LIB_DEST)

OBJLIBFILES=\
    $(OBJLIBFILES) \
    $(TEST_LIB_PATH)\l_textr6.lib

SOURCES=\
    include.cpp
