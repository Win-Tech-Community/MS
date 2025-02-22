/*******************************************************************************

Copyright (c) 2000 Microsoft Corporation.  All rights reserved.

File Name:

    brick2_6.bmp.cpp

Description

    Data file for the resource brick2_6.bmp.

*******************************************************************************/

#include "d3dlocus.h"

static BYTE g_brick2_6[] = {

   0x42, 0x4D, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 
   0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x0E, 0x00, 0x00, 0xC3, 0x0E, 0x00, 0x00, 0x00, 0x00, 
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 
   0xF7, 0xF9, 0x5D, 0x71, 0x9D, 0x5D, 0x72, 0x98, 0xF5, 0xF7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 0xF8, 0xF9, 0x66, 0x7B, 0x9E, 0x66, 0x7A, 0xA2, 
   0xF5, 0xF7, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 
   0xF5, 0xF7, 0x5A, 0x73, 0x97, 0x60, 0x7B, 0x9E, 0xF6, 0xF6, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0xF5, 0xF8, 0x3A, 0xB2, 0xC6, 0x3C, 0xB7, 0xCA, 
   0xF4, 0xF8, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF2, 
   0xFA, 0xFC, 0x27, 0xC9, 0xD6, 0x3C, 0xBA, 0xC9, 0xF6, 0xF9, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 0xF4, 0xF7, 0x44, 0x98, 0xB7, 0x4B, 0x9E, 0xBD, 
   0xF7, 0xF6, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF4, 
   0xF5, 0xF8, 0x5D, 0x69, 0x95, 0x6B, 0x7C, 0xA5, 0xF7, 0xFA, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0xF6, 0xF8, 0x5E, 0x74, 0x8C, 0x6F, 0x89, 0x9F, 
   0xF8, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 
};

static RESOURCEDATA g_rd_brick2_6(TEXT(MODULE_STRING), TEXT("brick2_6.bmp"), g_brick2_6, sizeof(g_brick2_6));

extern "C" LPVOID PREPEND_MODULE(_brick2_6) = (LPVOID)&g_rd_brick2_6;
