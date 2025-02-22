// FILE:        quad.cpp
// DESC:        TL vertex clip conformance tests (quad)

//#define D3D_OVERLOADS
#include "d3dlocus.h"
#include "cd3dtest.h"
#include "TLVertexClip.h"

// NAME:        CTLVertexClipQuad()
// DESC:        TL vertex clip quad class constructor
// INPUT:       none
// OUTPUT:      none

CTLVertexClipQuad::CTLVertexClipQuad()
{
	m_nTests = QUAD_TESTS;
	m_szTestName = TEXT("TLVertexClip Quad");
	m_szCommandKey = TEXT("Quad");
}

// NAME:        ~CTLVertexClipQuad()
// DESC:        TL vertex clip quad class destructor
// INPUT:       none
// OUTPUT:      none

CTLVertexClipQuad::~CTLVertexClipQuad()
{
}

// NAME:        SetEndPoints()
// DESC:        set end points
// INPUT:       A........end point
//              B........end point
//              uTest....test index
// OUTPUT:      none
// COMMENTS:    end points define lines thru viewport from/to each quadrant

void CTLVertexClipQuad::SetEndPoints(D3DVECTOR *A, D3DVECTOR *B, UINT uTest)
{
	UINT i = uTest % (4*POINTS_PER_SIDE);
	UINT j = uTest / (4*POINTS_PER_SIDE);

	D3DVECTOR Start = cD3DVECTOR(PxFromTest(i), PyFromTest(i), 0.0f);
	D3DVECTOR End = cD3DVECTOR(PxFromTest(j), PyFromTest(j), 0.0f);

	*A = Start;
	*B = End;
}
