//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft shared
// source or premium shared source license agreement under which you licensed
// this source code. If you did not accept the terms of the license agreement,
// you are not authorized to use this source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the SOURCE.RTF on your install media or the root of your tools installation.
// THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
// --------------------------------------------------------------------
//                                                                     
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A      
// PARTICULAR PURPOSE.                                                 
//                                                                     
// --------------------------------------------------------------------
#pragma once

#define Countof(array) (sizeof(array)/sizeof(array[0]))

/**
  * A class to encapsulate all the state pertaining to a filter graph. Useful when creating multiple graphs.
  */
class FilterGraph
{
public:
	IGraphBuilder		*pGraph;
	IMediaSeeking		*pMediaSeeking;
	IMediaControl		*pMediaControl;
	IMediaEvent			*pMediaEvent;
	IQualProp			*pQualProp;
	IAMDroppedFrames	*pDroppedFrames;
	IAMAudioRendererStats *pAudioRendererStats;
	IAMNetworkStatus *pNetworkStatus;

	// This is only available on CE
	// The IAMVideoRendererMode interface
	IAMVideoRendererMode* m_pVRMode;

	TCHAR url[MAX_PATH];
};
