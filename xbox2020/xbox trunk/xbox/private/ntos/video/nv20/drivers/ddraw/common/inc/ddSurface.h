// **************************************************************************
//
//       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.
//
//     NOTICE TO USER:   The source code  is copyrighted under  U.S. and
//     international laws.  Users and possessors of this source code are
//     hereby granted a nonexclusive,  royalty-free copyright license to
//     use this code in individual and commercial software.
//
//     Any use of this source code must include,  in the user documenta-
//     tion and  internal comments to the code,  notices to the end user
//     as follows:
//
//       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.
//
//     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY
//     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  "AS IS"
//     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-
//     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,
//     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-
//     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL
//     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INDIRECT,  INCI-
//     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-
//     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION
//     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF
//     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.
//
//     U.S. Government  End  Users.   This source code  is a "commercial
//     item,"  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),
//     consisting  of "commercial  computer  software"  and  "commercial
//     computer  software  documentation,"  as such  terms  are  used in
//     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-
//     ment only as  a commercial end item.   Consistent with  48 C.F.R.
//     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),
//     all U.S. Government End Users  acquire the source code  with only
//     those rights set forth herein.
//
// **************************************************************************
//
//  Module: ddSurface.h
//    Definition file for:
//       ddsurf.c
//
// **************************************************************************
//
// History:
//       Paul van der Kouwe 06/16/99 - created.
//
// **************************************************************************

#ifndef _DDSURFACE_H_
#define _DDSURFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

// macros

#define SET_GBL_SURFACE_DATA(pDDSLcl, flags, bits, rmask, gmask, bmask, amask)  \
{                                                                               \
    pDDSLcl->lpGbl->ddpfSurface.dwFlags = (flags);                              \
    pDDSLcl->lpGbl->ddpfSurface.dwRGBBitCount = (bits);                         \
    pDDSLcl->lpGbl->ddpfSurface.dwRBitMask = (rmask);                           \
    pDDSLcl->lpGbl->ddpfSurface.dwGBitMask = (gmask);                           \
    pDDSLcl->lpGbl->ddpfSurface.dwBBitMask = (bmask);                           \
    pDDSLcl->lpGbl->ddpfSurface.dwRGBAlphaBitMask = (amask);                    \
}

// helper routines
#ifndef WINNT
void  getDisplayDuration (void);
#endif
BOOL  nvCalculateColorKey (DWORD *pColorKey, LPDDRAWI_DDRAWSURFACE_LCL pLcl, DWORD dwFormat);
DWORD nvCalculateSurfaceParams (LPDDRAWI_DDRAWSURFACE_LCL pDDSLcl,
                                DWORD *pFormat, BOOL *bFourCC,
                                DWORD *pWidth, DWORD *pHeight, DWORD *pDepth, DWORD *dwMultiSampleBits,
                                DWORD *pBPPRequested, DWORD *pBPPGranted,
                                DWORD *pPitch, DWORD *pSlicePitch, BOOL bComputePitch /* rather than extracting it from pDDSLcl */);

// callbacks

DWORD __stdcall DestroySurface32   (LPDDHAL_DESTROYSURFACEDATA lpDestroySurface);
DWORD __stdcall CreateSurface32    (LPDDHAL_CREATESURFACEDATA lpCreateSurface);
DWORD __stdcall CanCreateSurface32 (LPDDHAL_CANCREATESURFACEDATA lpCanCreateSurface);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _DDSURFACE_H_
