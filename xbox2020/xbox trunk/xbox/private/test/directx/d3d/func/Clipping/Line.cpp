#include "d3dlocus.h"
#include "cd3dtest.h"
#include "dxlegacy.h"
#include "3dmath.h"
#include "Clipping.h"


D3DVERTEX Line::m_pLineVertices[10] = {
	D3DVERTEX(cD3DVECTOR(-0.95f, 0.00f, 0.f), Normalize(cD3DVECTOR( 0.f, 1.f, 1.f)), 0.f, 0.f),
	D3DVERTEX(cD3DVECTOR( 0.95f, 0.00f, 0.f), Normalize(cD3DVECTOR( 1.f, 0.f, 1.f)), 0.f, 0.f),

	D3DVERTEX(cD3DVECTOR( 0.00f, 0.00f, 0.f), Normalize(cD3DVECTOR( 0.f, 1.f, 1.f)), 0.f, 0.f),
	D3DVERTEX(cD3DVECTOR( 0.95f, 0.00f, 0.f), Normalize(cD3DVECTOR( 1.f, 0.f, 1.f)), 0.f, 0.f),

	D3DVERTEX(cD3DVECTOR( 0.00f, 0.00f, 0.f), Normalize(cD3DVECTOR( 0.f, 1.f, 1.f)), 0.f, 0.f),
	D3DVERTEX(cD3DVECTOR( 0.65f, 0.00f, 0.f), Normalize(cD3DVECTOR( 1.f, 0.f, 1.f)), 0.f, 0.f),

	D3DVERTEX(cD3DVECTOR(-0.95f, 0.00f, 0.f), Normalize(cD3DVECTOR( 0.f, 1.f, 1.f)), 0.f, 0.f),
	D3DVERTEX(cD3DVECTOR( 0.00f, 0.00f, 0.f), Normalize(cD3DVECTOR( 1.f, 0.f, 1.f)), 0.f, 0.f),

	D3DVERTEX(cD3DVECTOR(-0.65f, 0.00f, 0.f), Normalize(cD3DVECTOR( 0.f, 1.f, 1.f)), 0.f, 0.f),
	D3DVERTEX(cD3DVECTOR( 0.00f, 0.00f, 0.f), Normalize(cD3DVECTOR( 1.f, 0.f, 1.f)), 0.f, 0.f),
};



Line::Line()
{
    m_pInputVertices = 0;
    m_pRenderVertices = 0;
    m_dwVertices = 2;

    m_szTestName = TEXT("Line clipping");
    m_szCommandKey = TEXT("line");
    
    m_dwRotations = 7;
}

Line::~Line()
{
    if (m_pRenderVertices)
        delete [] m_pRenderVertices;
}

UINT Line::TestInitialize()
{
    m_pRenderVertices = new BYTE [(3 + 3 + 8*2)*sizeof(float)*m_dwVertices];
    if (m_pRenderVertices == 0)
    {
        WriteToLog("%s: Can't allocate memory for vertices\n", m_szTestName);
        return D3DTESTINIT_ABORT;
    }

    // Total tests:     
    // -triangle:       5
    // -API:            m_dwRPFullDX7APIListSize (?) * frequency (2) 
    // -FVF:            2
    // -properties:     7
    // -primitive type: 2

#ifdef UNDER_XBOX
    if (GetStartupContext() & TSTART_STRESS) {
        m_dwTotalAPIs = m_dwVBAPIListSize * 2;
        m_dwTotalTests = 5 * m_dwTotalAPIs * 2 * 7 * 2; // (?)

        SetAPI(m_pVBAPIList, m_dwVBAPIListSize, 2*5);
    }
    else {
#endif
        m_dwTotalAPIs = m_dwRPFullDX8APIListSize * 2;
        m_dwTotalTests = 5 * m_dwTotalAPIs * 2 * 7 * 2; // (?)

        SetAPI(m_pRPFullDX8APIList, m_dwRPFullDX8APIListSize, 2*5);
#ifdef UNDER_XBOX
    }
#endif

    return Clipping::TestInitialize();
}

bool Line::TestTerminate(void)
{
    if (m_pRenderVertices)
    {
        delete [] m_pRenderVertices;
        m_pRenderVertices = NULL;
    }
    return true;
}



bool Line::ResolveTestNumber()
{
    DWORD   dwPrimitiveType;
    DWORD   num = m_dwCurrentTestNumber - 1;
    m_dwCurrentLine = num % 5;              num /= 5;
    m_dwCurrentAPI = num % m_dwTotalAPIs;   num /= m_dwTotalAPIs;
    m_dwCurrentFVF = num % 2;               num /= 2;
    m_dwCurrentProperties = num % 7;        num /= 7;
    dwPrimitiveType = num % 2;              num /= 2;

    // Resolve current line
    m_pInputVertices = &m_pLineVertices[2 * m_dwCurrentLine];
    
    // Resolve current FVF
    if (m_dwCurrentFVF == 0)        m_dwCurrentFVF = D3DFVF_XYZ | D3DFVF_NORMAL;
    else                            m_dwCurrentFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
    
    // Add specular to the FVF
    if ((m_dwCurrentFVF & D3DFVF_DIFFUSE) && (m_dwCurrentProperties == CP_SPECULAR || m_dwCurrentProperties == CP_FOG))
        m_dwCurrentFVF |= D3DFVF_SPECULAR;

    // Add texture to the FVF
    if (m_dwCurrentProperties == CP_TEXTURE)    m_dwCurrentFVF |= 1 << D3DFVF_TEXCOUNT_SHIFT;
    if (m_dwCurrentProperties == CP_MULTITEX)   m_dwCurrentFVF |= (m_dwMaxTextures) << D3DFVF_TEXCOUNT_SHIFT;

    // Primitive type
    if (dwPrimitiveType == 0)       m_dwCurrentPrimitiveType = D3DPT_LINELIST;
    else                            m_dwCurrentPrimitiveType = D3DPT_LINESTRIP;

    return Clipping::ResolveTestNumber();
}


