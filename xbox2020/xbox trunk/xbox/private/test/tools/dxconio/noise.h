/*******************************************************************************

Copyright (c) 2000 Microsoft Corporation.  All rights reserved.

File Name:

    noise.h

Description:

    Noise functions.

*******************************************************************************/

#ifndef __NOISE_H__
#define __NOISE_H__

#define PRIME_TABLE_ENTRIES     256
#define MAX_OCTAVES             20

namespace DXCONIO {

class CPerlinNoise;
class CPerlinNoise1D;
class CPerlinNoise2D;
class CPerlinNoise3D;

typedef float (CPerlinNoise::* INTERPOLATEPROC)(float f1, float f2, float fBeta);
typedef float (CPerlinNoise1D::* NOISE1DPROC)(int x);
typedef float (CPerlinNoise2D::* NOISE2DPROC)(int x, int y);
typedef float (CPerlinNoise3D::* NOISE3DPROC)(int x, int y, int z);

typedef enum _INTERPOLATIONTYPE {
    INTERPOLATE_LINEAR = 0,
    INTERPOLATE_COSINE = 1,
} INTERPOLATIONTYPE, *PINTERPOLATIONTYPE;

//******************************************************************************
class CPerlinNoise {

protected:

    static UINT         m_puPrimes[3][PRIME_TABLE_ENTRIES];
    float               m_fPersistence;
    UINT                m_uOctaves;
    DWORD               m_dwSeed;
    INTERPOLATEPROC     m_pfnInterpolate;
    BOOL                m_bClamp;
    float               m_fRangeBase;
    float               m_fRangeMagnitude;
    DWORD               m_uOctave;
    struct
    {
        UINT            uPrime1;
        UINT            uPrime2;
        UINT            uPrime3;
    }                   m_plPrimesList[MAX_OCTAVES];

public:

                        CPerlinNoise(float fPersistence, UINT uOctaves, DWORD dwSeed, INTERPOLATIONTYPE irp, BOOL bClamp);
                        ~CPerlinNoise();

    void                SetPersistence(float fPersistence);
    void                SetOctaves(UINT uOctaves);
    void                SetSeed(DWORD dwSeed);
    void                SetInterpolation(INTERPOLATIONTYPE irp);
    void                EnableClamp(BOOL bEnable);
    void                SetRange(float fMin, float fMax);

protected:

    float               InterpolateLinear(float f1, float f2, float fBeta);
    float               InterpolateCosine(float f1, float f2, float fBeta);
    DWORD               Rand32(DWORD dwSeed);
    BOOL                IsPrime(UINT u);
    void                InitPrimesList(UINT uOctaves, DWORD dwSeed);
};

//******************************************************************************
class CPerlinNoise1D : public CPerlinNoise {

protected:

    NOISE1DPROC         m_pfnNoise;

public:

                        CPerlinNoise1D(float fPersistence, UINT uOctaves, DWORD dwSeed, INTERPOLATIONTYPE irp, BOOL bClamp, BOOL bSmooth);
                        ~CPerlinNoise1D();

    float               GetIntensity(float x);
    void                EnableSmoothing(BOOL bEnable);

protected:

    float               Noise1D(int x);
    float               SmoothNoise1D(int x);
    float               InterpolatedNoise1D(float x);
};

//******************************************************************************
class CPerlinNoise2D : public CPerlinNoise {

protected:

    NOISE2DPROC         m_pfnNoise;

public:

                        CPerlinNoise2D(float fPersistence, UINT uOctaves, DWORD dwSeed, INTERPOLATIONTYPE irp, BOOL bClamp, BOOL bSmooth);
                        ~CPerlinNoise2D();

    float               GetIntensity(float x, float y);
    void                EnableSmoothing(BOOL bEnable);

protected:

    float               Noise2D(int x, int y);
    float               SmoothNoise2D(int x, int y);
    float               InterpolatedNoise2D(float x, float y);
};

//******************************************************************************
class CPerlinNoise3D : public CPerlinNoise {

protected:

    NOISE3DPROC         m_pfnNoise;

public:

                        CPerlinNoise3D(float fPersistence, UINT uOctaves, DWORD dwSeed, INTERPOLATIONTYPE irp, BOOL bClamp, BOOL bSmooth);
                        ~CPerlinNoise3D();

    float               GetIntensity(float x, float y, float z);
    void                EnableSmoothing(BOOL bEnable);

protected:

    float               Noise3D(int x, int y, int z);
    float               SmoothNoise3D(int x, int y, int z);
    float               InterpolatedNoise3D(float x, float y, float z);
};

} // namespace DXCONIO

#endif // __NOISE_H__
