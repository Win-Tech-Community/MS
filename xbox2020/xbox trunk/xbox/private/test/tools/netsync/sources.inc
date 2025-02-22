!IF 0

Copyright (c) Microsoft Corporation

Module Name:

    sources.

Abstract:

    This file specifies the target component being built and the list of
    sources files needed to build that component.  Also specifies optional
    compiler switches and libraries that are unique for the component being
    built.

!ENDIF



TARGETPATH=$(BASEDIR)\private\test\lib

PRECOMPILED_INCLUDE=..\precomp.h
PRECOMPILED_PCH=precomp.pch
PRECOMPILED_OBJ=precomp.obj
PRECOMPILED_CXX=1

USECXX_FLAG=/Tp

INCLUDES=\
    $(INCLUDES); \
    $(BASEDIR)\private\test\inc; \
    ..\;

SOURCES=\
    util.c     \
    server.c   \
    client.c   \
    message.c  \
    netsync.c  \
