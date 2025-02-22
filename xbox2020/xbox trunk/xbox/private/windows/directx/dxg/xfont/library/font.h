//****************************************************************************
//
// XBox internal font header.
//
// History:
//
//   07/06/00 [andrewso] - Created
//   08/04/00 [andrewso] - Added compressed glyph bitmaps
//
//****************************************************************************

#include <d3d8.h>

#ifdef _XBOX
#include "xfontformat.h"
#else
#include "xfontformat-pc.h"
#endif

#pragma once

#if defined(__cplusplus)

extern "C" {

#endif

//
// Callbacks used to communicate to the true-type font package.  We go 
// through these callbacks to give the linker the opportunity to
// throw all of the true type stuff away...if the user doesn't call
// XFONT_OpenTrueTypeFont, then none of the TrueType methods get 
// referenced 
//

typedef void (__stdcall *CB_UnloadFont)(struct _Font *);
typedef HRESULT (__stdcall *CB_ResetTransform)(struct _Font *);
typedef HRESULT (__fastcall *CB_GetCharacterData)(struct _Font *, WCHAR, struct _Glyph **, unsigned *pcbGlyphSize);

//
// Structure definitions.
//

typedef struct IDirect3DSurface8 IDirect3DSurface8;

//============================================================================
// An entry in the cache.  The glyph immediately follows this structure.
//============================================================================

typedef struct _CacheEntry
{
    WCHAR wch;          // Cached character
    WORD wLength;       // Length of this entry, including the header

    // The entry is stashed on a circular, doubly-linked list.
    struct _CacheEntry *pNextEntry;
    struct _CacheEntry *pPrevEntry;
} CacheEntry;

//============================================================================
// The structure that holds the state of a font.  This is opaquely given to
// the consumer so they can manually switch between fonts without having to
// unload/load them.
//============================================================================

typedef struct _Font
{
    //
    // Housekeeping.
    //

    unsigned uReferenceCount;

    // 
    // Metrics information about this font.
    //

    unsigned uCellHeight;           // the height of the character cell
    unsigned uDescent;              // bottom of the cell to the baseline

    unsigned uAntialiasLevel;       // amount of antialiasing information (0, 2, 4)
    unsigned uRLEWidth;             // # of bits for RLE
    unsigned uMaxBitmapHeight;      // height of the tallest glyph
    unsigned uMaxBitmapWidth;       // width of the widest glyph
    unsigned uStyle;                // the style of the font to simulate (truetype only)
    unsigned uIntercharacterSpacing;// how many extra pixels to put between each character
    
    unsigned uAlignmentMode;        // how to align the text
    D3DCOLOR TextColor;             // the color of the text
    D3DCOLOR BackgroundColor;       // the color of the background
    BOOL     fPaintBackground;      // whether to fill the background or not

    BOOL     fUseClippingRectangle; // whether to use the clipping rectangle
    D3DRECT  ClippingRectangle;     // clipping rectangle
    D3DRECT  ClippingRectangleCopy; // clipping rectangle copy for GetClippingRectangle.

    //
    // Indirection tables used to abstract rendering bitmaps and truetype
    // fonts.
    //

    CB_UnloadFont pfnUnloadFont;
    CB_ResetTransform pfnResetTransform;
    CB_GetCharacterData pfnGetCharacterData;

    //
    // The glyph cache.
    //

    // Memory to hold the glyph/bitmap when there is no cache.
    void *pvOneGlyph;

    // The real cache.
    BYTE *pbCache;              // Start of the cache.
    BYTE *pbCacheEnd;           // End of the cache.
    BYTE *pbCacheNext;          // Where to put the next new entry.

    unsigned cbCacheSize;       // Size of the cache.
    unsigned cbCacheUsed;       // How much as been used.

    CacheEntry CacheHead;       // Head of the cache list.
} Font;

//
// Exposed functions.
//

// Open a TrueType font.
HRESULT __stdcall TT_OpenTrueTypeFont(LPCWSTR wszFileName, struct _Font **ppFont);

// Open a bitmap font.
HRESULT __stdcall BP_OpenBitmapFont(LPCWSTR wszFileName, unsigned uCacheSize, struct _Font **ppFont, BOOL *pfUseCache);
HRESULT __stdcall BP_OpenBitmapFontFromMemory(CONST void *pFontData, unsigned uFontDataSize, struct _Font **ppFont);

// Render a single character.
HRESULT __stdcall PaintText(Font *, LPCVOID, unsigned, D3DFORMAT, LPCWSTR, unsigned, long, long, unsigned, unsigned, unsigned, unsigned);

// Methods used by the font packages to control the font cache.
HRESULT AddToCache(Font *, WCHAR wch, unsigned cbGlyph, Glyph **ppGlyph);
void ClearCache(Font *);

// 
// Debug helpers.
//

#if DBG

void XFRIP(PCHAR Format, ...);

#define XFNULL(x, y)  { if (x == NULL) XFRIP(y); } 
#define XFASSERT(x, y) { if (!(x)) XFRIP(y); }

#else

#define XFRIP(x)
#define XFASSERT(x, y)
#define XFNULL(x, y)

#endif

#if defined(__cplusplus)

};

#endif
