//////////////////////////////////////////////////////////////////////
//
//  PRIVATE header file for linklist utility
//
//////////////////////////////////////////////////////////////////////
//
//  A Linked List Entry
//
typedef struct _lle
    {
#ifdef DEBUGVER
    WORD            wTest;      // consistency check
#endif
    HLLE            hlleNext;
#ifdef DBLLINK
    HLLE            hllePrev;
#endif // DBLLINK
    WORD            rgw[0];     // Variable length data
    } LLE;
typedef LLE *       PLLE;
typedef LLE FAR *   LPLLE;
//
// Linked List Information
//
typedef struct _lli
    {
    HLLE            hlleHead;
    HLLE            hlleTail;
    DWORD           chlleMac;
    void *          pcs;                // pointer to critical section object
    DWORD           cbUserData;         // How big the user data is
    LLF             llf;                // LinkList Flags
    LPFNKILLNODE    lpfnKill;           // Callback for deletion of node
    LPFNFCMPNODE    lpfnCmp;            // Callback for node comparison
    } LLI;
typedef LLI *       PLLI;
typedef LLI FAR *   LPLLI;
//
//  Some NICE nulls (for clean code)
//
#define hlliNull    (HLLI)NULL
#define hlleNull    (HLLE)NULL
//
// These help keep the code clean
//
#define LockHlle(hlle)      ((LPLLE)LockHmem(hlle))
#define LockHlli(hlli)      ((LPLLI)LockHmem(hlli))
#define HlliAlloc()         ((HLLI)AllocHmem(sizeof(LLI)))
#define HlleAllocCb(cb)     ((HLLE)AllocHmem(cb))
#define FreeHlli(hlli)      FreeHmem(hlli)
#define FreeHlle(hlle)      FreeHmem(hlle)
#define UnlockHlli(hlli)	UnlockHmem(hlli)
#define UnlockHlle(hlle)	UnlockHmem(hlle)

//
//  PRIVATE INTERNAL ROUTINES
//
void PASCAL LLInsertHlle( HLLI, HLLE, HLLE, HLLE );
void PASCAL LLDeleteHlle( HLLI, HLLE, HLLE );
DWORD PASCAL LLChlleInLl( HLLI );

//
// Some debug stuff
//
#ifdef DEBUGVER
#define WCONSIST        (WORD)0xabcd
#endif // DEBUGVER

#define AllocHmem(cb) ExAllocatePoolWithTag(PagedPool, cb, 'illh')
#define FreeHmem(pv) ExFreePoolWithTag(pv, 'illh')
#define LockHmem(pv) (pv)
#define UnlockHmem(pv)
