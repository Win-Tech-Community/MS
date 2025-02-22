/*
 * Copyright 1993-1998 NVIDIA, Corporation.  All rights reserved.
 * THE INFORMATION CONTAINED HEREIN IS PROPRIETARY AND CONFIDENTIAL TO
 * NVIDIA, CORPORATION.  USE, REPRODUCTION OR DISCLOSURE TO ANY THIRD PARTY
 * IS SUBJECT TO WRITTEN PRE-APPROVAL BY NVIDIA, CORPORATION.
 */
/********************************* Direct 3D *******************************\
*                                                                           *
* Module: nvCelsiusTables.cpp                                               *
*       tables useful for quick lookups of precomputed values               *
*                                                                           *
*****************************************************************************
*                                                                           *
* History:                                                                  *
*       Craig Duttweiler        13May99         NV10 development            *
*                                                                           *
\***************************************************************************/
#include "nvprecomp.h"

#if (NVARCH >= 0x10)

//---------------------------------------------------------------------------

// table of precomputed combiner settings for stupid legacy texture blends.

// the table is indexed as [i][j]
// where i = D3DTBLEND_BLAH
//       j=0 => alpha_icw[0]
//       j=1 => color_icw[0]
//       j=2 => alpha_ocw[0]
//       j=3 => color_ocw[0]

DWORD celsiusTextureBlendSettings[D3D_TBLEND_MAX+1][4] =
{
    // i=0
    // invalid

    ~0,
    ~0,
    ~0,
    ~0,

    // i=1
    // D3DTBLEND_DECAL
    // aPix = aTex
    // cPix = cTex

    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_8)             |  // aTex0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_8)             |  // cTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0),     // dev/null

    // i=2
    // D3DTBLEND_MODULATE
    // aPix = aTex
    // cPix = cTex * cDiffuse

    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_8)             |  // aTex0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_8)             |  // cTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_4)             |  // cDiffuse
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0),     // dev/null

    // i=3
    // D3DTBLEND_DECALALPHA
    // aPix = aDiffuse
    // cPix = ((1 - aTex) * cDiffuse) + (aTex * cTex)

    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_4)             |  // aDiffuse
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_8)             |  // 1-aTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_4)             |  // cDiffuse
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_8)             |  // aTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_8),               // cTex0

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0),     // dev/null

    // i=4
    // D3DTBLEND_MODULATEALPHA
    // aPix = aTex * aDiffuse
    // cPix = cTex * cDiffuse

    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_8)             |  // aTex0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_4)             |  // aDiffuse
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_8)             |  // cTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_4)             |  // cDiffuse
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0),     // dev/null

    // i=5
    // D3DTBLEND_DECALMASK
    // aPix = aDiffuse
    // cPix = lsb(aTex) ? cTex : cDiffuse

    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_4)             |  // aDiffuse
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_4)             |  // cDiffuse
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_8)             |  // cTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _TRUE)    |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0),     // dev/null

    // i=6
    // D3DTBLEND_MODULATEMASK
    // aPix = aDiffuse
    // cPix = lsb(aTex) ? cTex * cDiffuse : cDiffuse

    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_4)             |  // aDiffuse
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_4)             |  // cDiffuse
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_8)             |  // cTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_4),               // cDiffuse

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _TRUE)    |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0),     // dev/null

    // i=7
    // D3DTBLEND_COPY (same as DECAL)
    // aPix = aTex
    // cPix = cTex

    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_8)             |  // aTex0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_8)             |  // cTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0),     // dev/null

    // i=8
    // D3DTBLEND_ADD
    // aPix = aDiffuse
    // cPix = cTex + cDiffuse

    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_4)             |  // aDiffuse
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_8)             |  // cTex0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_4)             |  // cDiffuse
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_0),               // 1

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0)      // dev/null
};

//---------------------------------------------------------------------------

// combiner settings used when they enable a texture blend but not a texture
// aPix = aDiffuse
// cPix = cDiffuse

DWORD celsiusTextureBlendDefault[4] =
{
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _A_SOURCE, _REG_4)             |  // aDiffuse
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_ALPHA,  _TRUE)              |
    DRF_DEF(056, _SET_COMBINER_ALPHA_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _A_SOURCE, _REG_4)             |  // cDiffuse
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_MAP,    _UNSIGNED_INVERT)   |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _B_SOURCE, _REG_0)             |  // 1
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _C_SOURCE, _REG_0)             |  // 0
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_MAP,    _UNSIGNED_IDENTITY) |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_ALPHA,  _FALSE)             |
    DRF_DEF(056, _SET_COMBINER_COLOR_ICW, _D_SOURCE, _REG_0),               // 0

    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _OPERATION,  _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _MUX_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _SUM_DST,    _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _AB_DST,     _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER_ALPHA_OCW, _CD_DST,     _REG_0),     // dev/null

    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _OPERATION,     _NOSHIFT) |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _MUX_ENABLE,    _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DOT_ENABLE, _FALSE)   |
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _SUM_DST,       _REG_C)   |  // a*b + c*d => r12
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _AB_DST,        _REG_0)   |  // dev/null
    DRF_DEF(056, _SET_COMBINER0_COLOR_OCW, _CD_DST,        _REG_0)      // dev/null
};

//---------------------------------------------------------------------------

// table mapping dependencies between d3d renderstates and celsius state.

// celsiusDirtyBitsFromRenderState[D3DRENDERSTATE_FOO] contains the celsius class
// dirty bits that should be set whenever D3DRENDERSTATE_FOO is changed

DWORD celsiusDirtyBitsFromRenderState[D3D_RENDERSTATE_MAX+1] =
{
    0,                                                            //  0   invalid
    (CELSIUS_DIRTY_COMBINERS | CELSIUS_DIRTY_TEXTURE_STATE |      //  1   D3DRENDERSTATE_TEXTUREHANDLE
     CELSIUS_DIRTY_TEXTURE_TRANSFORM),
    0,                                                            //  2   D3DRENDERSTATE_ANTIALIAS
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  3   D3DRENDERSTATE_TEXTUREADDRESS
    (CELSIUS_DIRTY_TEXTURE_STATE | CELSIUS_DIRTY_CONTROL0),       //  4   D3DRENDERSTATE_TEXTUREPERSPECTIVE
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  5   D3DRENDERSTATE_WRAPU
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  6   D3DRENDERSTATE_WRAPV
    (CELSIUS_DIRTY_TRANSFORM | CELSIUS_DIRTY_CONTROL0 |           //  7   D3DRENDERSTATE_ZENABLE
     CELSIUS_DIRTY_TEXTURE_STATE | CELSIUS_DIRTY_MISC_STATE |
     CELSIUS_DIRTY_SPECFOG_COMBINER | CELSIUS_DIRTY_TL_MODE),
    CELSIUS_DIRTY_MISC_STATE,                                     //  8   D3DRENDERSTATE_FILLMODE
    CELSIUS_DIRTY_MISC_STATE,                                     //  9   D3DRENDERSTATE_SHADEMODE
    0,                                                            //  10  D3DRENDERSTATE_LINEPATTERN
    0,                                                            //  11  D3DRENDERSTATE_MONOENABLE
    0,                                                            //  12  D3DRENDERSTATE_ROP2
    CELSIUS_DIRTY_MISC_STATE,                                     //  13  D3DRENDERSTATE_PLANEMASK
    CELSIUS_DIRTY_MISC_STATE,                                     //  14  D3DRENDERSTATE_ZWRITEENABLE
    CELSIUS_DIRTY_MISC_STATE,                                     //  15  D3DRENDERSTATE_ALPHATESTENABLE
    0,                                                            //  16  D3DRENDERSTATE_LASTPIXEL
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  17  D3DRENDERSTATE_TEXTUREMAG
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  18  D3DRENDERSTATE_TEXTUREMIN
    CELSIUS_DIRTY_MISC_STATE,                                     //  19  D3DRENDERSTATE_SRCBLEND
    CELSIUS_DIRTY_MISC_STATE,                                     //  20  D3DRENDERSTATE_DESTBLEND
    CELSIUS_DIRTY_COMBINERS,                                      //  21  D3DRENDERSTATE_TEXTUREMAPBLEND
    CELSIUS_DIRTY_MISC_STATE,                                     //  22  D3DRENDERSTATE_CULLMODE
    CELSIUS_DIRTY_MISC_STATE,                                     //  23  D3DRENDERSTATE_ZFUNC
    CELSIUS_DIRTY_MISC_STATE,                                     //  24  D3DRENDERSTATE_ALPHAREF
    CELSIUS_DIRTY_MISC_STATE,                                     //  25  D3DRENDERSTATE_ALPHAFUNC
    CELSIUS_DIRTY_MISC_STATE,                                     //  26  D3DRENDERSTATE_DITHERENABLE
    CELSIUS_DIRTY_MISC_STATE,                                     //  27  D3DRENDERSTATE_ALPHABLENDENABLE
    CELSIUS_DIRTY_SPECFOG_COMBINER,                               //  28  D3DRENDERSTATE_FOGENABLE
    (CELSIUS_DIRTY_LIGHTS | CELSIUS_DIRTY_SPECFOG_COMBINER),      //  29  D3DRENDERSTATE_SPECULARENABLE
    0,                                                            //  30  D3DRENDERSTATE_ZVISIBLE
    0,                                                            //  31  D3DRENDERSTATE_SUBPIXEL
    0,                                                            //  32  D3DRENDERSTATE_SUBPIXELX
    0,                                                            //  33  D3DRENDERSTATE_STIPPLEDALPHA
    CELSIUS_DIRTY_SPECFOG_COMBINER,                               //  34  D3DRENDERSTATE_FOGCOLOR
    CELSIUS_DIRTY_SPECFOG_COMBINER,                               //  35  D3DRENDERSTATE_FOGTABLEMODE
    CELSIUS_DIRTY_SPECFOG_COMBINER,                               //  36  D3DRENDERSTATE_FOGTABLESTART   (D3DRENDERSTATE_FOGSTART)
    CELSIUS_DIRTY_SPECFOG_COMBINER,                               //  37  D3DRENDERSTATE_FOGTABLEEND     (D3DRENDERSTATE_FOGEND)
    CELSIUS_DIRTY_SPECFOG_COMBINER,                               //  38  D3DRENDERSTATE_FOGTABLEDENSITY (D3DRENDERSTATE_FOGDENSITY)
    0,                                                            //  39  D3DRENDERSTATE_STIPPLEENABLE
    CELSIUS_DIRTY_MISC_STATE,                                     //  40  D3DRENDERSTATE_EDGEANTIALIAS
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  41  D3DRENDERSTATE_COLORKEYENABLE
    0,                                                            //  42  D3DRENDERSTATE_OLDALPHABLENDENABLE
    0,                                                            //  43  D3DRENDERSTATE_BORDERCOLOR
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  44  D3DRENDERSTATE_TEXTUREADDRESSU
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  45  D3DRENDERSTATE_TEXTUREADDRESSV
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  46  D3DRENDERSTATE_MIPMAPLODBIAS
    CELSIUS_DIRTY_MISC_STATE,                                     //  47  D3DRENDERSTATE_ZBIAS
    CELSIUS_DIRTY_SPECFOG_COMBINER,                               //  48  D3DRENDERSTATE_RANGEFOGENABLE
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  49  D3DRENDERSTATE_ANISOTROPY
    0,                                                            //  50  D3DRENDERSTATE_FLUSHBATCH
    0,                                                            //  51  D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT
    (CELSIUS_DIRTY_CONTROL0 | CELSIUS_DIRTY_MISC_STATE),          //  52  D3DRENDERSTATE_STENCILENABLE
    CELSIUS_DIRTY_MISC_STATE,                                     //  53  D3DRENDERSTATE_STENCILFAIL
    CELSIUS_DIRTY_MISC_STATE,                                     //  54  D3DRENDERSTATE_STENCILZFAIL
    CELSIUS_DIRTY_MISC_STATE,                                     //  55  D3DRENDERSTATE_STENCILPASS
    CELSIUS_DIRTY_MISC_STATE,                                     //  56  D3DRENDERSTATE_STENCILFUNC
    CELSIUS_DIRTY_MISC_STATE,                                     //  57  D3DRENDERSTATE_STENCILREF
    CELSIUS_DIRTY_MISC_STATE,                                     //  58  D3DRENDERSTATE_STENCILMASK
    CELSIUS_DIRTY_MISC_STATE,                                     //  59  D3DRENDERSTATE_STENCILWRITEMASK
    CELSIUS_DIRTY_MISC_STATE,                                     //  60  D3DRENDERSTATE_TEXTUREFACTOR
    0,                                                            //  61  D3DRENDERSTATE_EVICTMANAGEDTEXTURES
    0,                                                            //  62  D3DRENDERSTATE_SCENECAPTURE
    0,                                                            //  63  invalid
    0,                                                            //  64  D3DRENDERSTATE_STIPPLEPATTERN00
    0,                                                            //  65  D3DRENDERSTATE_STIPPLEPATTERN01
    0,                                                            //  66  D3DRENDERSTATE_STIPPLEPATTERN02
    0,                                                            //  67  D3DRENDERSTATE_STIPPLEPATTERN03
    0,                                                            //  68  D3DRENDERSTATE_STIPPLEPATTERN04
    0,                                                            //  69  D3DRENDERSTATE_STIPPLEPATTERN05
    0,                                                            //  70  D3DRENDERSTATE_STIPPLEPATTERN06
    0,                                                            //  71  D3DRENDERSTATE_STIPPLEPATTERN07
    0,                                                            //  72  D3DRENDERSTATE_STIPPLEPATTERN08
    0,                                                            //  73  D3DRENDERSTATE_STIPPLEPATTERN09
    0,                                                            //  74  D3DRENDERSTATE_STIPPLEPATTERN10
    0,                                                            //  75  D3DRENDERSTATE_STIPPLEPATTERN11
    0,                                                            //  76  D3DRENDERSTATE_STIPPLEPATTERN12
    0,                                                            //  77  D3DRENDERSTATE_STIPPLEPATTERN13
    0,                                                            //  78  D3DRENDERSTATE_STIPPLEPATTERN14
    0,                                                            //  79  D3DRENDERSTATE_STIPPLEPATTERN15
    0,                                                            //  80  D3DRENDERSTATE_STIPPLEPATTERN16
    0,                                                            //  81  D3DRENDERSTATE_STIPPLEPATTERN17
    0,                                                            //  82  D3DRENDERSTATE_STIPPLEPATTERN18
    0,                                                            //  83  D3DRENDERSTATE_STIPPLEPATTERN19
    0,                                                            //  84  D3DRENDERSTATE_STIPPLEPATTERN20
    0,                                                            //  85  D3DRENDERSTATE_STIPPLEPATTERN21
    0,                                                            //  86  D3DRENDERSTATE_STIPPLEPATTERN22
    0,                                                            //  87  D3DRENDERSTATE_STIPPLEPATTERN23
    0,                                                            //  88  D3DRENDERSTATE_STIPPLEPATTERN24
    0,                                                            //  89  D3DRENDERSTATE_STIPPLEPATTERN25
    0,                                                            //  90  D3DRENDERSTATE_STIPPLEPATTERN26
    0,                                                            //  91  D3DRENDERSTATE_STIPPLEPATTERN27
    0,                                                            //  92  D3DRENDERSTATE_STIPPLEPATTERN28
    0,                                                            //  93  D3DRENDERSTATE_STIPPLEPATTERN29
    0,                                                            //  94  D3DRENDERSTATE_STIPPLEPATTERN30
    0,                                                            //  95  D3DRENDERSTATE_STIPPLEPATTERN31
    0,                                                            //  96  invalid
    0,                                                            //  97  invalid
    0,                                                            //  98  invalid
    0,                                                            //  99  invalid
    0,                                                            //  100 invalid
    0,                                                            //  101 invalid
    0,                                                            //  102 invalid
    0,                                                            //  103 invalid
    0,                                                            //  104 invalid
    0,                                                            //  105 invalid
    0,                                                            //  106 invalid
    0,                                                            //  107 invalid
    0,                                                            //  108 invalid
    0,                                                            //  109 invalid
    0,                                                            //  110 invalid
    0,                                                            //  111 invalid
    0,                                                            //  112 invalid
    0,                                                            //  113 invalid
    0,                                                            //  114 invalid
    0,                                                            //  115 invalid
    0,                                                            //  116 invalid
    0,                                                            //  117 invalid
    0,                                                            //  118 invalid
    0,                                                            //  119 invalid
    0,                                                            //  120 invalid
    0,                                                            //  121 invalid
    0,                                                            //  122 invalid
    0,                                                            //  123 invalid
    0,                                                            //  124 invalid
    0,                                                            //  125 invalid
    0,                                                            //  126 invalid
    0,                                                            //  127 invalid
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  128 D3DRENDERSTATE_WRAP0
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  129 D3DRENDERSTATE_WRAP1
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  130 D3DRENDERSTATE_WRAP2
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  131 D3DRENDERSTATE_WRAP3
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  132 D3DRENDERSTATE_WRAP4
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  133 D3DRENDERSTATE_WRAP5
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  134 D3DRENDERSTATE_WRAP6
    (CELSIUS_DIRTY_TL_MODE | CELSIUS_DIRTY_TEXTURE_STATE),        //  135 D3DRENDERSTATE_WRAP7
    0,                                                            //  136 D3DRENDERSTATE_CLIPPING
    CELSIUS_DIRTY_LIGHTS,                                         //  137 D3DRENDERSTATE_LIGHTING
    0,                                                            //  138 D3DRENDERSTATE_EXTENTS
    CELSIUS_DIRTY_LIGHTS,                                         //  139 D3DRENDERSTATE_AMBIENT
    CELSIUS_DIRTY_SPECFOG_COMBINER,                               //  140 D3DRENDERSTATE_FOGVERTEXMODE
    CELSIUS_DIRTY_LIGHTS,                                         //  141 D3DRENDERSTATE_COLORVERTEX
    CELSIUS_DIRTY_LIGHTS,                                         //  142 D3DRENDERSTATE_LOCALVIEWER
    CELSIUS_DIRTY_TRANSFORM,                                      //  143 D3DRENDERSTATE_NORMALIZENORMALS
    0,                                                            //  144 D3DRENDERSTATE_COLORKEYBLENDENABLE
    CELSIUS_DIRTY_LIGHTS,                                         //  145 D3DRENDERSTATE_DIFFUSEMATERIALSOURCE
    CELSIUS_DIRTY_LIGHTS,                                         //  146 D3DRENDERSTATE_SPECULARMATERIALSOURCE
    CELSIUS_DIRTY_LIGHTS,                                         //  147 D3DRENDERSTATE_AMBIENTMATERIALSOURCE
    CELSIUS_DIRTY_LIGHTS,                                         //  148 D3DRENDERSTATE_EMISSIVEMATERIALSOURCE
    CELSIUS_DIRTY_LIGHTS,                                         //  149 D3DRENDERSTATE_ALPHASOURCE
    CELSIUS_DIRTY_LIGHTS,                                         //  150 D3DRENDERSTATE_FOGFACTORSOURCE
    (CELSIUS_DIRTY_MISC_STATE | CELSIUS_DIRTY_TRANSFORM),         //  151 D3DRENDERSTATE_VERTEXBLEND
    CELSIUS_DIRTY_TEXTURE_STATE,                                  //  152 D3DRENDERSTATE_CLIPPLANEENABLE
    0,                                                            //  153 D3DRENDERSTATE_SOFTWAREVEXTEXPROCESSING
    CELSIUS_DIRTY_MISC_STATE,                                     //  154 D3DRENDERSTATE_POINTSIZE
    CELSIUS_DIRTY_MISC_STATE,                                     //  155 D3DRENDERSTATE_POINTSIZEMIN
    CELSIUS_DIRTY_MISC_STATE | CELSIUS_DIRTY_TEXTURE_STATE,       //  156 D3DRENDERSTATE_POINTSPRITEENABLE
    CELSIUS_DIRTY_MISC_STATE | CELSIUS_DIRTY_TEXTURE_STATE,       //  157 D3DRENDERSTATE_POINTSCALEENABLE
    CELSIUS_DIRTY_MISC_STATE,                                     //  158 D3DRENDERSTATE_POINTSCALEA
    CELSIUS_DIRTY_MISC_STATE,                                     //  159 D3DRENDERSTATE_POINTSCALEB
    CELSIUS_DIRTY_MISC_STATE,                                     //  150 D3DRENDERSTATE_POINTSCALEC
    0,                                                            //  161 D3DRENDERSTATE_MULTISAMPLEAA
    0,                                                            //  162 D3DRENDERSTATE_MULTISAMPLEMASK
    0,                                                            //  163 D3DRENDERSTATE_COLORKEYMASK
    0,                                                            //  164 D3DRS_PATCHSEGMENTS
    0,                                                            //  165 D3DRS_DEBUGMONITORTOKEN
    0,                                                            //  166 D3DRS_POINTSIZE_MAX
    0,                                                            //  167 D3DRS_INDEXEDVERTEXBLENDENABLE
    CELSIUS_DIRTY_MISC_STATE,                                     //  168 D3DRS_COLORWRITEENABLE
    0,                                                            //  169 invalid
    0,                                                            //  170 D3DRS_TWEENFACTOR
    CELSIUS_DIRTY_MISC_STATE,                                     //  171 D3DRS_BLENDOP
};

//---------------------------------------------------------------------------

// table mapping dependencies between d3d texture stage state and celsius state.

// celsiusDirtyBitsFromTextureStageState[D3DTSS_FOO] contains the celsius class
// dirty bits that should be set whenever D3DTSS_FOO is changed

DWORD celsiusDirtyBitsFromTextureStageState[D3D_TEXSTAGESTATE_MAX+1] =
{
    CELSIUS_DIRTY_TEXTURE_STATE | CELSIUS_DIRTY_TEXTURE_TRANSFORM | //  0  D3DTSS_TEXTUREMAP
    CELSIUS_DIRTY_COMBINERS,
    CELSIUS_DIRTY_TEXTURE_TRANSFORM | CELSIUS_DIRTY_COMBINERS,      //  1  D3DTSS_COLOROP
    CELSIUS_DIRTY_COMBINERS,                                        //  2  D3DTSS_COLORARG1
    CELSIUS_DIRTY_COMBINERS,                                        //  3  D3DTSS_COLORARG2
    CELSIUS_DIRTY_COMBINERS,                                        //  4  D3DTSS_ALPHAOP
    CELSIUS_DIRTY_COMBINERS,                                        //  5  D3DTSS_ALPHAARG1
    CELSIUS_DIRTY_COMBINERS,                                        //  6  D3DTSS_ALPHAARG2
    0,                                                              //  7  D3DTSS_BUMPENVMAT00
    0,                                                              //  8  D3DTSS_BUMPENVMAT01
    0,                                                              //  9  D3DTSS_BUMPENVMAT10
    0,                                                              //  10 D3DTSS_BUMPENVMAT11
    CELSIUS_DIRTY_TEXTURE_TRANSFORM | CELSIUS_DIRTY_TEXTURE_STATE | //  11 D3DTSS_TEXCOORDINDEX
    CELSIUS_DIRTY_FVF | CELSIUS_DIRTY_TL_MODE,
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  12 D3DTSS_ADDRESS
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  13 D3DTSS_ADDRESSU
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  14 D3DTSS_ADDRESSV
    0,                                                              //  15 D3DTSS_BORDERCOLOR
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  16 D3DTSS_MAGFILTER
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  17 D3DTSS_MINFILTER
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  18 D3DTSS_MIPFILTER
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  19 D3DTSS_MIPMAPLODBIAS
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  20 D3DTSS_MAXMIPLEVEL
    CELSIUS_DIRTY_TEXTURE_STATE,                                    //  21 D3DTSS_MAXANISOTROPY
    0,                                                              //  22 D3DTSS_BUMPENVLSCALE
    0,                                                              //  23 D3DTSS_BUMPENVLOFFSET
    CELSIUS_DIRTY_TEXTURE_TRANSFORM,                                //  24 D3DTSS_TEXTURETRANSFORMFLAGS
    0,                                                              //  25 D3DTSS_ADDRESSW
    CELSIUS_DIRTY_COMBINERS,                                        //  26 D3DTSS_COLORARG0
    CELSIUS_DIRTY_COMBINERS,                                        //  27 D3DTSS_ALPHAARG0
    CELSIUS_DIRTY_COMBINERS                                         //  28 D3DTSS_RESULTARG
};

//---------------------------------------------------------------------------

// table mapping dp2ops to the celsius method values associated with them.
// these are defined in term of NV056_SET_BEGIN_END_OP_X but the same values
// are used for all enumerants of type NV056_SET_BEGIN_ENDX_OP_X

DWORD celsiusBeginEndOp[D3D_DP2OP_MAX+1] =
{
    ~0,                                          //   0  invalid
    NV056_SET_BEGIN_END_OP_POINTS,               //   1  D3DDP2OP_POINTS
    NV056_SET_BEGIN_END_OP_LINES,                //   2  D3DDP2OP_INDEXEDLINELIST
    NV056_SET_BEGIN_END_OP_TRIANGLES,            //   3  D3DDP2OP_INDEXEDTRIANGLELIST
    ~0,                                          //   4  invalid
    ~0,                                          //   5  invalid
    ~0,                                          //   6  invalid
    ~0,                                          //   7  invalid
    ~0,                                          //   8  D3DDP2OP_RENDERSTATE
    ~0,                                          //   9  invalid
    ~0,                                          //  10  invalid
    ~0,                                          //  11  invalid
    ~0,                                          //  12  invalid
    ~0,                                          //  13  invalid
    ~0,                                          //  14  invalid
    NV056_SET_BEGIN_END_OP_LINES,                //  15  D3DDP2OP_LINELIST
    NV056_SET_BEGIN_END_OP_LINE_STRIP,           //  16  D3DDP2OP_LINESTRIP
    NV056_SET_BEGIN_END_OP_LINE_STRIP,           //  17  D3DDP2OP_INDEXEDLINESTRIP
    NV056_SET_BEGIN_END_OP_TRIANGLES,            //  18  D3DDP2OP_TRIANGLELIST
    NV056_SET_BEGIN_END_OP_TRIANGLE_STRIP,       //  19  D3DDP2OP_TRIANGLESTRIP
    NV056_SET_BEGIN_END_OP_TRIANGLE_STRIP,       //  20  D3DDP2OP_INDEXEDTRIANGLESTRIP
    NV056_SET_BEGIN_END_OP_TRIANGLE_FAN,         //  21  D3DDP2OP_TRIANGLEFAN
    NV056_SET_BEGIN_END_OP_TRIANGLE_FAN,         //  22  D3DDP2OP_INDEXEDTRIANGLEFAN
    NV056_SET_BEGIN_END_OP_TRIANGLE_FAN,         //  23  D3DDP2OP_TRIANGLEFAN_IMM
    NV056_SET_BEGIN_END_OP_LINES,                //  24  D3DDP2OP_LINELIST_IMM
    ~0,                                          //  25  D3DDP2OP_TEXTURESTAGESTATE
    NV056_SET_BEGIN_END_OP_TRIANGLES,            //  26  D3DDP2OP_INDEXEDTRIANGLELIST2
    NV056_SET_BEGIN_END_OP_LINES,                //  27  D3DDP2OP_INDEXEDLINELIST2
    ~0,                                          //  28  D3DDP2OP_VIEWPORTINFO
    ~0,                                          //  29  D3DDP2OP_WINFO
    ~0,                                          //  30  D3DDP2OP_SETPALETTE
    ~0,                                          //  31  D3DDP2OP_UPDATEPALETTE
    ~0,                                          //  32  D3DDP2OP_ZRANGE
    ~0,                                          //  33  D3DDP2OP_SETMATERIAL
    ~0,                                          //  34  D3DDP2OP_SETLIGHT
    ~0,                                          //  35  D3DDP2OP_CREATELIGHT
    ~0,                                          //  36  D3DDP2OP_SETTRANSFORM
    ~0,                                          //  37  D3DDP2OP_EXT
    ~0,                                          //  38  D3DDP2OP_TEXBLT
    ~0,                                          //  39  D3DDP2OP_STATESET
    ~0,                                          //  40  D3DDP2OP_SETPRIORITY
    ~0,                                          //  41  D3DDP2OP_SETRENDERTARGET
    ~0,                                          //  42  D3DDP2OP_CLEAR
    ~0,                                          //  43  D3DDP2OP_SETTEXLOD
    ~0                                           //  44  D3DDP2OP_SETCLIPPLANE
};

//---------------------------------------------------------------------------

// table mapping dp2ops to the scale and bias required to calculate the number
// of vertices from the number of primitives. the scale is in the upper half
// of the word and the bias is in the lower.
// numVertices = scale * numPrimitives + bias

DWORD celsiusPrimitiveToPrimitiveMagic[D3D_DP2OP_MAX+1] =
{
    ~0,                                          //   0  invalid
    0x00010100,                                  //   1  D3DDP2OP_POINTS
    0x00020200,                                  //   2  D3DDP2OP_INDEXEDLINELIST
    0x00030300,                                  //   3  D3DDP2OP_INDEXEDTRIANGLELIST
    ~0,                                          //   4  invalid
    ~0,                                          //   5  invalid
    ~0,                                          //   6  invalid
    ~0,                                          //   7  invalid
    ~0,                                          //   8  D3DDP2OP_RENDERSTATE
    ~0,                                          //   9  invalid
    ~0,                                          //  10  invalid
    ~0,                                          //  11  invalid
    ~0,                                          //  12  invalid
    ~0,                                          //  13  invalid
    ~0,                                          //  14  invalid
    0x00020200,                                  //  15  D3DDP2OP_LINELIST
    0x00020101,                                  //  16  D3DDP2OP_LINESTRIP
    0x00020101,                                  //  17  D3DDP2OP_INDEXEDLINESTRIP
    0x00030300,                                  //  18  D3DDP2OP_TRIANGLELIST
    0x40030102,                                  //  19  D3DDP2OP_TRIANGLESTRIP
    0x40030102,                                  //  20  D3DDP2OP_INDEXEDTRIANGLESTRIP
    0x80030102,                                  //  21  D3DDP2OP_TRIANGLEFAN
    0x80030102,                                  //  22  D3DDP2OP_INDEXEDTRIANGLEFAN
    0x80030102,                                  //  23  D3DDP2OP_TRIANGLEFAN_IMM
    0x00020200,                                  //  24  D3DDP2OP_LINELIST_IMM
    ~0,                                          //  25  D3DDP2OP_TEXTURESTAGESTATE
    0x00030300,                                  //  26  D3DDP2OP_INDEXEDTRIANGLELIST2
    0x00020200,                                  //  27  D3DDP2OP_INDEXEDLINELIST2
    ~0,                                          //  28  D3DDP2OP_VIEWPORTINFO
    ~0,                                          //  29  D3DDP2OP_WINFO
    ~0,                                          //  30  D3DDP2OP_SETPALETTE
    ~0,                                          //  31  D3DDP2OP_UPDATEPALETTE
    ~0,                                          //  32  D3DDP2OP_ZRANGE
    ~0,                                          //  33  D3DDP2OP_SETMATERIAL
    ~0,                                          //  34  D3DDP2OP_SETLIGHT
    ~0,                                          //  35  D3DDP2OP_CREATELIGHT
    ~0,                                          //  36  D3DDP2OP_SETTRANSFORM
    ~0,                                          //  37  D3DDP2OP_EXT
    ~0,                                          //  38  D3DDP2OP_TEXBLT
    ~0,                                          //  39  D3DDP2OP_STATESET
    ~0,                                          //  40  D3DDP2OP_SETPRIORITY
    ~0,                                          //  41  D3DDP2OP_SETRENDERTARGET
    ~0,                                          //  42  D3DDP2OP_CLEAR
    ~0,                                          //  43  D3DDP2OP_SETTEXLOD
    ~0                                           //  44  D3DDP2OP_SETCLIPPLANE
};

//---------------------------------------------------------------------------

// table mapping dp2ops to a name humans understand

#ifdef DEBUG
char* celsiusPrimitiveName[D3D_DP2OP_MAX+1] =
{
    "oops",                                      //   0  invalid
    "points",                                    //   1  D3DDP2OP_POINTS
    "indexed line list",                         //   2  D3DDP2OP_INDEXEDLINELIST
    "indexed tri list",                          //   3  D3DDP2OP_INDEXEDTRIANGLELIST
    "oops",                                      //   4  invalid
    "oops",                                      //   5  invalid
    "oops",                                      //   6  invalid
    "oops",                                      //   7  invalid
    "oops",                                      //   8  D3DDP2OP_RENDERSTATE
    "oops",                                      //   9  invalid
    "oops",                                      //  10  invalid
    "oops",                                      //  11  invalid
    "oops",                                      //  12  invalid
    "oops",                                      //  13  invalid
    "oops",                                      //  14  invalid
    "line list",                                 //  15  D3DDP2OP_LINELIST
    "line strip",                                //  16  D3DDP2OP_LINESTRIP
    "indexed line strip",                        //  17  D3DDP2OP_INDEXEDLINESTRIP
    "tri list",                                  //  18  D3DDP2OP_TRIANGLELIST
    "tri strip",                                 //  19  D3DDP2OP_TRIANGLESTRIP
    "indexed tri strip",                         //  20  D3DDP2OP_INDEXEDTRIANGLESTRIP
    "tri fan",                                   //  21  D3DDP2OP_TRIANGLEFAN
    "indexed tri fan",                           //  22  D3DDP2OP_INDEXEDTRIANGLEFAN
    "tri fan imm",                               //  23  D3DDP2OP_TRIANGLEFAN_IMM
    "line list imm",                             //  24  D3DDP2OP_LINELIST_IMM
    "oops",                                      //  25  D3DDP2OP_TEXTURESTAGESTATE
    "indexed tri list 2",                        //  26  D3DDP2OP_INDEXEDTRIANGLELIST2
    "indexed line list 2",                       //  27  D3DDP2OP_INDEXEDLINELIST2
    "oops",                                      //  28  D3DDP2OP_VIEWPORTINFO
    "oops",                                      //  29  D3DDP2OP_WINFO
    "oops",                                      //  30  D3DDP2OP_SETPALETTE
    "oops",                                      //  31  D3DDP2OP_UPDATEPALETTE
    "oops",                                      //  32  D3DDP2OP_ZRANGE
    "oops",                                      //  33  D3DDP2OP_SETMATERIAL
    "oops",                                      //  34  D3DDP2OP_SETLIGHT
    "oops",                                      //  35  D3DDP2OP_CREATELIGHT
    "oops",                                      //  36  D3DDP2OP_SETTRANSFORM
    "oops",                                      //  37  D3DDP2OP_EXT
    "oops",                                      //  38  D3DDP2OP_TEXBLT
    "oops",                                      //  39  D3DDP2OP_STATESET
    "oops",                                      //  40  D3DDP2OP_SETPRIORITY
    "oops",                                      //  41  D3DDP2OP_SETRENDERTARGET
    "oops",                                      //  42  D3DDP2OP_CLEAR
    "oops",                                      //  43  D3DDP2OP_SETTEXLOD
    "oops"                                       //  44  D3DDP2OP_SETCLIPPLANE
};
#endif

// table needed to dispatch the right method for vertex shaders
// [] . .  stream  - ie vertex vs diffuse
// . [] .  data type  - ie XYZ vs XYZW
// . . [0] method name
// . . [1] param count (popcount of second index)
DWORD dwCelsiusMethodDispatch[11][16][2] = {
        // 0 vertex
        0xDEADBEEF,                    0, //  0 none
        0xDEADBEEF,                    0, //  1 x
        0xDEADBEEF,                    0, //  2  y
        0xDEADBEEF,                    0, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        0xDEADBEEF,                    0, //  5 x z
        0xDEADBEEF,                    0, //  6  yz
        NV056_SET_VERTEX3F(0),         3, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        0xDEADBEEF,                    0, //  9 x  w
        0xDEADBEEF,                    0, // 10  y w
        NV056_SET_VERTEX3F(0),         3, // 11 xy w
        0xDEADBEEF,                    0, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        NV056_SET_VERTEX4F(0),         4, // 15 xyzw

        // 1 diffuse
        0xDEADBEEF,                    0, //  0 none
        0xDEADBEEF,                    0, //  1 x
        0xDEADBEEF,                    0, //  2  y
        0xDEADBEEF,                    0, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        0xDEADBEEF,                    0, //  5 x z
        0xDEADBEEF,                    0, //  6  yz
        NV056_SET_DIFFUSE_COLOR3F(0),  3, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        0xDEADBEEF,                    0, //  9 x  w
        0xDEADBEEF,                    0, // 10  y w
        NV056_SET_DIFFUSE_COLOR3F(0),  3, // 11 xy w
        0xDEADBEEF,                    0, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        NV056_SET_DIFFUSE_COLOR4F(0),  4, // 15 xyzw

        // 2 specular
        0xDEADBEEF,                    0, //  0 none
        0xDEADBEEF,                    0, //  1 x
        0xDEADBEEF,                    0, //  2  y
        0xDEADBEEF,                    0, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        0xDEADBEEF,                    0, //  5 x z
        0xDEADBEEF,                    0, //  6  yz
        NV056_SET_SPECULAR_COLOR3F(0), 3, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        0xDEADBEEF,                    0, //  9 x  w
        0xDEADBEEF,                    0, // 10  y w
        NV056_SET_SPECULAR_COLOR3F(0), 3, // 11 xy w
        0xDEADBEEF,                    0, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        NV056_SET_SPECULAR_COLOR4F(0), 4, // 15 xyzw

        // 3 backfacing diffuse - unused
        0xDEADBEEF,                    0, //  0 none
        0xDEADBEEF,                    0, //  1 x
        0xDEADBEEF,                    0, //  2  y
        0xDEADBEEF,                    0, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        0xDEADBEEF,                    0, //  5 x z
        0xDEADBEEF,                    0, //  6  yz
        0xDEADBEEF,                    0, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        0xDEADBEEF,                    0, //  9 x  w
        0xDEADBEEF,                    0, // 10  y w
        0xDEADBEEF,                    0, // 11 xy w
        0xDEADBEEF,                    0, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        0xDEADBEEF,                    0, // 15 xyzw

        // 4 backfacing specular - unused
        0xDEADBEEF,                    0, //  0 none
        0xDEADBEEF,                    0, //  1 x
        0xDEADBEEF,                    0, //  2  y
        0xDEADBEEF,                    0, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        0xDEADBEEF,                    0, //  5 x z
        0xDEADBEEF,                    0, //  6  yz
        0xDEADBEEF,                    0, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        0xDEADBEEF,                    0, //  9 x  w
        0xDEADBEEF,                    0, // 10  y w
        0xDEADBEEF,                    0, // 11 xy w
        0xDEADBEEF,                    0, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        0xDEADBEEF,                    0, // 15 xyzw

        // 5 fog
        0xDEADBEEF,                    0, //  0 none
        NV056_SET_FOG1F,               1, //  1 x
        0xDEADBEEF,                    0, //  2  y
        0xDEADBEEF,                    0, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        0xDEADBEEF,                    0, //  5 x z
        0xDEADBEEF,                    0, //  6  yz
        0xDEADBEEF,                    0, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        0xDEADBEEF,                    0, //  9 x  w
        0xDEADBEEF,                    0, // 10  y w
        0xDEADBEEF,                    0, // 11 xy w
        0xDEADBEEF,                    0, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        0xDEADBEEF,                    0, // 15 xyzw

        // 6 point size
        0xDEADBEEF,                    0, //  0 none
        NV056_SET_POINT_SIZE,          1, //  1 x
        0xDEADBEEF,                    0, //  2  y
        0xDEADBEEF,                    0, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        0xDEADBEEF,                    0, //  5 x z
        0xDEADBEEF,                    0, //  6  yz
        0xDEADBEEF,                    0, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        0xDEADBEEF,                    0, //  9 x  w
        0xDEADBEEF,                    0, // 10  y w
        0xDEADBEEF,                    0, // 11 xy w
        0xDEADBEEF,                    0, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        0xDEADBEEF,                    0, // 15 xyzw

        // 7 texture 0
        0xDEADBEEF,                    0, //  0 none
        0xDEADBEEF,                    0, //  1 x
        0xDEADBEEF,                    0, //  2  y
        NV056_SET_TEXCOORD0_2F(0),     2, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        NV056_SET_TEXCOORD0_2F(0),     2, //  5 x z
        NV056_SET_TEXCOORD0_2F(0),     2, //  6  yz
        0xDEADBEEF,                    0, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        NV056_SET_TEXCOORD0_2F(0),     2, //  9 x  w
        NV056_SET_TEXCOORD0_2F(0),     2, // 10  y w
        0xDEADBEEF,                    0, // 11 xy w
        NV056_SET_TEXCOORD0_2F(0),     2, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        NV056_SET_TEXCOORD0_4F(0),     4, // 15 xyzw

        // 8 texture 1
        0xDEADBEEF,                    0, //  0 none
        0xDEADBEEF,                    0, //  1 x
        0xDEADBEEF,                    0, //  2  y
        NV056_SET_TEXCOORD1_2F(0),     2, //  3 xy
        0xDEADBEEF,                    0, //  4   z
        NV056_SET_TEXCOORD1_2F(0),     2, //  5 x z
        NV056_SET_TEXCOORD1_2F(0),     2, //  6  yz
        0xDEADBEEF,                    0, //  7 xyz
        0xDEADBEEF,                    0, //  8    w
        NV056_SET_TEXCOORD1_2F(0),     2, //  9 x  w
        NV056_SET_TEXCOORD1_2F(0),     2, // 10  y w
        0xDEADBEEF,                    0, // 11 xy w
        NV056_SET_TEXCOORD1_2F(0),     2, // 12   zw
        0xDEADBEEF,                    0, // 13 x zw
        0xDEADBEEF,                    0, // 14  yzw
        NV056_SET_TEXCOORD1_4F(0),     4, // 15 xyzw
};

#endif  // NVARCH >= 0x010

