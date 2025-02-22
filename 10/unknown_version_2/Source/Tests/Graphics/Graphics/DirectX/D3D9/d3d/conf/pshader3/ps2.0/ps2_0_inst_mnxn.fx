E MapReserve
    );

NTSTATUS
PnprRecopyMirrorPages (
    VOID
    );

//
// Define an IA64 RSE flush routine that is available in the kernel but not in
// the headers.
//

#if defined(_IA64_)

VOID
RtlpFlushRSE (
    OUT PULONGLONG BackingStore,
    OUT PULONGLONG RNat
    );

#endif

extern KEVENT PnpReplaceEvent;

﻿<?xml version='1.0' encoding='utf-8' standalone='yes'?>
<Content xmlns="http://microsoft.com/schemas/Windows/Kits/Manifest">
  <ContentGroup
      BuildArchitecture="each"
      Destination="$(_BuildArch)"
      >
    <FeatureReference Name="Device.Graphics"/>
    <BinaryFile
        Destination="nttest\windowstest\graphics\d3d\conf"
        Name="DXGIHybridPresentModern.exe"
        Source="$(OBJ_PATH)\$(O)"
        />
  </ContentGroup>
</Content>

//////////////////////////////////////////////////////////////////////
// File:  DXGIPresent.h
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// Purpose:
// Interfaces for the DXGI present test.
//
// History:
// ?? ??? ????  AndrewLu  Created.
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// Build flags
//
/////////////////////////////////////////////////////////////////

#ifndef DXGIPRESENT_H_INCLUDED
#define DXGIPRESENT_H_INCLUDED


/////////////////////////////////////////////////////////////////
//
// Includes
//
/////////////////////////////////////////////////////////////////

//
// Win32 headers
//

#include <windows.h>
#include <basetsd.h>
#include <dwmapi.h>
#include <dwmapip.h>


//
// Direct3D headers
//
#include <d3d11_2.h>

#include <d3d10_1.h>
#include <d3dx10.h>

//
// STL headers
//

#include <vector>
#include <algorithm>


//
// Framework headers
//

#include <WGFTestCore.h>
#include <WGFTestUI.h>

#include <DXGITest.h>
#include <D3DWrappers.h>


//
// Project headers
//

#include "Adapter.h"
#include "DXGIBufferCompare.h"

#include "DXGIWndClass.h"
#include "DXGISurfUtils.h"
#include "DXGISwapEffects.h"
#include "DXGISwapChainFlag.h"
#include "DXGIPresentFlagRecord.h"
#include "D3D10RefUtil.h"
#include "EnumModesGDI.h"

#include "WindowTree.h"
#include <RegionHelper.h>

#include "D3D10SwapChain.h"
#include "DeviceWrapper10.h"
#include "DeviceWrapper11.h"

#include "ModeSet.h"
#include "scrollinfo.h"
#include "DCOMPIsolation.h"

#include <wincodec.h>
#include "Handle.h"
#include "BBDims.h"
#include "WGFHelpers.h"

using HelperType::Vector2D;
using WindowsTest::CHandle;
using namespace testfactor;

/////////////////////////////////////////////////////////////////
//
// Constants
//
/////////////////////////////////////////////////////////////////

#define MAX_WINDOWS 255
#define MAX_MODES_PER_OUTPUT 256
#define MAX_OUTPUTS 4
#define MAX_ADAPTERS 4
#define MAX_TEXTURES 4
#define MAX_DISPLAYMODES MAX_MODES_PER_OUTPUT * MAX_OUTPUTS * MAX_ADAPTERS
#define MAX_PRESENT_RETRY_COUNT 3

/////////////////////////////////////////////////////////////////
//
// Type definitions
//
/////////////////////////////////////////////////////////////////

//
// Direct3D version-specific type wrappers
//

typedef CDeviceWrapper10 CDeviceWrapper;
typedef CSwapChainWrapper10 CSwapChainWrapper;

typedef struct _RELATIVEGETDSDDIMS
{
	float fWidthFactor;
	float fHeightFactor;
} RELATIVEGETDSDDIMS;


typedef union
{
	struct
	{
		BYTE red;
		BYTE green;
		BYTE blue;
		BYTE alpha;
	};
	DWORD color;
} MYD3DCOLOR;


/////////////////////////////////////////////////////////////////
//
// Globals
//
/////////////////////////////////////////////////////////////////

extern DXGI_FORMAT GetDSDDestFormats[];
extern const UINT cuiNoOfGetDSDDestFormats;
extern RELATIVEGETDSDDIMS RelativeGetDSDDims[];
extern const UINT cuiNoOfDSDDims;

unsigned FlipFlags(const Vector2D<float>&);
unsigned RotateFlags(DXGI_MODE_ROTATION);

/////////////////////////////////////////////////////////////////
//
// Interfaces
//
/////////////////////////////////////////////////////////////////

class CDXGIPresentSingleSC
	:
	public CDXGITest,
	public clsBasicWindowClass,
	public CTestDXGISurfaceUtils,
	public clsD3D10Ref,
	public clsEnumModesGDI
{
	//
	// Construction/destruction
	//

public:
	CDXGIPresentSingleSC();

	virtual ~CDXGIPresentSingleSC();

	HRESULT ActivateWindow(HWND hWindow);
	bool UpdateOutputWindowInformation(
		IDXGISwapChain *pSwapChain,
		WINDOWINFO deviceWindowInfo,
		DXGI_MODE_ROTATION = DXGI_MODE_ROTATION_IDENTITY);

	HRESULT CreateTextures(
		DXGI_FORMAT bbFormat,
		UINT windowWidth,
		UINT windowHeight,
		UINT displayWidth,
		UINT displayHeight,
		UINT numberOfBuffers);

	void ReleaseTextures();
	bool InitializeLockableTexture
		(
		ID3DTexture2D * pTex
		);
	bool CheckLockableTexture
		(
		ID3DTexture2D * pTex,
		UINT * pDiscrepancyCount
		);
	void ReleaseTestCaseObjects();
	virtual bool PerformPresent( IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags );
	bool GetDisplaySurfaceData(
		IDXGISurface *pGetDSDSurface,
		bool bMSSwapChain,
		bool isWindowed );

	bool EvaluatePresentedImage
		(
		__in ID3DTexture2D * pSrcTexture2D,
		__in ID3DTexture2D * pRefTexture2D,
		__out_opt float * pNonConformanceFraction,
		__in_opt bool bVerbose = true,
		__out_opt HRESULT* phr = NULL
		);

	bool EvaluatePresentedImage
	    (
	    __in ID3DTexture2D* pSrcTexture2D,
	    __in ID3DTexture2D* pRefTexture2D,
	    __out_opt float* pNonConformanceFraction,
	    bool bVerbose,
	    __out_opt HRESULT* phr,
	    const Vector2D<int>&,
	    DXGI_MODE_ROTATION
	    );

	HRESULT InitializeBackBuffer
		(
		CSwapChainWrapper* pSwapchainWrapper,
		UINT textureIndex,
		const Vector2D<unsigned>* = nullptr
		);

        HRESULT InitializeBackBufferWithDirtyRects
                (
                CDeviceWrapper10* pDeviceWrapper,
                CSwapChainWrapper* pSwapchainWrapper,
                UINT textureIndex,
                RGNDATA* pDirtyData
                );

	HRESULT LinearToGamma
		(
		ID3DTexture2D * pResource
		);

	HRESULT MaskAlphaChannel
		(
		ID3DTexture2D * pResource
		);

	HRESULT DrawRect
		(
		ID3DTexture2D * pResource,
		UINT x,
		UINT y,
		UINT width,
		UINT height,
		MYD3DCOLOR color
		);

	bool IsSRGB
		(
		DXGI_FORMAT Format
		);

	HRESULT CopyRegion
		(
		__in ID3DTexture2D * pSource,
		__in ID3DTexture2D * pDest,
		__in LPRGNDATA pRegionData,
		__in bool bDisableSRGBConversion
		);

	DXGI_MODE_ROTATION  DisplayOrientationToDxgiModeRotation
		(
		DWORD displayOrientation
		);

	DWORD  DxgiModeRotationToDisplayOrientation
		(
		DXGI_MODE_ROTATION dxgiModeRotation
		);
	HRESULT AdjustForStretchAndRotation(const Vector2D<float>&, DXGI_MODE_ROTATION, CHandle<ID3DTexture2D>&);

	HRESULT CreateTextureAndCopyBackBuffer
		(
		__out ID3DTexture2D ** pDestTexture,
		DXGI_FORMAT format,
		const Vector2D<unsigned>* = nullptr
		);

	void ProcessMessages();

	//
	// Helper methods
	//
	HRESULT CheckForegroundWindow(LPCTSTR ExpectedClassName);

protected:
	UINT m_iCurrentTestCase;

	std::map< HMONITOR, DEVMODEW > m_DesktopMode;	// original desktop mode, to be restored upon exit

	float m_fMaxNonConformanceFractionWin;
	float m_fMaxNonConformanceFractionFS;
	static const DXGI_FORMAT dxgifmtBBInitTexture;

	static CBufferCompare DXGIBufferCompare;

	clsD3D9Device m_D3D9Device;

	DXGI_FACTORY_POINTER m_FactoryPointer;
	DXGI_ADAPTER_POINTER m_AdapterPointer;

	CDeviceWrapper PrimaryAdapterDevice;

	D3D10_DEVICE_POINTER m_DevicePointer;

	HWND m_hwndFocusWindow;
	HWND m_hwndDeviceWindow;
	DXGI_SWAP_CHAIN_DESC m_SCDesc;
	CSwapChainWrapper TestedSwapChain;
	CSwapChainWrapper TestedSwapChainMS;
	IDXGISwapChain* m_pSwapChain;
	IDXGISwapChain* m_pSwapChainMS;

	// Simplified information about the output and the relationship between the device
	// window and the output.
	//
	// To do: This will have to be revised substantially to accommodate test cases involving
	// multiple outputs and multiple adapters.

	IDXGIOutput *pDeviceWindowOutput;
	WCHAR m_DeviceName[ 32 ];
	UINT uiDeviceOutputWidth;
	UINT uiDeviceOutputHeight;
	RECT rectDeviceWindow;

	ID3DTexture2D *pBBInitTextureSys[MAX_TEXTURES];
	ID3DTexture2D *pBBInitTextureVid[MAX_TEXTURES];
	ID3DShaderResourceView *pBBInitSRV[MAX_TEXTURES];

	float m_fGamma;	// gamma value for sRGB backbuffers
	ID3DTexture2D *m_pGetDSDTexture;
	IDXGISurface *m_pGetDSDSurface;
	ID3DTexture2D *m_pGetDSDTextureMS;
	IDXGISurface *m_pGetDSDSurfaceMS;
	CDCompIsolation m_DCOMPIsolation;

	int iDSDFmtIndex;
	int iDSDDimIndex;
	BOOL m_MultisampleTest;
	DXGI_MODE_ROTATION m_RotationMode;
	BOOL m_bNonPrerotated;
	UINT m_NumberOfPresents;
	BOOL m_UseCurrentDesktopMode;
	UINT m_RequiredFormatSupport;
	RFactor m_globalRFactorDwmOnBpp;
	RFactor m_globalRFactorDwmOffBpp;
	UINT m_ParameterError;
	UINT m_MaxBufferCount;
	UINT m_BufferCount;
	UINT m_TexturesAvailable;
	UINT m_TexturesToLoad;
	DXGIPresentFlagRecord m_PresentFlag;
	DXGISwapEffectRecord m_SwapEffect;
	bool m_ValidateNoExtraBuffers;
	bool m_bUseDirtyRects; // true if we should test dirty rects.
	bool m_tp_bWindowless;       // Test parameter to control Windowed or Windowless (DCOMP) presents.
	SCROLLINGINFO m_ScrollInfo; // Scrolling info.

	std::vector < DXGI_ADAPTER_DESC > m_vecAdapterDescriptors;

	//for diagnostics
	bool m_bLargeMemoryUsage;

protected:
	virtual HRESULT CreateTestWindows
		(
		UINT focusWindowLeft,
		UINT focusWindowTop,
		UINT focusWindowWidth,
		UINT focusWindowHeight
		);

	virtual HRESULT GetMultisampleQualityLevels(
		D3D_DEVICE_POINTER devicePointer,
		__in std::vector< ModeInformation >* pModes,
		__out std::vector< ModeInformation >* pMultisampleIndex,
		UINT maxMultisampleCount,
		UINT maxMultisampleQualityIndex);

	virtual HRESULT GetSupportedFormats(
		D3D_DEVICE_POINTER devicePointer,
		__in std::vector< ModeInformation >* pModes,
		__out std::vector< ModeInformation >* pMultisampleIndex,
		UINT requiredSupport);

	virtual HRESULT CreateAdapterDevice(
		TEST_FEATURE_LEVEL testFeatureLevel,
		UINT adapter,
		D3D_DEVICE_POINTER *pDevicePointer);

    private:
        IWICImagingFactory* imgFactory;
        HRESULT imgFactoryResult;
        HRESULT ImagingFactoryResult() const { return imgFactoryResult; }
        IWICImagingFactory* ImagingFactory()
        {
            if (!imgFactory)
            {
                imgFactoryResult = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(imgFactory), reinterpret_cast<void**>(&imgFactory));
            }
            return imgFactory;
        }
};

template<bool TestSyncTransform> class SyncTransformTest;

template<> class SyncTransformTest<false>
{
    protected:
        Vector2D<int> GetOffset() const { return Vector2D<int>(0, 0); }
        Vector2D<float> GetStretchFactor() const { return Vector2D<float>(1.f, 1.f); }
        DXGI_MODE_ROTATION GetRotation() const { return DXGI_MODE_ROTATION_IDENTITY; }
        bool SetSyncTransform(IDXGISwapChain&, const RECT&){ return true; }
        bool ScaleToWindow() const { return true; }
};

enum class TransformType
{
    None,
    Matrix,
    Rotation,
    SourceSize
};

typedef std::tuple<TransformType, TransformType, TransformType> TransformOrder_t;
tstring ToString(const TransformOrder_t&);
bool FromString(TransformOrder_t*, const tstring &);

#define Param(name, type) private:   CVariationParameter< type >* name; \
                                     void Create##name (CVariationGenerator& c) { c.CreateParameter(_T( #name ), &##name ); } \
                          protected: type Get##name () const { return name##->GetValue(); } \
                                     virtual bool Use##name##() const { return false; } \
                                     typedef type name##_t; \
                                     virtual RFactor Init##name (CVariationParameter< type >&) = 0

template<> class SyncTransformTest<true>
{
    Param(StretchFactor, Vector2D<float>);
    Param(Offset, Vector2D<int>);
    Param(SourceSize, Vector2D<unsigned>);
    Param(Rotation, DXGI_MODE_ROTATION);
    Param(CallOrder, TransformOrder_t);

    protected:
        RFactor InitSyncTransformParams(CVariationGenerator&);
        bool SetSyncTransform(IDXGISwapChain&, const RECT&);
        bool ScaleToWindow() const { return false; }

        static const RECT WindowRect;

    private:
        static void WriteOrderToLog(const TransformOrder_t&);
        void SetTransformTypes(IDXGISwapChain2&, const DXGI_MATRIX_3X2_F&, const TransformOrder_t&);
        static Offset_t AccountForNegativeStretch(const Offset_t&, const StretchFactor_t&, const Vector2D<int>&);
        static DXGI_MATRIX_3X2_F TransformMatrix(const StretchFactor_t&, const Offset_t&, const Rotation_t&, const RECT&);
};

#undef Param

template<bool TestSyncTransform>
class CPresentWinConvertStretch_ : public CDXGIPresentSingleSC, public SyncTransformTest<TestSyncTransform>
{
	//
	// Construction
	//

public:
	CPresentWinConvertStretch_(DXGI_FORMAT RestrictFormat = DXGI_FORMAT_UNKNOWN);

	//
	// Framework override methods
	//

public:
	virtual TEST_RESULT Setup();
	virtual void Cleanup();

	void InitTestParameters();
	virtual void InitTestParametersImpl() = 0;
	virtual void InitModeParameters();

	virtual HRESULT ModeListTransform(
		D3D_DEVICE_POINTER devicePointer,
		__in std::vector< ModeInformation >* pModes,
		__out std::vector< ModeInformation >* pTransformedModes);

	virtual void CleanupTestCase();
	virtual TEST_RESULT ExecuteTestCase();

	HRESULT AdapterAndOutputFromHMon(
		HMONITOR monitor,
		__out UINT* adapterID,
		__out UINT* outputID);

	void Convert(
		__in std::vector<GDI_MONITOR_MODE>* pMonitorModePairs,
		__out std::vector< ModeInformation >* pMultisampleIndex);

	void DisplayModeForRemote();
	bool PerformPresentScrollAndDirtyRects( IDXGISwapChain *pSwapChain, BOOL bUseDirtyRects, bool bDoScrolling, SCROLLINGINFO *pscrollinfo, UINT syncInterval, UINT flags );
	bool ApplyScrollAndDirtyRectsToReferenceImage
		(
		__out ID3DTexture2D * pRefImage,
		__in ID3DTexture2D * pSourceImage,
		__in bool bApplyDirtyRect,
		__in bool bApplyScrolling,
		__in SCROLLINGINFO *pScrollInfo,
		__in bool bDisableSRGBConversion
		);

	bool ScrollRect
		(
		__out ID3D10Texture2D * pFinalImage,
		__in const RECT *pr,
		__in const POINT *pRelocate
		);

	RGNDATA * CreateDualEllipticRegion(int nLeft, int nTop, int nRight, int nBottom);

protected:
	virtual TEST_RESULT CreateDeviceAndSwapChain();
	virtual HRESULT UpdateReferenceTexture();
	virtual HRESULT TransitionAfterPresent(){return 0;};
	virtual HRESULT TransitionBeforePresent(){return 0;};
	virtual bool IsDeviceLost(HRESULT hr);
	virtual TEST_RESULT ReCreateDeviceAndSwapChain();

	//
	// Member data
	//

protected:
	bool m_bDWM;
	int m_OutputModeIndex;
	int m_iBBDimIndex;
	int m_iWindow;
	int m_iLastAdapterOrdinal;
	int m_iLastOutputOrdinal;
	bool m_bStretchBB;	// true if all the stretch tests should be tried
	clsEnumModesGDI::DesktopModeRecord m_DesktopModes[MAX_DISPLAYMODES];
	UINT m_numberOfModes;
	UINT m_numberOfWindowsToTest;
	bool m_adapterNoOutputs;
	clsEnumModesGDI::GDI_MONITOR_MODE TestedMonitorMode;
	ModeInformation m_OutputModeSet[MAX_DISPLAYMODES];
	ModeInformation m_ModeInformation;

	ID3DTexture2D * m_pBackBufferCleared;
	ID3DTexture2D * m_pBackBufferRendered;
	bool m_StartFullScreen;
	HMONITOR m_LastHmon;
	DXGISwapChainFlagRecord m_SwapChainFlags;
	bool m_bExpectDeviceLoss;
	DWORD m_dwPresentTime; // time to present in ms
	bool m_bStopNow;	   // stop presenting if true

private:
    CPresentWinConvertStretch_& operator=(const CPresentWinConvertStretch_&);
    const RELATIVE_BB_DIMS& ScaleFactor() const;
    Vector2D<unsigned> SwapChainDimension() const;
    const RECT& FocusWindowRect() const;
    const DXGI_FORMAT FormatRestriction;
    Vector2D<unsigned>* BBRenderDim(Vector2D<unsigned>&) const;
};

typedef CPresentWinConvertStretch_<false> CPresentWinConvertStretch;

class CPresentWinClippingWindows
	: public CPresentWinConvertStretch
{
public:
	CPresentWinClippingWindows();
	virtual ~CPresentWinClippingWindows();

	//
	// Framework override methods
	//
	virtual TEST_RESULT Setup();
	// virtual void Cleanup();
	virtual void CleanupTestCase();
	virtual TEST_RESULT ExecuteTestCase();
    void InitTestParametersImpl();

protected:
	virtual TEST_RESULT CreateDeviceAndSwapChain();

	HRESULT CreateTestWindows(
		UINT focusWindowLeft,
		UINT focusWindowTop,
		UINT focusWindowWidth,
		UINT focusWindowHeight);

	virtual HRESULT UpdateReferenceTexture();


private:
	WindowTree m_WindowTree;
	RECT m_ClippingWindows;
	static const COLORREF m_ClippingColor = 0xffffff;
};

class CPresentWinChildWindows
	: public CPresentWinConvertStretch
{
public:
	CPresentWinChildWindows();
	virtual ~CPresentWinChildWindows();

	//
	// Framework override methods
	//
	virtual TEST_RESULT Setup();
	// virtual void Cleanup();
	virtual void CleanupTestCase();
	virtual TEST_RESULT ExecuteTestCase();
    void InitTestParametersImpl();

protected:
	virtual TEST_RESULT CreateDeviceAndSwapChain();

	HRESULT CreateTestWindows(
		UINT focusWindowLeft,
		UINT focusWindowTop,
		UINT focusWindowWidth,
		UINT focusWindowHeight);

private:
	WindowTree m_WindowTree;
	RECT m_ChildWindows;
	static const COLORREF m_ClippingColor = 0xffffff;
};

class CPresentWinScrollAndDirtyRects
	: public CPresentWinConvertStretch
{
public:
	CPresentWinScrollAndDirtyRects();
	virtual ~CPresentWinScrollAndDirtyRects();

	//
	// Framework override methods
	//
	virtual TEST_RESULT Setup();
	// virtual void Cleanup();
	void InitTestParametersImpl();
	virtual void CleanupTestCase();
	virtual TEST_RESULT ExecuteTestCase();


protected:
	virtual TEST_RESULT CreateDeviceAndSwapChain();

	HRESULT CreateTestWindows(
		UINT focusWindowLeft,
		UINT focusWindowTop,
		UINT focusWindowWidth,
		UINT focusWindowHeight);

	virtual HRESULT UpdateReferenceTexture();


private:
	WindowTree m_WindowTree;
	RECT m_ClippingWindows;
	static const COLORREF m_ClippingColor = 0xffffff;
};


class CPresentWinConvertStretchMS
	:
	public CPresentWinConvertStretch
{
	//
	// Construction/destruction
	//

public:
	CPresentWinConvertStretchMS();


	//
	// Framework override methods
	//

public:
	void InitTestParametersImpl();

	virtual HRESULT ModeListTransform(
		D3D_DEVICE_POINTER devicePointer,
		__in std::vector< ModeInformation >* pModes,
		__out std::vector< ModeInformation >* pTransformedModes);


	virtual TEST_RESULT ExecuteTestCase();
};


class CPresentFS
	:
	public CDXGIPresentSingleSC
{
	//
	// Construction/destruction
	//

public:
	CPresentFS();

	virtual ~CPresentFS();


	//
	// Framework override methods
	//

public:
	virtual TEST_RESULT Setup();
	virtual void Cleanup();

	virtual void InitTestParameters();
	virtual void InitFSTestParameters();
	virtual void InitModeParameters();
	virtual HRESULT ModeListTransform(
		D3D_DEVICE_POINTER devicePointer,
		__in std::vector< ModeInformation >* pModes,
		__out std::vector< ModeInformation >* pTransformedModes);

	virtual TEST_RESULT ExecuteTestCase();
	virtual RFactor IntitTestRFactors();

	virtual void CleanupTestCase();

protected:

	TEST_RESULT CreateDeviceAndSwapChain();

	HRESULT EnumerateModes(	std::vector < Adapter >* pAdapters);

	HRESULT EnumerateAdapterModes
		(
		std::vector < Adapter >* pAdapters,
		IDXGIAdapter * pDXGIAdapterEnumMode,
		UINT uiAdapterOrdinal
		);

	virtual HRESULT ResizeBuffers
		(
		IDXGISwapChain * pSwapChain,
		DXGI_SWAP_CHAIN_DESC * pSwapChainDesc
		);

	HRESULT SetDisplayMode
		(
		IDXGIOutput * pTargetOutput
		);


	//
	// Member data
	//

protected:

	bool m_bTestRotatedModes;
	bool m_bOneModeOnly;
	bool m_bIgnoreRefresh;	// true if only one refresh rate / mode should be used
	bool m_bAlwaysFilterLowResolution;	// true if low resolutions should always be filtered out
	bool m_bUseMinimalFormatList; // Whether to test all pixel formats, or just R8G8B8A8 and B8G8R8A8.

	int m_iModeIndex;
	ModeInformation m_OutputModeSet[MAX_DISPLAYMODES];
	ModeInformation m_ModeInformation;
	BOOL m_bDWMState;
	RFactor m_globalRFactor;
	int m_iTotalModes;


	/*
	int m_iSourceRectIndex;
	int m_iDestRectIndex;
	int m_iDirtyRectSetIndex;
	*/
};


class CPresentFSMS
	:
	public CPresentFS
{
	//
	// Construction/destruction
	//

public:
	CPresentFSMS();


	virtual void InitTestParameters();
	virtual void InitFSMSTestParameters();
	virtual HRESULT ModeListTransform(
		D3D_DEVICE_POINTER devicePointer,
		__in std::vector< ModeInformation >* pModes,
		__out std::vector< ModeInformation >* pTransformedModes);

	virtual TEST_RESULT ExecuteTestCase();
	virtual RFactor IntitTestRFactors();



	//
	// Member data
	//

protected:
	UINT m_uMaxQuality;		// define max quality levels for the test to limit test run times;
};


class CPresentFSRotation
	:
	public CPresentFS
{
	//
	// Construction/destruction
	//

public:
	CPresentFSRotation();

	virtual void InitTestParameters();
	virtual RFactor IntitTestRFactors();

};


class CPresentFSMulti
	:
	public CPresentFSMS
{
	//
	// Construction/destruction
	//

public:
	CPresentFSMulti();

	virtual void InitTestParameters();



	//
	// Helper methods
	//

protected:
	virtual HRESULT ResizeBuffers
		(
		IDXGISwapChain * pSwapChain,
		DXGI_SWAP_CHAIN_DESC * pSwapChainDesc
		);


	//
	// Member data.
	//

protected:
	int m_Scaling;
	int m_ScalingMS;
};

class PresentWinCSSmallWindow
	:
	public CPresentWinConvertStretch
{
	//
	// Construction/destruction
	//

public:
	PresentWinCSSmallWindow();

	virtual ~PresentWinCSSmallWindow();
	virtual HRESULT CreateTestWindows
		(
		UINT focusWindowLeft,
		UINT focusWindowTop,
		UINT focusWindowWidth,
		UINT focusWindowHeight
		);
	virtual bool PerformPresent( IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags );

    void InitTestParametersImpl();
protected:
	UINT m_nPresents;
	bool m_bWin8OrHigher;
};

#endif
//
// Project headers
//

#include "TestApp.h"


CDXGILatency::CDXGILatency()
{
}

CDXGILatency::~CDXGILatency()
{
}

bool CDXGILatency::InitializeTestGroup()
{
	DebugOut.Write("Entering InitializeTestGroup.\n");

	CleanupTestGroup();

	if (InitializeWindowClass())
	{
		DebugOut.Write("Exiting InitializeTestGroup (Succeeded).\n");

		return true;
	}

	DebugOut.Write("Exiting InitializeTestGroup (Failed).\n");

	return false;
}

void CDXGILatency::CleanupTestGroup()
{
	DebugOut.Write("Entering CleanupTestGroup.\n");

	//CleanupWindowClass();

	DebugOut.Write("Exiting CleanupTestGroup.\n");
}
/*
 *  file        :   OPMControl.h
 *  description :   OPM control types declarations
 *  history     :	6/2/2005 created
 *
 */
#pragma once

#include <windows.h>
#include <wincrypt.h>

#include <d3d9.h>
#include <dxva9typ.h>
#include <ddraw.h>
#include <opmapi.h>
#include "AuthHelper.h"
#include "OPMUtil.h"

const DWORD OPM_MESSAGE_LENGTH = 40;
const DWORD MAX_MON = 8;

typedef struct _tagLevelEntry
{
    TCHAR*       LevelTag;
    ULONG       Level;
}   LEVEL_ENTRY;

typedef struct _tagSignalingEntry
{
    TCHAR*       StandardTag;
    ULONG       Standard;
}   SIGNAL_ENTRY;

static  LEVEL_ENTRY     HDCPLevels[] = 
        {
            {TEXT("HDCP_OFF"), OPM_HDCP_OFF},
            {TEXT("HDCP_ON"), OPM_HDCP_ON},
        };

static  LEVEL_ENTRY     CGMSALevels[] =
        {
            {TEXT("CGMSA_OFF"), OPM_CGMSA_OFF},
            {TEXT("CGMSA_COPY_FREELY"), OPM_CGMSA_COPY_FREELY},
            {TEXT("CGMSA_COPY_NO_MORE"), OPM_CGMSA_COPY_NO_MORE},
            {TEXT("CGMSA_COPY_ONE_GENERATION"), OPM_CGMSA_COPY_ONE_GENERATION},
            {TEXT("CGMSA_COPY_NEVER"), OPM_CGMSA_COPY_NEVER},
            {TEXT("RED_CTL and CGMSA_OFF"), OPM_CGMSA_REDISTRIBUTION_CONTROL_REQUIRED | OPM_CGMSA_OFF},
            {TEXT("RED_CTL and CGMSA_COPY_FREELY"), OPM_CGMSA_REDISTRIBUTION_CONTROL_REQUIRED | OPM_CGMSA_COPY_FREELY},
            {TEXT("RED_CTL and CGMSA_COPY_NO_MORE"), OPM_CGMSA_REDISTRIBUTION_CONTROL_REQUIRED | OPM_CGMSA_COPY_NO_MORE},
            {TEXT("RED_CTL and CGMSA_COPY_ONE_GENERATION"), OPM_CGMSA_REDISTRIBUTION_CONTROL_REQUIRED | OPM_CGMSA_COPY_ONE_GENERATION},
            {TEXT("RED_CTL and CGMSA_COPY_NEVER"), OPM_CGMSA_REDISTRIBUTION_CONTROL_REQUIRED | OPM_CGMSA_COPY_NEVER},
        };

static  LEVEL_ENTRY     ACPLevels[] =
        {
            {TEXT("ACP_OFF"), OPM_ACP_OFF},
            {TEXT("ACP_LEVEL_ONE"), OPM_ACP_LEVEL_ONE},
            {TEXT("ACP_LEVEL_TWO"), OPM_ACP_LEVEL_TWO},
            {TEXT("ACP_LEVEL_THREE"), OPM_ACP_LEVEL_THREE},
        };

static  SIGNAL_ENTRY     SignalStandards[] =
        {
            {TEXT("NONE"), OPM_PROTECTION_STANDARD_NONE},
            {TEXT("IEC61880_525I"), OPM_PROTECTION_STANDARD_IEC61880_525I},
            {TEXT("IEC61880_2_525I"), OPM_PROTECTION_STANDARD_IEC61880_2_525I},
            {TEXT("IEC62375_625P"), OPM_PROTECTION_STANDARD_IEC62375_625P},
            {TEXT("EIA608B_525"), OPM_PROTECTION_STANDARD_EIA608B_525},
            {TEXT("EN300294_625I"), OPM_PROTECTION_STANDARD_EN300294_625I},
            {TEXT("CEA805A_TYPEA_525P"), OPM_PROTECTION_STANDARD_CEA805A_TYPEA_525P},
            {TEXT("CEA805A_TYPEA_750P"), OPM_PROTECTION_STANDARD_CEA805A_TYPEA_750P},
            {TEXT("CEA805A_TYPEA_1125I"), OPM_PROTECTION_STANDARD_CEA805A_TYPEA_1125I},
            {TEXT("CEA805A_TYPEB_525P"), OPM_PROTECTION_STANDARD_CEA805A_TYPEB_525P},
            {TEXT("CEA805A_TYPEB_750P"), OPM_PROTECTION_STANDARD_CEA805A_TYPEB_750P},
            {TEXT("CEA805A_TYPEB_1125I"), OPM_PROTECTION_STANDARD_CEA805A_TYPEB_1125I},
            {TEXT("ARIBTRB15_525I"), OPM_PROTECTION_STANDARD_ARIBTRB15_525I},
            {TEXT("ARIBTRB15_525P"), OPM_PROTECTION_STANDARD_ARIBTRB15_525P},
            {TEXT("ARIBTRB15_750P"), OPM_PROTECTION_STANDARD_ARIBTRB15_750P},
            {TEXT("ARIBTRB15_1125I"), OPM_PROTECTION_STANDARD_ARIBTRB15_1125I},
            {TEXT("OTHER"), OPM_PROTECTION_STANDARD_OTHER},
        };
const INT NUMOFSIGNALPROT = 16;
static  SIGNAL_ENTRY     AspectRatios[] =
        {
            {TEXT("EN300294_FULL_FORMAT_4_BY_3"), OPM_ASPECT_RATIO_EN300294_FULL_FORMAT_4_BY_3},
            {TEXT("EN300294_BOX_14_BY_9_CENTER"), OPM_ASPECT_RATIO_EN300294_BOX_14_BY_9_CENTER},
            {TEXT("EN300294_BOX_14_BY_9_TOP"), OPM_ASPECT_RATIO_EN300294_BOX_14_BY_9_TOP},
            {TEXT("EN300294_BOX_16_BY_9_CENTER"), OPM_ASPECT_RATIO_EN300294_BOX_16_BY_9_CENTER},
            {TEXT("EN300294_BOX_16_BY_9_TOP"), OPM_ASPECT_RATIO_EN300294_BOX_16_BY_9_TOP},
            {TEXT("EN300294_BOX_GT_16_BY_9_CENTER"), OPM_ASPECT_RATIO_EN300294_BOX_GT_16_BY_9_CENTER},
            {TEXT("EN300294_FULL_FORMAT_4_BY_3_PROTECTED_CENTER"), OPM_ASPECT_RATIO_EN300294_FULL_FORMAT_4_BY_3_PROTECTED_CENTER},
            {TEXT("EN300294_FULL_FORMAT_16_BY_9_ANAMORPHIC"), OPM_ASPECT_RATIO_EN300294_FULL_FORMAT_16_BY_9_ANAMORPHIC},
};


typedef struct  tagOPMDisplayData
{
    ULONG DisplayWidth;
    ULONG DisplayHeight;
    DXVA2_SampleFormat dsfSampleInterleaveFormat;
    D3DFORMAT d3dFormat;
    ULONG ulFrequencyNumerator;
    ULONG ulFrequencyDenominator;
}   OPM_DISPLAYDATA;

typedef struct  tagOPMHDCPKeyData
{
    ULONG               HDCPFlags;
    GUID                BKey;
    GUID                reserved1;
    GUID                reserved2;
}   OPM_HDCPKEYDATA;

typedef struct  tagOPMSRMPARAMETERS
{
    BOOL				IsSRMSet;
    ULONG               SRMVersion;
}   OPM_SRMPARAMETERS;

typedef struct  tagOPMStatusSignalData
{
    ULONG               AvailableTVProtectionStandards;
    ULONG               ActiveTVProtectionStandard;
    ULONG               Reserved;
    ULONG               AspectRatioValidMask1;
    ULONG               AspectRatioData1;
    ULONG               AspectRatioValidMask2;
    ULONG               AspectRatioData2;
    ULONG               AspectRatioValidMask3;
    ULONG               AspectRatioData3;
    ULONG               Reserved2[4];
    ULONG               Reserved3[4];
}   OPM_SIGNALDATA;

typedef struct  tagOPMSetSignalData
{
    ULONG NewTVProtectionStandard;
    ULONG AspectRatioChangeMask1;
    ULONG AspectRatioData1;
    ULONG AspectRatioChangeMask2;
    ULONG AspectRatioData2;
    ULONG AspectRatioChangeMask3;
    ULONG AspectRatioData3;
    ULONG Reserved[ 4 ];
    ULONG Reserved2[ 4 ];
    ULONG Reserved3;
}   OPM_SETSIGNALDATA;
    

typedef struct  tagOPMConfig
{
    ULONG               ProtectionMask;
    ULONG               LocalProtectionLevel[PROTECTION_TYPES];
    ULONG               GlobalProtectionLevel[PROTECTION_TYPES];
    ULONG               StatusFlags;
    LONG				ConnectorType;
    ULONG               BusType;
    

    OPM_DISPLAYDATA    DisplayData;
    OPM_HDCPKEYDATA    HDCPKeyData;
    OPM_SIGNALDATA     SignalData;
    OPM_SRMPARAMETERS  SRMData;
    
}   OPM_CONFIG;

/*
 *  class       :   OPMControl
 *  description :   
 *  notes       :   abstract base
 */

HRESULT CreateOPMFromDirect3D(IDirect3DDevice9* pDirect3DDevice9,OPM_VIDEO_OUTPUT_SEMANTICS vos,ULONG *pulNumVideoOutputs,IOPMVideoOutput*** pppOPMVideoOutput);

class OPMControl
{
public:
    OPMControl(IDirect3DDevice9*, OPM_VIDEO_OUTPUT_SEMANTICS vos, HRESULT*, BOOL fClone = FALSE , UINT MonitorIndex = 0);
    OPMControl(HWND hWnd, OPM_VIDEO_OUTPUT_SEMANTICS vos, HRESULT*, BOOL fClone = FALSE , UINT MonitorIndex = 0);
    ~OPMControl();

    HRESULT QueryConnectorType(LONG*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryProtectionType(ULONG*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryLocalProtectionLevel(const ULONG, ULONG*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryGlobalProtectionLevel(const ULONG, ULONG*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryDisplayData(OPM_DISPLAYDATA*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QuerySignalData(OPM_SIGNALDATA*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryHDCPKeyData(OPM_HDCPKEYDATA*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryBusData(ULONG*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryHDCPSRMParameters(ULONG *, ULONG *,OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryOutputId(UINT64*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);
    HRESULT QueryDVICharacteristics(ULONG*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS vos);

    HRESULT SetProtectionHDCP(OPM_HDCP_PROTECTION_LEVEL);
    HRESULT SetProtectionCOPPCompatibleHDCP(OPM_HDCP_PROTECTION_LEVEL);
    HRESULT SetProtectionCSSDVDHDCP(OPM_HDCP_PROTECTION_LEVEL);
    HRESULT SetProtectionCGMSA(ULONG);
    HRESULT SetProtectionACP(OPM_ACP_PROTECTION_LEVEL);
    HRESULT SetSignalData(OPM_SETSIGNALDATA*);
    HRESULT SetHDCPSRMParameters(OPM_SET_HDCP_SRM_PARAMETERS *, ULONG ulAdditionalParametersSize, const BYTE* pbAdditionalParameters); 
    HRESULT Initialize(BOOL bTryWithRSAEnc = FALSE, BOOL bRevoked = FALSE);

    _OPM_VIDEO_OUTPUT_SEMANTICS GetInitializationSemantics();
    BYTE* GetCertificate(){return m_pbGHCert;};
    ULONG GetCertificateSize(){return m_cbGHCertLen;};

    IOPMVideoOutput*   m_pOPMDevice;

    // Monitor
    HMONITOR        m_hMonitor;
    
protected:

    OPM_VIDEO_OUTPUT_SEMANTICS m_vos;//note that this is only used for creation

    //  context
    IDirect3DDevice9*    m_pParent;
    
    
    //  OPM parameters
    UINT            m_uStatusSeqIdx;
    UINT            m_uCommandSeqIdx;

    //  helper
    CPAuthHelper  m_AuthHelper;

    //certificate
    BYTE*           m_pbGHCert;
    ULONG           m_cbGHCertLen;


    //  methods
    HRESULT QueryStatus(GUID*, BYTE*, const ULONG, BYTE*, ULONG*, OPM_VIDEO_OUTPUT_SEMANTICS);
    HRESULT Command(GUID*, BYTE*, const ULONG, 	ULONG ulAdditionalParametersSize = 0, const BYTE *pbAdditionalParameters = NULL);

};  //  class   OPMControl


// Tests for Instruction: mNxN
#include "include.fx"

#define PS_SETUP \
	ps_2_0
#define SET_PRED \
	mov r0, c2 \
	setp_gt p0, r0, c0.y

// sets green, then removes green if either red or blue channels are set:
#define PS_END \
	mov r2.ga, c0.x \
	add_sat r2.g, r2.g, -r2.r \
	add_sat r2.g, r2.g, -r2.b \
	mov oC0, r2

#define SET_VS \
	VertexShaderConstant[0] = <mFinal>; \
	VertexShader = <NormalVS>;

#define SET_MAIN_PS_CONST \
	PixelShaderConstant[0] = {1.0, 0.0, 0.0009765625, 0.03125};

// Standard verify result macro, outputs to r1 0-right and 1-wrong, per component:
#define VERIFY_RESULT \
	add r1, r0, -c1 \
	cmp r1, r1, r1, -r1 \
	mov r3, c1 \
	cmp r3, r3, r3, -r3 \
	max r3, r3, c0.x \
	mul r3, r2, r3 \
	add r1, r3, -r1 \
	cmp r1, r1, c0.y, c0.x    \
	mov r2, c0.y

// The following can be used to verify each component individually, since some
// instructions or macros may write to extra components and you do not want to verify those.
#define V_X add_sat r2.r, r2.r, r1.x
#define V_Y add_sat r2.r, r2.r, r1.y
#define V_Z add_sat r2.r, r2.r, r1.z
#define V_W add_sat r2.r, r2.r, r1.w

#define TESTCASE \
Technique \
< \
	String Name =
#define PASSBEGIN \
	; \
	String Shape = "TinyQuad"; \
> \
{ \
	Pass P0 \
	{
#define TESTBEGIN \
		PixelShade