!include ..\..\..\..\sources.inc

TARGETNAME=m_bees
TARGETTYPE=LIBRARY
TARGETPATH=$(TEST_LIB_DEST)

USER_C_FLAGS=$(USER_C_FLAGS) /Zm200

SOURCES=\
    sparklen.bmp.cpp
