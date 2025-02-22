/*** bm.c - Memory Manager routines
*
*	Copyright <C> 1990, Microsoft Corporation
*
* Purpose:  handle memory requests of dlls & linked list
*
*
*************************************************************************/
#include "stdafx.h"
#pragma hdrstop

#include "cvinc\cvwmem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define cablMax    0x100
#define clpvMax    0x100
#define BLOCKMASK  0xFF00
#define ITEMMASK   0x00FF
#define BLOCKSHIFT 8

typedef LPV FAR *ABL; // Allocation BLock

static HMEM hvCur = (HMEM) 1;
static ABL FAR *rgabl = NULL;

#ifdef _DEBUG
typedef BYTE FAR *LCKB; // LoCK Block

static LCKB FAR *rglckb = NULL;
#endif

#ifndef hmemNull
#define hmemNull ( (HMEM) NULL )
#endif	// !hmemNull

#define IablFromHmem(hv) ( ((UINT)hv) >> BLOCKSHIFT)
#define IlpvFromHmem(hv) ( ((UINT)hv) &  ITEMMASK)
#define HmemFromIablIlpv(iabl,ilpv) ((HMEM) (( iabl << BLOCKSHIFT ) | ilpv ))
#define LpvFromHmem(hv) *( *( rgabl + IablFromHmem ( hv ) ) + IlpvFromHmem ( hv ))
#define LpvFromIablIlpv(iabl,ilpv) *( *( rgabl + iabl ) + ilpv )

#ifdef _DEBUG
#define LckFromHmem(hv) *( *( rglckb + IablFromHmem ( hv ) ) + IlpvFromHmem ( hv ))
#endif

HMEM PASCAL BMFindAvail ( void );
BOOL PASCAL BMNewBlock ( int );

//#define TRACK_DEBUGGER_LEAKS
#if defined (TRACK_DEBUGGER_LEAKS)

#undef new

class CMemoryBlock : public CObject
{
public:
	CMemoryBlock (ULONG cbExtra)
	{
		if (g_cAllocs == 0)
			afxDump.SetDepth (1);

		m_cbExtra = cbExtra;
		m_cAllocs = g_cAllocs++;
	}

	~CMemoryBlock ()
	{
	};

	void Dump (CDumpContext& dc) const
	{
		TCHAR szBuffer[32];

		wsprintf(szBuffer, _T("0x%08x, 0x%08x"), m_cAllocs, m_cbExtra);
		dc << szBuffer;
	}

	void* PASCAL operator new(size_t nSize, LPCSTR lpszFileName, int nLine, size_t cbExtra)
	{
		return ::operator new(nSize + cbExtra, _CLIENT_BLOCK, lpszFileName, nLine);
	}

	HMEM GetExtra () const
	{
		return (HMEM) rgb;
	}

	static CMemoryBlock *GetBlockFromExtra (HMEM hv)
	{
		return (CMemoryBlock *) (((char *) hv) - ((CMemoryBlock *) 0)->rgb);
	}

private:
	ULONG	m_cbExtra;
	ULONG	m_cAllocs;
	static ULONG g_cAllocs;

	char	rgb[4];
};

ULONG CMemoryBlock::g_cAllocs = 0;

CMemoryBlock::CMemoryBlock (ULONG cbExtra)

#endif	// TRACK_DEBUGGER_LEAKS




// Public functions

BOOL PASCAL BMInit ( VOID ) {

#ifdef BMHANDLES	// {

    if ( ( rgabl = (ABL FAR *) cvw3_fmalloc ( sizeof ( ABL ) * cablMax ) ) == NULL ) {
        return FALSE;
    }
    _fmemset ( rgabl, 0, sizeof ( ABL ) * cablMax );

#ifdef _DEBUG
    if ( ( rglckb = (LCKB FAR *) cvw3_fmalloc ( sizeof ( LCKB ) * cablMax ) ) == NULL ) {
        return FALSE;
    }
    _fmemset ( rglckb, 0, sizeof ( LCKB ) * cablMax );
#endif

    // CAV 6583 -- must reset hvCur each time we re-init
    // (the IDE calls BMInit() each time it starts a debug session, codeview
    // only calls BMInit() once so hvCur doesn't need to be reset...

	hvCur = (HMEM) 1;

	CVInitCritSection(icsBm);

    return BMNewBlock ( 0 );

#else	// } else !BMHANDLES {

	// We're going to return pointers directly, rather than having our own
	// handles.  So we need to make sure that pointers and handles are the
	// same size.
	ASSERT ( sizeof(HMEM) == sizeof(VOID FAR *) );

	return TRUE;

#endif	// }

}

HMEM PASCAL LOADDS BMAlloc ( UINT cb ) {

#ifdef BMHANDLES	// {

	HMEM hv;

	CVEnterCritSection(icsBm);

	hv	= BMFindAvail ( );

    if ( hv ) {
        LPV lpv = cvw3_fmalloc ( cb );

        if ( lpv == NULL ) {
            hv = hmemNull;
        }
        else {
            LpvFromHmem ( hv ) = lpv;
        }
    }

	CVLeaveCritSection(icsBm);

    return hv;

#else	// } else !BMHANDLES {

#if defined (TRACK_DEBUGGER_LEAKS)
	CMemoryBlock *pMemoryBlock = new(THIS_FILE, __LINE__, cb) CMemoryBlock (cb);
	return pMemoryBlock->GetExtra();
#else
	return (HMEM) cvw3_fmalloc(cb);
#endif

#endif	// }

}

HMEM PASCAL LOADDS BMRealloc ( HMEM hv, UINT cb ) {

#ifdef BMHANDLES	// {

	LPV  lpv;
    UINT cbOld;

	CVEnterCritSection(icsBm);

	lpv = LpvFromHmem ( hv );
    ASSERT ( lpv );
    cbOld = cvw3_fmsize ( lpv );

    if ( cbOld != cb ) {
        LPV lpvNew = cvw3_fmalloc ( cb );

	if ( lpv && lpvNew) {
            _fmemcpy ( lpvNew, lpv, min ( cb, cbOld ) );
            cvw3_ffree ( lpv );
            LpvFromHmem ( hv ) = lpvNew;
        }
        else {
            hv = hmemNull;
        }
    }

	CVLeaveCritSection(icsBm);

    return hv;

#else	// } else !BMHANDLES {

#if defined (TRACK_DEBUGGER_LEAKS)
	HMEM pNew = BMAlloc (cb);
	memcpy (pNew, hv, cb);
	BMFree (hv);
	return pNew;
#else
	return (HMEM) cvw3_frealloc((VOID FAR *)hv, cb);
#endif

#endif	// }

}

VOID PASCAL LOADDS BMFree ( HMEM hv ) {

#ifdef BMHANDLES	// {

	CVEnterCritSection(icsBm);

    if ( hv < hvCur ) {
        hvCur = hv;
    }

    cvw3_ffree ( LpvFromHmem ( hv ) );
    LpvFromHmem ( hv ) = NULL;

#ifdef _DEBUG
    LckFromHmem ( hv ) = 0;
#endif

	CVLeaveCritSection(icsBm);

#else	// } else !BMHANDLES {

#if defined (TRACK_DEBUGGER_LEAKS)
	if (hv != NULL)
	{
		CMemoryBlock *pMemoryBlock = CMemoryBlock::GetBlockFromExtra (hv);
		delete pMemoryBlock;
	}
#else
	cvw3_ffree((VOID FAR *)hv);
#endif

#endif	// }

}

#ifdef BMLock
#undef BMLock
#endif
LPV  PASCAL LOADDS BMLock ( HMEM hv ) {

#ifdef BMHANDLES	// {

    LPV lpv;

    if ( hv ) {
#ifdef _DEBUG
        LckFromHmem ( hv ) += 1;

		ASSERT ( LckFromHmem ( hv ) > 0 );	// check for overflow
#endif
        lpv = LpvFromHmem( hv );
    }
    else {
        lpv = NULL;
    }

    return lpv;

#else	// } else !BMHANDLES {

	return (VOID FAR *) hv;

#endif	// }

}

#ifdef BMUnlock
#undef BMUnlock
#endif
VOID PASCAL LOADDS BMUnlock ( HMEM hv ) {

#if defined (BMHANDLES) && defined (_DEBUG)
    if ( hv ) {
        ASSERT ( LckFromHmem ( hv ) > 0 );

        LckFromHmem ( hv ) -= 1;
    }
#endif

}

BOOL PASCAL LOADDS BMIsLocked ( HMEM hv ) {

#if defined (BMHANDLES) && defined (_DEBUG)
    return !!(LckFromHmem(hv));
#else
    return FALSE;
#endif
}

// Private functions

#ifdef BMHANDLES	// {

HMEM PASCAL BMFindAvail ( void ) {
    WORD iabl = IablFromHmem ( hvCur );
    WORD ilpv = IlpvFromHmem ( hvCur );
    HMEM hv   = hmemNull;
    BOOL fFail= FALSE;

    // We were out of memory, and nobody has freed anything.

    if ( hvCur == hmemNull ) {
        return hmemNull;
    }

    while ( TRUE ) {
        // Loop through the current allocation block to find and
        //  empty slot - Note that hvCur always represents the
        //  least possible open block, so we don't have to backtrack

        while ( ilpv < clpvMax && LpvFromIablIlpv ( iabl, ilpv ) ) {
            ilpv += 1;
        }

        // If we ran off the end of the current block

        if ( ilpv == clpvMax ) {
            iabl += 1;

            if ( iabl == cablMax ) {
                fFail = TRUE;
                break;
            }
            else if ( *( rgabl + iabl ) == NULL ) {
                if ( !BMNewBlock ( iabl ) ) {
                    fFail = TRUE;
                    break;
                }
            }

            ilpv = 0;
        }
        else {
            break;
        }

    };

    if ( !fFail ) {
        hv = HmemFromIablIlpv ( iabl, ilpv );
    }

    hvCur = hv;
    return hv;
}

BOOL PASCAL BMNewBlock ( int iabl ) {
    ASSERT ( iabl < cablMax );
    ASSERT ( *( rgabl + iabl ) == NULL );

    if ( ( *( rgabl + iabl ) = cvw3_fmalloc ( clpvMax * sizeof ( LPV ) ) ) == NULL ) {
        return FALSE;
    }
    _fmemset ( *( rgabl + iabl ), 0, clpvMax * sizeof ( LPV ) );

#ifdef _DEBUG
    if ( ( *( rglckb + iabl ) = cvw3_fmalloc ( clpvMax * sizeof ( BYTE ) ) ) == NULL ) {
        return FALSE;
    }
    _fmemset ( *( rglckb + iabl ), 0, clpvMax * sizeof ( BYTE ) );
#endif

    return TRUE;
}

#endif	// } BMHANDLES
