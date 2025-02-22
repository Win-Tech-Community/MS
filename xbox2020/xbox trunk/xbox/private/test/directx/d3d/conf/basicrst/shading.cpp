//#define D3D_OVERLOADS
#include "d3dlocus.h"
#include "cd3dtest.h"
#include "3dmath.h"
#include "BasicRst.h"

//************************************************************************
// Shading Test functions

CShadingTest::CShadingTest()
{
	m_szTestName = TEXT("BasicRst Shading");
	m_szCommandKey = TEXT("Shading");
}

CShadingTest::~CShadingTest()
{
}

UINT CShadingTest::TestInitialize(void)
{
//    UINT n = m_pMode->nSrcDevice;

	// Setup the Test range
	SetTestRange(1,SHADING_TESTS);

	// Check the caps we are interested in
	DWORD dwShadeCaps = m_d3dcaps.ShadeCaps;

	// Check the appropriate Shade caps
//	if ((m_dwVersion <= 0x0700) && !(dwShadeCaps & D3DPSHADECAPS_COLORFLATRGB))
//	{
//		WriteToLog("Device capability not supported: Shade Flat.\n");
//		return D3DTESTINIT_ABORT;
//	}

	if (!(dwShadeCaps & D3DPSHADECAPS_COLORGOURAUDRGB))
	{
		WriteToLog("Device capability not supported: Shade Gouraud.\n");
		return D3DTESTINIT_ABORT;
	}

    // Tell RenderPrimitive disable API cycling
    // m_dwPrimitives = 1; should be changed to something like 
    // SetAPI(RP_DP);

	return D3DTESTINIT_RUN;
}

bool CShadingTest::ExecuteTest(UINT uTestNum)
{
	// Initialize some variables
 	dwVertexCount = 0;
	msgString[0] = '\0';

	// Set the appropriate renderstate
	if (uTestNum <= 7)
	{
		sprintf(msgString, "%sFlat, ", msgString);
		SetRenderState(D3DRENDERSTATE_SHADEMODE, (DWORD)D3DSHADE_FLAT);

		// Let's build some triangles.
		switch (uTestNum)
		{
			case (1):
				DrawShadeListTests(0);
				sprintf(msgString, "%sEight triangles (Yellow)", msgString);
				break;
			case (2):
				DrawShadeListTests(1);
				sprintf(msgString, "%sEight triangles (Red)", msgString);
				break;
			case (3):
				DrawShadeListTests(2);
				sprintf(msgString, "%sEight triangles (Blue)", msgString);
				break;
			case (4):
				DrawShadeListTests(3);
				sprintf(msgString, "%sEight triangles (Green)", msgString);
				break;
			case (5):
				DrawShadeListTests(4);
				sprintf(msgString, "%sEight triangles (Blue)", msgString);
				break;
			case (6):
				DrawShadeStripTests();
				sprintf(msgString, "%sMulticolor Triangle Strip", msgString);
				break;
			case (7):
				DrawShadeFanTests();
				sprintf(msgString, "%sMulticolor Triangle Fan", msgString);
				break;
		}
	}
	else
	{
		sprintf(msgString, "%sGouraud, ", msgString);
		SetRenderState(D3DRENDERSTATE_SHADEMODE, (DWORD)D3DSHADE_GOURAUD);

		// Let's build some triangles.
		switch (uTestNum-7)
		{
			case (1):
				DrawShadeListTests(0);
				sprintf(msgString, "%sEight triangles (Yellow)", msgString);
				break;
			case (2):
				DrawShadeListTests(1);
				sprintf(msgString, "%sEight triangles (Red, Green, & Blue)", msgString);
				break;
			case (3):
				DrawShadeListTests(2);
				sprintf(msgString, "%sEight triangles (Red & Blue)", msgString);
				break;
			case (4):
				DrawShadeListTests(3);
				sprintf(msgString, "%sEight triangles (Green & Red)", msgString);
				break;
			case (5):
				DrawShadeListTests(4);
				sprintf(msgString, "%sEight triangles (Blue & Green)", msgString);
				break;
			case (6):
				DrawShadeStripTests();
				sprintf(msgString, "%sMulticolor Triangle Strip", msgString);
				break;
			case (7):
				DrawShadeFanTests();
				sprintf(msgString, "%sMulticolor Triangle Fan", msgString);
				break;
		}
	}

	// Tell the log that we are starting
	BeginTestCase(msgString);

    return true;
}

void CShadingTest::SceneRefresh(void)
{
	if (BeginScene())
	{
		// Render the data.
		if (PrimType == D3DPT_TRIANGLELIST)
		{
			RenderPrimitive(PrimType,D3DFVF_TLVERTEX,VertexList,dwVertexCount,NULL,0,0);
		}
		else
		{
			RenderPrimitive(PrimType,D3DFVF_TLVERTEX,VertexList,dwVertexCount,NULL,0,0);
			RenderPrimitive(PrimType,D3DFVF_TLVERTEX,Single1List,3,NULL,0,0);
			RenderPrimitive(PrimType,D3DFVF_TLVERTEX,Single2List,3,NULL,0,0);
			RenderPrimitive(PrimType,D3DFVF_TLVERTEX,Single3List,3,NULL,0,0);
		}

		EndScene();
	}	
}

//************************************************************************
// Internal API:    DrawShadeTests
//
// Purpose:         
//
// Return:          None.
//************************************************************************

void CShadingTest::DrawShadeListTests(int nTest)
{
	// Color of triangles
	D3DCOLOR Color1[] = { RGBA_MAKE(255,255,0,255),	// Yellow
						  RGBA_MAKE(255,0,0,255),	// Red
						  RGBA_MAKE(0,0,255,255),	// Blue
						  RGBA_MAKE(0,255,0,255),	// Green
						  RGBA_MAKE(0,0,255,255) };	// Blue

	D3DCOLOR Color2[] = { RGBA_MAKE(255,255,0,255),	// Yellow
						  RGBA_MAKE(0,255,0,255),	// Green
						  RGBA_MAKE(255,0,0,255),	// Red
						  RGBA_MAKE(255,0,0,255),	// Red
						  RGBA_MAKE(0,0,255,255) };	// Blue

	D3DCOLOR Color3[] = { RGBA_MAKE(255,255,0,255),	// Yellow
						  RGBA_MAKE(0,0,255,255),	// Blue
						  RGBA_MAKE(255,0,0,255),	// Red
						  RGBA_MAKE(0,255,0,255),	// Green
						  RGBA_MAKE(0,255,0,255) };	// Green

	// Set the Triangle Primitive Type to List
	PrimType = D3DPT_TRIANGLELIST;

	// Right Angled with Left and Top
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 10.0f,10.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color1[nTest], 0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 90.0f,10.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color2[nTest], 0, 1.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 10.0f,90.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color3[nTest], 0, 0.0f,1.0f);
				
	// Right Angled with Left and Bottom
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 100.0f,10.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color1[nTest], 0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 180.0f,90.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color2[nTest], 0, 1.0f,1.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 100.0f,90.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color3[nTest], 0, 0.0f,1.0f);
				
	// Equaladiral with edge on Left
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 190.0f,10.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color1[nTest], 0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 270.0f,50.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color2[nTest], 0, 1.0f,0.5f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 190.0f,90.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color3[nTest], 0, 0.0f,1.0f);
				
	// Right Angled with Right and Top
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 10.0f,100.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color1[nTest], 0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 90.0f,100.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color2[nTest], 0, 1.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 90.0f,180.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color3[nTest], 0, 1.0f,1.0f);
				
	// Right Angled with Right and Bottom
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 180.0f,180.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color1[nTest], 0, 1.0f,1.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 100.0f,180.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color2[nTest], 0, 0.0f,1.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 180.0f,100.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color3[nTest], 0, 1.0f,0.0f);
				
	// Equaladiral with edge on Right
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 270.0f,180.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color1[nTest], 0, 1.0f,1.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 190.0f,140.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color2[nTest], 0, 0.0f,0.5f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 270.0f,100.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color3[nTest], 0, 1.0f,0.0f);
				
	// Equaladiral with edge on Top
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 50.0f,270.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color1[nTest], 0, 0.5f,1.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 10.0f,190.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color2[nTest], 0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 90.0f,190.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color3[nTest], 0, 1.0f,0.0f);
				
	// Equaladiral with edge on Bottom
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 180.0f,270.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color1[nTest], 0, 1.0f,1.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 100.0f,270.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color2[nTest], 0, 0.0f,1.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 140.0f,190.0f + (float)m_vpTest.Y,0.9f),(1.0f / 0.9f), Color3[nTest], 0, 0.5f,0.0f);
}

void CShadingTest::DrawShadeStripTests(void)
{
	// Set the Triangle Primitive Type to Strip
	PrimType = D3DPT_TRIANGLESTRIP;

	// Multicolor Mesh
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X +  32.0f,170.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,0,0,255),  0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X +  32.0f, 30.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,128,0,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X +  83.2f,170.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(128,128,0,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 134.4f, 30.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(128,255,0,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 185.6f,170.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,128,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 236.8f, 30.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,128,128,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 288.0f,170.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,128,255,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 288.0f, 30.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,0,255,255),  0, 0.0f,0.0f);

	// Single TriStrip
	Single1List[0] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X +  67.0f,200.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,0,0,255),0, 0.0f,0.0f);
	Single1List[1] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 102.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,0,255),0, 0.0f,0.0f);
	Single1List[2] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X +  32.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,0,255,255),0, 0.0f,0.0f);

	// Single TriStrip
	Single2List[0] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 195.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,0,255),0, 0.0f,0.0f);
	Single2List[1] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 125.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,0,255,255),0, 0.0f,0.0f);
	Single2List[2] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 160.0f,200.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,0,0,255),0, 0.0f,0.0f);

	// Single TriStrip
	Single3List[0] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 218.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,0,255,255),0, 0.0f,0.0f);
	Single3List[1] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 253.0f,200.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,0,0,255),0, 0.0f,0.0f);
	Single3List[2] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 288.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,0,255),0, 0.0f,0.0f);
}

void CShadingTest::DrawShadeFanTests(void)
{
	// Set the Triangle Primitive Type to Fan
	PrimType = D3DPT_TRIANGLEFAN;

	// Multicolor Mesh
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X +  10.0f,140.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,0,0,255),  0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 150.0f, 10.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,128,0,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 150.0f, 62.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(128,255,0,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 150.0f,114.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,0,255),  0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 150.0f,166.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,128,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 150.0f,218.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,128,255,255),0, 0.0f,0.0f);
	VertexList[dwVertexCount++] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 150.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,0,255,255),  0, 0.0f,0.0f);

	// Single TriFan
	Single1List[0] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 240.0f, 10.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,0,0,255),0, 0.0f,0.0f);
	Single1List[1] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 280.0f, 90.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,0,255),0, 0.0f,0.0f);
	Single1List[2] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 200.0f, 90.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,0,255,255),0, 0.0f,0.0f);

	// Single TriFan
	Single2List[0] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 280.0f,180.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,0,255),0, 0.0f,0.0f);
	Single2List[1] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 200.0f,180.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,0,255,255),0, 0.0f,0.0f);
	Single2List[2] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 240.0f,100.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,0,0,255),0, 0.0f,0.0f);

	// Single TriFan
	Single3List[0] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 200.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,0,255,255),0, 0.0f,0.0f);
	Single3List[1] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 240.0f,190.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(255,0,0,255),0, 0.0f,0.0f);
	Single3List[2] = cD3DTLVERTEX(cD3DVECTOR((float)m_vpTest.X + 280.0f,270.0f + (float)m_vpTest.Y, 0.5f), (1.0f / 0.5f), RGBA_MAKE(0,255,0,255),0, 0.0f,0.0f);
}