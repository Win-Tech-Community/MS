TARGETNAME=textr1
TARGETTYPE=PROGRAM
TARGETPATH=obj

!include ..\..\..\..\sources.inc

#UMRES=$(TEST_RES_PATH)\textr.res

TARGETLIBS=\
    $(TARGETLIBS) \
    $(TEST_LIB_PATH)\d3dlocus.lib \
    $(TEST_LIB_PATH)\l_textr1.lib

SOURCES=\
    include.cpp
