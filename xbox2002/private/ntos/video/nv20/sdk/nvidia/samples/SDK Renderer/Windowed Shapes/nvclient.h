 /***************************************************************************\
|*                                                                           *|
|*       Copyright 1993-1998 NVIDIA, Corporation.  All rights reserved.      *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     international laws.  Users and possessors of this source code are     *|
|*     hereby granted a nonexclusive,  royalty-free copyright license to     *|
|*     use this code in individual and commercial software.                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user documenta-     *|
|*     tion and  internal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*       Copyright 1993-1998 NVIDIA, Corporation.  All rights reserved.      *|
|*                                                                           *|
|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|
|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  "AS IS"     *|
|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|
|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|
|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|
|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|
|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INDIRECT,  INCI-     *|
|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|
|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|
|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|
|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|
|*                                                                           *|
|*     U.S. Government  End  Users.   This source code  is a "commercial     *|
|*     item,"  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|
|*     consisting  of "commercial  computer  software"  and  "commercial     *|
|*     computer  software  documentation,"  as such  terms  are  used in     *|
|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|
|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|
|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|
|*     all U.S. Government End Users  acquire the source code  with only     *|
|*     those rights set forth herein.                                        *|
|*                                                                           *|
 \***************************************************************************/

/*************************************************************************************************
*
*	File: nvclient.h
*
*	Description:
*		Definitions and prototypes for nvclient.c.
*
**************************************************************************************************/

// additional SDK macros
#define NV_SUBCHANNEL(n)				(channel->subchannel[n])
#define WAIT_FOR_SUBCHANNEL(psc,nBytes)	while((psc)->control.Free<(nBytes))
#define PACK_PITCH(s,d)					((V032)((((U032)(d))<<16)|(((U032)(s))&0x0000FFFF)) )

// 32-bit handles of our choice to track our allocated objects
enum
{
	OUR_DEVICE_ID = 0xBAAD0000,
	OUR_CHANNEL_ID,
	OUR_FRAME_BUFFER_ID,
	OUR_FRAME_BUFFER_CTX_ID,
	OUR_2D_RENDERING_SURFACE_ID,
	OUR_RECTANGLE_RENDERER_ID,
	OUR_CLIP_RECTANGLE_ID,
	OUR_LINE_RENDERER_ID,
	OUR_BLIT_ID
};

// subchannel definitions
enum
{
	WORKING_SUBCH = 0,
	CLIP_RECT_SUBCH,
	RECT_RENDER_SUBCH,
	LINE_RENDER_SUBCH,
	BLIT_SUBCH
};

// errors
typedef ULONG NV_STATUS;
enum 
{
	NV_STATUS_SUCCESS = 0,
	NV_STATUS_ERROR,
	NV_STATUS_ERROR_ALLOC_DEV,
	NV_STATUS_ERROR_DEV_TYPE,
	NV_STATUS_ERROR_ALLOC_CTX_DMA,
	NV_STATUS_ERROR_ALLOC_CH_PIO,
	NV_STATUS_ERROR_ALLOC_CH_DMA,
	NV_STATUS_ERROR_ALLOC_MEM,
	NV_STATUS_ERROR_ALLOC_OBJ,
	NV_STATUS_ERROR_CONFIG_GET,
	NV_STATUS_ERROR_ALLOC_CLIENT
};

// drawing constants
#define MAX_8BIT_COLOR 0xff
#define RECTANGLE_QTY 5000
#define LINE_QTY 1000
#define BLIT_QTY 5000
#define NV_DELAY 75000

// rectangle definition consisting of an origin and an extent
struct NV_RECT
{
	POINT org;
	SIZE ext;
};

// BLIT movement definitions
enum H_DIR {LEFT, RIGHT};
enum V_DIR {UP, DOWN};
struct DIRECTION_VECTOR
{
	H_DIR horiz;
	V_DIR vert;
};

// prototypes
NV_STATUS NvCreate();
NV_STATUS NvDrawLines(HWND);
NV_STATUS NvDrawRectangles(HWND);
NV_STATUS NvBlits(HWND);
void NvDestroy();
NV_RECT NvGetClientNvRect(HWND);
void NvClientToScreenRect(HWND, RECT*);
void NvGetRandomRGB24Color(PULONG, PULONG, PULONG);
POINT NvGetRandomPoint(SIZE);
SIZE NvGetRandomExtent(SIZE);
void NvReportError(ULONG);
void NvDisplayCaption(HWND, ULONG, NV_RECT);
void NvScreenToClientRect(HWND, RECT*);
RECT NvRectToWinRect(NV_RECT);
void NvMoveBlitDest(NV_RECT*, DIRECTION_VECTOR*, NV_RECT);
