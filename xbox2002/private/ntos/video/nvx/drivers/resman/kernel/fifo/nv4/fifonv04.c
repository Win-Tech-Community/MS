 /***************************************************************************\
|*                                                                           *|
|*        Copyright (c) 1993-2000 NVIDIA, Corp.  All rights reserved.        *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     international laws.   NVIDIA, Corp. of Sunnyvale, California owns     *|
|*     the copyright  and as design patents  pending  on the design  and     *|
|*     interface  of the NV chips.   Users and possessors of this source     *|
|*     code are hereby granted  a nonexclusive,  royalty-free  copyright     *|
|*     and  design  patent license  to use this code  in individual  and     *|
|*     commercial software.                                                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user documenta-     *|
|*     tion and  internal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*     Copyright (c) 1993-2000  NVIDIA, Corp.    NVIDIA  design  patents     *|
|*     pending in the U.S. and foreign countries.                            *|
|*                                                                           *|
|*     NVIDIA, CORP.  MAKES  NO REPRESENTATION ABOUT  THE SUITABILITY OF     *|
|*     THIS SOURCE CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT     *|
|*     EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORP. DISCLAIMS     *|
|*     ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,  INCLUDING  ALL     *|
|*     IMPLIED   WARRANTIES  OF  MERCHANTABILITY  AND   FITNESS   FOR  A     *|
|*     PARTICULAR  PURPOSE.   IN NO EVENT SHALL NVIDIA, CORP.  BE LIABLE     *|
|*     FOR ANY SPECIAL, INDIRECT, INCIDENTAL,  OR CONSEQUENTIAL DAMAGES,     *|
|*     OR ANY DAMAGES  WHATSOEVER  RESULTING  FROM LOSS OF USE,  DATA OR     *|
|*     PROFITS,  WHETHER IN AN ACTION  OF CONTRACT,  NEGLIGENCE OR OTHER     *|
|*     TORTIOUS ACTION, ARISING OUT  OF OR IN CONNECTION WITH THE USE OR     *|
|*     PERFORMANCE OF THIS SOURCE CODE.                                      *|
|*                                                                           *|
 \***************************************************************************/

/******************** Chip Specific HAL FIFO Routines **********************\
*                                                                           *
* Module: FIFONV04.C                                                        *
*   The NV4 specific HAL FIFO routines reside in this file.                 *
*                                                                           *
*****************************************************************************
*                                                                           *
* History:                                                                  *
*                                                                           *
\***************************************************************************/
#include <nv_ref.h>
#include <nv4_ref.h>
#include <nvrm.h>
#include <nv4_hal.h>
#include "nvhw.h"
#include "nvhalcpp.h"

// forwards
RM_STATUS nvHalFifoControl_NV04(VOID *);
RM_STATUS nvHalFifoAllocPio_NV04(VOID *);
RM_STATUS nvHalFifoAllocDma_NV04(VOID *);
RM_STATUS nvHalFifoFree_NV04(VOID *);
RM_STATUS nvHalFifoGetExceptionData_NV04(VOID *);
RM_STATUS nvHalFifoService_NV04(VOID *);
RM_STATUS nvHalFifoAccess_NV04(VOID *);
RM_STATUS nvHalFifoHashAdd_NV04(VOID *);
RM_STATUS nvHalFifoHashDelete_NV04(VOID *);
RM_STATUS nvHalFifoHashFunc_NV04(VOID *);

//
// The context switch interface is only used internally, but perhaps
// should be made available to the resource manager anyway.
//
static RM_STATUS nvHalFifoContextSwitch_NV04(PHALHWINFO, U032);

static U032 nvHalFifoCalcDmaFetch_NV04(U032, U032, U032);

RM_STATUS
nvHalFifoControl_NV04(VOID *arg)
{
    PFIFOCONTROLARG_000 pFifoControlArg = (PFIFOCONTROLARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFIFOHALINFO pFifoHalInfo;
    PFIFOHALINFO_NV04 pFifoHalPvtInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo;
    U032 FifoReassign, FifoPush, FifoPull;
    U032 i;

    // ASSERTIONS

    //
    // Verify interface revision.
    //
    if (pFifoControlArg->id != FIFO_CONTROL_000)
        return (RM_ERR_VERSION_MISMATCH);

	pHalHwInfo = pFifoControlArg->pHalHwInfo;
    pFifoHalInfo = pHalHwInfo->pFifoHalInfo;
    pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;
    pFifoHalPvtInfo = (PFIFOHALINFO_NV04)pHalHwInfo->pFifoHalPvtInfo;

    switch (pFifoControlArg->cmd) {
        case FIFO_CONTROL_INIT:
            //
            // Setup default parameters. 
            //
            pFifoHalInfo->RetryCount = 255;
            pFifoHalInfo->UserBase = DEVICE_BASE(NV_USER);
            pFifoHalPvtInfo->Mode = 0;
            pFifoHalPvtInfo->InUse = 0;
            
            //
            // Setup interrupt enable mask.
            //
            pFifoHalInfo->IntrEn0 =
                DRF_DEF(_PFIFO, _INTR_EN_0, _CACHE_ERROR, _ENABLED) |
                DRF_DEF(_PFIFO, _INTR_EN_0, _RUNOUT, _ENABLED) |
                DRF_DEF(_PFIFO, _INTR_EN_0, _RUNOUT_OVERFLOW, _ENABLED) |
                DRF_DEF(_PFIFO, _INTR_EN_0, _DMA_PUSHER, _ENABLED) |
                DRF_DEF(_PFIFO, _INTR_EN_0, _DMA_PT, _ENABLED);

            //
            // Zero FIFO get/put.
            //
            REG_WR32(NV_PFIFO_CACHE1_PUT, 0);
            REG_WR32(NV_PFIFO_CACHE1_GET, 0);
            //
            // Zero DMA FIFO get/put.
            //
            REG_WR32(NV_PFIFO_CACHE1_DMA_PUT, 0);
            REG_WR32(NV_PFIFO_CACHE1_DMA_GET, 0);
            //
            // Zero FIFO hash valid.
            //
            REG_WR32(NV_PFIFO_CACHE0_HASH, 0);
            REG_WR32(NV_PFIFO_CACHE1_HASH, 0);
            //
            // Zero engine assignments
            //
            //REG_WR32(NV_PFIFO_CACHE0_ENGINE, 0);
            //REG_WR32(NV_PFIFO_CACHE1_ENGINE, 0);
            //
            // Make all FIFO's default
            //
            REG_WR32(NV_PFIFO_MODE, pFifoHalPvtInfo->Mode);
            REG_WR32(NV_PFIFO_DMA, 0);
            REG_WR32(NV_PFIFO_SIZE, 0);
            //
            // Clear all pusher state
            //
            REG_WR32(NV_PFIFO_CACHE1_DMA_STATE, 0);
            //
            // Zero run-out pointers.
            //
            REG_WR_DRF_NUM(_PFIFO, _RUNOUT_PUT, _ADDRESS, 0);
            REG_WR_DRF_NUM(_PFIFO, _RUNOUT_GET, _ADDRESS, 0);
            break;
        case FIFO_CONTROL_LOAD:
            //
            // Update the dma fetch numbers using reasonable defaults.
            //
            REG_WR32(NV_PFIFO_CACHE1_DMA_FETCH, 
                     DRF_DEF(_PFIFO, _CACHE1_DMA_FETCH, _TRIG, _128_BYTES) |
                     DRF_DEF(_PFIFO, _CACHE1_DMA_FETCH, _SIZE, _32_BYTES) |
                     DRF_DEF(_PFIFO, _CACHE1_DMA_FETCH, _MAX_REQS, _15));
            
            //
            // Enable default timeslicing
            //    
            REG_WR32(NV_PFIFO_DMA_TIMESLICE, 
                     DRF_DEF(_PFIFO, _DMA_TIMESLICE, _TIMEOUT, _ENABLED)
                     | DRF_DEF(_PFIFO, _DMA_TIMESLICE, _SELECT, _128K));
            
            //
            // Set retry delay to match common hardware latency.
            //
            REG_WR_DRF_NUM(_PFIFO, _DELAY_0, _WAIT_RETRY, pFifoHalInfo->RetryCount);
            //
            // Disable cache reassignment.
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHES, _REASSIGN, _DISABLED);
            //
            // Disable pusher and puller access to cache0.
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHE0_PUSH0, _ACCESS, _DISABLED);
            REG_WR_DRF_DEF(_PFIFO, _CACHE0_PULL0, _ACCESS, _DISABLED);
            //
            // Disable pusher and puller access to cache1.
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH0, _ACCESS, _DISABLED);
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PULL0, _ACCESS, _DISABLED);
            FIFOLOG(3, 0, 0);
            //
            // Disable the pusher, if active
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_DMA_PUSH, _ACCESS, _DISABLED);
            
            //
            // Force a context switch to PRAMIN.
            //
            // KJK This should be replaced with a full software-based context switch
            //
            nvHalFifoContextSwitch_NV04(pHalHwInfo, (NUM_FIFOS_NV04 - 1));
            
            //
            // Zero FIFO get/put.
            //
            REG_WR32(NV_PFIFO_CACHE1_PUT, 0);
            REG_WR32(NV_PFIFO_CACHE1_GET, 0);

            //
            // Enable pusher and puller access to cache1.
            //
            FIFOLOG(3, 1, 0);
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PULL0, _ACCESS, _ENABLED);
            //
            // Delay for slow CACHE1_PULL.
            //
            //temp = REG_RD32(NV_PFIFO_CACHE1_PULL0);
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH0, _ACCESS, _ENABLED);
            //
            // Enable cache reassignment.
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHES, _REASSIGN, _ENABLED);
            break;
        case FIFO_CONTROL_UNLOAD:
            //
            // Disable dma timeslicing
            //    
            REG_WR32(NV_PFIFO_DMA_TIMESLICE, DRF_DEF(_PFIFO, _DMA_TIMESLICE, _TIMEOUT, _DISABLED));

            //
            // Empty FIFO and runout.
            //
            while ((REG_RD_DRF(_PFIFO, _CACHE1_STATUS, _LOW_MARK) != NV_PFIFO_CACHE1_STATUS_LOW_MARK_EMPTY)
                   || (REG_RD_DRF(_PFIFO, _RUNOUT_STATUS, _LOW_MARK) != NV_PFIFO_RUNOUT_STATUS_LOW_MARK_EMPTY)
                   || (REG_RD_DRF(_PFIFO, _CACHE1_DMA_PUSH, _STATE) == NV_PFIFO_CACHE1_DMA_PUSH_STATE_BUSY))
            {
                //
                // Make sure we process any fifo interrupts
                //
                HALRMSERVICEINTR(pHalHwInfo, FIFO_ENGINE_TAG);
                
                //
                // Check if GE needs servicing.
                //
                if (REG_RD32(NV_PGRAPH_INTR))
                    HALRMSERVICEINTR(pHalHwInfo, GR_ENGINE_TAG);
            }

            //
            // Disable the dma pusher, if active
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_DMA_PUSH, _ACCESS, _DISABLED);

            //
            // Wait til idle
            //
            while (REG_RD_DRF(_PFIFO, _CACHE1_DMA_PUSH, _STATE) == NV_PFIFO_CACHE1_DMA_PUSH_STATE_BUSY)
			    ;

            //
            // Disable cache reassignment.
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHES, _REASSIGN, _DISABLED);
            //
            // Disable pusher and puller access to cache0.
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHE0_PUSH0, _ACCESS, _DISABLED);
            REG_WR_DRF_DEF(_PFIFO, _CACHE0_PULL0, _ACCESS, _DISABLED);
            //
            // Disable pusher and puller access to cache1.
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH0, _ACCESS, _DISABLED);
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PULL0, _ACCESS, _DISABLED);
            FIFOLOG(3, 0, 0);
            //
            // Force a context switch to PRAMIN.
            //
            // KJK This should be replaced with a full software-based context switch
            //
            nvHalFifoContextSwitch_NV04(pHalHwInfo, (NUM_FIFOS_NV04 - 1));
            
            //
            // Zero FIFO get/put.
            //
            REG_WR32(NV_PFIFO_CACHE1_PUT, 0);
            REG_WR32(NV_PFIFO_CACHE1_GET, 0);
            
            //
            // Flush all FIFOs.
            //
            FifoReassign = REG_RD32(NV_PFIFO_CACHES);
            FifoPush = REG_RD32(NV_PFIFO_CACHE1_PUSH0);
            FifoPull = REG_RD32(NV_PFIFO_CACHE1_PULL0);
            REG_WR_DRF_DEF(_PFIFO, _CACHES, _REASSIGN, _DISABLED);
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH0, _ACCESS, _DISABLED);
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PULL0, _ACCESS, _DISABLED);
            FIFOLOG(1, 0, 0);

            //
            // Update the FIFO context and its dirty bits.  By moving the get pointer to the current
            // put value, we are flushing any pending push data that hasn't been fetched yet.
            //
            for (i = 0; i < NUM_FIFOS_NV04; i++)
            {
                if (pFifoHalPvtInfo->InUse & (1 << i))
                {
                    REG_WR32((U032)(pFbHalPvtInfo->fifoContextAddr + (i * 32) + SF_OFFSET(NV_RAMFC_DMA_GET)), 
                             REG_RD32((U032)(pFbHalPvtInfo->fifoContextAddr + (i * 32) + SF_OFFSET(NV_RAMFC_DMA_PUT))));

                    //
                    // Also, when setting the channels get pointer equal to its put, ensure the next
                    // DWORD is interpreted as a command (and not data) by clearing RAMFC_DMA_METHOD.
                    //
                    REG_WR32((U032)(pFbHalPvtInfo->fifoContextAddr + (i * 32) + SF_OFFSET(NV_RAMFC_DMA_METHOD)), 0x0);
                }
            }

            //
            // Restore CACHE1 state.
            //
            FIFOLOG(1, FifoPull, FifoReassign);
            REG_WR32(NV_PFIFO_CACHE1_PULL0, FifoPull);
            REG_WR32(NV_PFIFO_CACHE1_PUSH0, FifoPush);
            REG_WR32(NV_PFIFO_CACHES, FifoReassign);

            //
            // Flush all pending
            //
            REG_WR32(NV_PFIFO_DMA, 0);
            
            //
            // Disable all FIFO interrupts.
            //
            REG_WR32(NV_PFIFO_INTR_EN_0, 0);
            break;
        case FIFO_CONTROL_DESTROY:
            break;
        case FIFO_CONTROL_UPDATE:
            //
            // Update the dma fetch numbers
            //
            REG_WR32(NV_PFIFO_CACHE1_DMA_FETCH, 
                     DRF_DEF(_PFIFO, _CACHE1_DMA_FETCH, _TRIG, _128_BYTES) |
                     DRF_DEF(_PFIFO, _CACHE1_DMA_FETCH, _SIZE, _32_BYTES) |
                     DRF_DEF(_PFIFO, _CACHE1_DMA_FETCH, _MAX_REQS, _15));
            break;
        default:
            return (RM_ERR_BAD_ARGUMENT);
    }

    return (RM_OK);
}

RM_STATUS
nvHalFifoAllocPio_NV04(VOID *arg)
{
    PFIFOALLOCPIOARG_000 pFifoAllocPioArg = (PFIFOALLOCPIOARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFIFOHALINFO pFifoHalInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo;
    PFIFOHALINFO_NV04 pFifoHalPvtInfo;
    U032 CacheData, InitCtxtPtr;
    U032 i;

    // ASSERTIONS

    //
    // Verify interface revision.
    //
    if (pFifoAllocPioArg->id != FIFO_ALLOC_PIO_000)
        return (RM_ERR_VERSION_MISMATCH);

    //
    // Pull what we need out of argument structure.
    //
	pHalHwInfo = pFifoAllocPioArg->pHalHwInfo;
    pFifoHalInfo = pHalHwInfo->pFifoHalInfo;
    pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;
    pFifoHalPvtInfo = (PFIFOHALINFO_NV04)pHalHwInfo->pFifoHalPvtInfo;

    //
    // Disable cache reassignment.
    //
    CacheData = REG_RD32(NV_PFIFO_CACHES);
    REG_WR_DRF_DEF(_PFIFO_, CACHES, _REASSIGN, _DISABLED);

    //
    // Initialize freshly allocated FIFO context.
    //
    InitCtxtPtr = pFbHalPvtInfo->fifoContextAddr + (pFifoAllocPioArg->chid * 32);
    for (i = 0; i < 8; i++)
    {
        REG_WR32(InitCtxtPtr+(i*4), 0);
    }

    //
    // Set MODE to pio.
    //
    pFifoHalPvtInfo->Mode &= ~(1 << pFifoAllocPioArg->chid);
    REG_WR32(NV_PFIFO_MODE, pFifoHalPvtInfo->Mode);

    //
    // Is this channel in use?
    //
    if ((pFifoHalInfo->AllocateCount++ == 0)
     || (REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _CHID) == pFifoAllocPioArg->chid))
    {
        //
        // Disable cache1.
        //
        REG_WR_DRF_DEF(_PFIFO_, CACHE1_PUSH0, _ACCESS, _DISABLED);
        REG_WR_DRF_DEF(_PFIFO_, CACHE1_PULL0, _ACCESS, _DISABLED);
        FIFOLOG(1, 0, 0);
        //
        // Set initial cache parameters.
        //
        REG_WR_DRF_NUM(_PFIFO, _CACHE1_PUSH1, _CHID,    pFifoAllocPioArg->chid);
        REG_WR_DRF_NUM(_PFIFO, _CACHE1_PUT,   _ADDRESS, 0);
        REG_WR_DRF_NUM(_PFIFO, _CACHE1_GET,   _ADDRESS, 0);
        REG_WR32(NV_PFIFO_CACHE1_ENGINE, 0);
        //
        // Enable cache1.
        //
        FIFOLOG(1, 1, 1);
        REG_WR_DRF_DEF(_PFIFO_, CACHE1_PULL0, _ACCESS,   _ENABLED);
        REG_WR_DRF_DEF(_PFIFO_, CACHE1_PUSH0, _ACCESS,   _ENABLED);
        CacheData = DRF_DEF(_PFIFO_, CACHES, _REASSIGN, _ENABLED);
    }

    //
    // Restore previous cache reassignability.
    //
    REG_WR32(NV_PFIFO_CACHES, CacheData);

    //
    // Mark channel as allocated.
    //
    pFifoHalPvtInfo->InUse |= (1 << pFifoAllocPioArg->chid);

    return (RM_OK);
}

//
// nvHalFifoCalcDmaFetch
//
// Derive chip-dependent DMA fetch parameter register value
// from values specified at channel allocation time.
//
U032
nvHalFifoCalcDmaFetch_NV04(U032 fetchTrigger, U032 fetchSize, U032 fetchRequests)
{
    U032 dmaFetch;

    //
    // Input trigger value is in bytes.
    // Hardware value must be specified in increments of 8 between
    // 8 - 256 bytes.
    //
    if (fetchTrigger < 8) fetchTrigger = 8;
    if (fetchTrigger > 256) fetchTrigger = 256;
    fetchTrigger = (fetchTrigger / 8) - 1;

    //
    // Input size value is in bytes.
    // Hardware value must be specified in increments of 32
    // between 32 - 256 bytes.
    //
    if (fetchSize < 32) fetchSize = 32;
    if (fetchSize > 256) fetchSize = 256;
    fetchSize = (fetchSize / 32) - 1;

    //
    // Requests must be between 0 and 15.
    //
    if (fetchRequests > 15) fetchRequests = 15;

    //
    // Put it all together.
    //
    dmaFetch = DRF_NUM(_PFIFO, _CACHE1_DMA_FETCH, _TRIG, fetchTrigger) |
        DRF_NUM(_PFIFO, _CACHE1_DMA_FETCH, _SIZE, fetchSize) |
        DRF_NUM(_PFIFO, _CACHE1_DMA_FETCH, _MAX_REQS, fetchRequests);

    return dmaFetch;
}

RM_STATUS
nvHalFifoAllocDma_NV04(VOID *arg)
{
    PFIFOALLOCDMAARG_000 pFifoAllocDmaArg = (PFIFOALLOCDMAARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFIFOHALINFO pFifoHalInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo;
    PFIFOHALINFO_NV04 pFifoHalPvtInfo;
    U032 CacheData, InitCtxtPtr;
    U032 DefaultFetch;
    U032 DmaContext;
    U032 i;

    //
    // Verify interface revision.
    //
    if (pFifoAllocDmaArg->id != FIFO_ALLOC_DMA_000)
        return (RM_ERR_VERSION_MISMATCH);

    //
    // Pull what we need out of argument structure.
    //
	pHalHwInfo = pFifoAllocDmaArg->pHalHwInfo;
    pFifoHalInfo = pHalHwInfo->pFifoHalInfo;
    pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;
    pFifoHalPvtInfo = (PFIFOHALINFO_NV04)pHalHwInfo->pFifoHalPvtInfo;

    //
    // Validate push buffer state.
    //
    DmaContext = INST_RD32(pFifoAllocDmaArg->dmaInstance, SF_OFFSET(NV_DMA_CLASS));
    if (SF_VAL(_DMA, _TARGET_NODE, DmaContext) == NV_DMA_TARGET_NODE_NVM)
        return (RM_ERR_BAD_OBJECT_BUFFER);

    //
    // Disable cache reassignment.
    //
    CacheData = REG_RD32(NV_PFIFO_CACHES);
    REG_WR_DRF_DEF(_PFIFO_, CACHES, _REASSIGN, _DISABLED);
    
    //
    // Initialize freshly allocated FIFO context.
    //
    InitCtxtPtr = pFbHalPvtInfo->fifoContextAddr + (pFifoAllocDmaArg->chid * 32);
    for (i = 0 ; i < 8 ; i++ )
    {
        REG_WR32(InitCtxtPtr+(i*4), 0);
    }

    //
    // Insert the instance (note that the rest of the context can start as zero)
    //
    REG_WR32((U032)(InitCtxtPtr + SF_OFFSET(NV_RAMFC_DMA_INST)), pFifoAllocDmaArg->dmaInstance);

    DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM: nvHalFifoAllocateDma_NV04 - CACHE1 currently mapped to ChID ", REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _CHID));
    
    //
    // Adjust fetch max request (exception to the "all start as zero" rule)
    //
    DefaultFetch = nvHalFifoCalcDmaFetch_NV04(pFifoAllocDmaArg->fetchTrigger, pFifoAllocDmaArg->fetchSize, pFifoAllocDmaArg->fetchRequests);
    REG_WR32((U032)(InitCtxtPtr + SF_OFFSET(NV_RAMFC_DMA_FETCH_TRIG)), DefaultFetch);
    
    //
    // Set channel mode to dma
    //
    pFifoHalPvtInfo->Mode |= (1 << pFifoAllocDmaArg->chid);
    REG_WR32(NV_PFIFO_MODE, pFifoHalPvtInfo->Mode);

    //
    // Is this channel in use?
    //
    if ((pFifoHalInfo->AllocateCount++ == 0)
     || (REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _CHID) == pFifoAllocDmaArg->chid))
    {
        //
        // KJK Warning!!  We're getting in here if this is the first (0)
        // channel allocated in the system due to the checks above.
        // We really shouldn't be...
        //
        
        //
        // Disable cache1.
        //
        REG_WR_DRF_DEF(_PFIFO_, CACHE1_PUSH0, _ACCESS, _DISABLED);
        REG_WR_DRF_DEF(_PFIFO_, CACHE1_PULL0, _ACCESS, _DISABLED);
        FIFOLOG(1, 0, 0);
        //
        // Set initial cache parameters.
        //
        REG_WR_DRF_NUM(_PFIFO, _CACHE1_PUSH1, _CHID,   pFifoAllocDmaArg->chid);
        
        if (pFifoHalPvtInfo->Mode & (1 << pFifoAllocDmaArg->chid))
            FLD_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH1, _MODE, _DMA); 
        
        REG_WR_DRF_NUM(_PFIFO, _CACHE1_DMA_PUT, _OFFSET, 0);
        REG_WR_DRF_NUM(_PFIFO, _CACHE1_DMA_GET, _OFFSET, 0);
        
        REG_WR32(NV_PFIFO_CACHE1_DMA_INSTANCE, pFifoAllocDmaArg->dmaInstance);

        //
        // Force a reload of the PTE's
        //
        REG_WR32(NV_PFIFO_CACHE1_DMA_CTL, 0);
        
        //
        // Clear all pusher state
        //
        REG_WR32(NV_PFIFO_CACHE1_DMA_STATE, 0);
        
        REG_WR32(NV_PFIFO_CACHE1_ENGINE, 0);
        
        //
        // Set default watermarks
        //
        //REG_WR32(NV_PFIFO_CACHE1_DMA_FETCH, 0x000F6068);
        REG_WR32(NV_PFIFO_CACHE1_DMA_FETCH, DefaultFetch);
        
        //
        // Enable cache1.
        //
        if (pFifoHalPvtInfo->Mode & (1 << pFifoAllocDmaArg->chid))
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_DMA_PUSH, _ACCESS, _ENABLED);
        
        FIFOLOG(1, 1, 1);
        REG_WR_DRF_DEF(_PFIFO_, CACHE1_PULL0, _ACCESS,   _ENABLED);
        REG_WR_DRF_DEF(_PFIFO_, CACHE1_PUSH0, _ACCESS,   _ENABLED);
        CacheData = DRF_DEF(_PFIFO_, CACHES, _REASSIGN, _ENABLED);
    }

    //
    // Restore previous cache reassignability.
    //
    REG_WR32(NV_PFIFO_CACHES, CacheData);

    //
    // Mark channel as allocated.
    //
    pFifoHalPvtInfo->InUse |= (1 << pFifoAllocDmaArg->chid);

    return (RM_OK);
}

RM_STATUS
nvHalFifoFree_NV04(VOID *arg)
{
    PFIFOFREEARG_000 pFifoFreeArg = (PFIFOFREEARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFIFOHALINFO pFifoHalInfo;
    PFIFOHALINFO_NV04 pFifoHalPvtInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo;
    U032 FifoReassign, FifoPush, FifoPull;
    U032 InitCtxtPtr;
    U032 i;

    // ASSERTIONS

    //
    // Verify interface revision.
    //
    if (pFifoFreeArg->id != FIFO_FREE_000)
        return (RM_ERR_VERSION_MISMATCH);

    //
    // Pull what we need out of the argument structure.
    //
	pHalHwInfo = pFifoFreeArg->pHalHwInfo;
    pFifoHalInfo = pHalHwInfo->pFifoHalInfo;
    pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;
    pFifoHalPvtInfo = (PFIFOHALINFO_NV04)pHalHwInfo->pFifoHalPvtInfo;

    //
    // Save CACHE1 state.
    //
    FifoReassign = REG_RD32(NV_PFIFO_CACHES);
    FifoPush     = REG_RD32(NV_PFIFO_CACHE1_PUSH0);
    FifoPull     = REG_RD32(NV_PFIFO_CACHE1_PULL0);
    REG_WR_DRF_DEF(_PFIFO, _CACHES,       _REASSIGN, _DISABLED);
    REG_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH0, _ACCESS,   _DISABLED);
    REG_WR_DRF_DEF(_PFIFO, _CACHE1_PULL0, _ACCESS,   _DISABLED);
    FIFOLOG(4, 0, 0);

    //
    // Update the FIFO context and its dirty bits.
    //    
    if (REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _CHID) == pFifoFreeArg->chid)
    {
        REG_WR32(NV_PFIFO_CACHE1_ENGINE, 0);
        
        //
        // If this is a dma channel, we need to shut him down and clear out
        //
        if (pFifoHalPvtInfo->Mode & (1 << pFifoFreeArg->chid))
        {
            //
            // Disable dma pusher activity
            //
            REG_WR32(NV_PFIFO_CACHE1_DMA_PUSH, 0);
            
            //
            // Wait til idle
            //
            while (REG_RD_DRF(_PFIFO, _CACHE1_DMA_PUSH, _STATE) == NV_PFIFO_CACHE1_DMA_PUSH_STATE_BUSY)
			    ;
            
            //
            // Now zero everything out
            //
            REG_WR32(NV_PFIFO_CACHE1_DMA_PUT, 0);
            REG_WR32(NV_PFIFO_CACHE1_DMA_GET, 0);
            REG_WR32(NV_PFIFO_CACHE1_DMA_STATE, 0);
            REG_WR32(NV_PFIFO_CACHE1_DMA_FETCH, 0);
            REG_WR32(NV_PFIFO_CACHE1_DMA_TLB_PTE, 0);
            
            //
            // Move this channel back to PIO.  This way any inadvertant writes will go to runout.
            //
            pFifoHalPvtInfo->Mode &= ~(1 << pFifoFreeArg->chid);
            REG_WR32(NV_PFIFO_MODE, pFifoHalPvtInfo->Mode);
        }        
    }
    else
    {
        //
        // Flush the context into the FIFO context RAM.
        //
        InitCtxtPtr = pFbHalPvtInfo->fifoContextAddr + (pFifoFreeArg->chid * 32);
        for (i = 0; i < 8; i++)
        {
            REG_WR32(InitCtxtPtr+(4*i), 0);
        }
        
        //
        // If this is a dma channel, make sure we clear any pending pushing
        //
        if (pFifoHalPvtInfo->Mode & (1 << pFifoFreeArg->chid))
        {
            //
            // Clear any pending transfers
            //
            REG_WR32(NV_PFIFO_DMA, REG_RD32(NV_PFIFO_DMA) & (~(1 << pFifoFreeArg->chid)));
            
            //
            // Move this channel back to PIO.  This way any inadvertant writes will go to runout.
            //
            pFifoHalPvtInfo->Mode &= ~(1 << pFifoFreeArg->chid);
            REG_WR32(NV_PFIFO_MODE, pFifoHalPvtInfo->Mode);
        }
    }

    //
    // Restore CACHE1 state.
    //
    FIFOLOG(4, FifoPull, FifoReassign);
    REG_WR32(NV_PFIFO_CACHE1_PULL0, FifoPull);
    REG_WR32(NV_PFIFO_CACHE1_PUSH0, FifoPush);
    REG_WR32(NV_PFIFO_CACHES, FifoReassign);

    //
    // Free up channel.
    //
    pFifoHalPvtInfo->InUse &= ~(1 << pFifoFreeArg->chid);

    pFifoHalInfo->AllocateCount--;

    return (RM_OK);
}

//
// nvHalFifoContextSwitch
//
// Context switch the fifo.
//
static RM_STATUS
nvHalFifoContextSwitch_NV04(PHALHWINFO pHalHwInfo, U032 ChID)
{
    PFIFOHALINFO pFifoHalInfo = pHalHwInfo->pFifoHalInfo;
    PFIFOHALINFO_NV04 pFifoHalPvtInfo = (PFIFOHALINFO_NV04)pHalHwInfo->pFifoHalPvtInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;
    U032 FifoReassign, FifoPush, FifoPull;
    U032 CurrentChID;
    U032 PushPending;
    U032 CtxtPtr = (U032)pFbHalPvtInfo->fifoContextAddr;

    //if (id != FIFO_CONTEXT_SWITCH)
    //    return (HAL_ERROR);

    //
    // Save CACHE1 state.
    //
    FifoReassign = REG_RD32(NV_PFIFO_CACHES);
    FifoPush = REG_RD32(NV_PFIFO_CACHE1_PUSH0);
    FifoPull = REG_RD32(NV_PFIFO_CACHE1_PULL0);
    REG_WR_DRF_DEF(_PFIFO, _CACHES, _REASSIGN, _DISABLED);
    REG_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH0, _ACCESS, _DISABLED);
    REG_WR_DRF_DEF(_PFIFO, _CACHE1_PULL0, _ACCESS, _DISABLED);
    FIFOLOG(1, 0, 0);
    
    //
    // Make sure our local (rm) contexts are up to date for the outgoing channel
    //
    CurrentChID = REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _CHID); 

    DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM: Manually saving the FIFO context on ChID: ", CurrentChID);

    REG_WR32((U032)(CtxtPtr + (CurrentChID * 32) + SF_OFFSET(NV_RAMFC_DMA_PUT)), REG_RD32(NV_PFIFO_CACHE1_DMA_PUT));
    REG_WR32((U032)(CtxtPtr + (CurrentChID * 32) + SF_OFFSET(NV_RAMFC_DMA_GET)), REG_RD32(NV_PFIFO_CACHE1_DMA_GET));
    REG_WR32((U032)(CtxtPtr + (CurrentChID * 32) + SF_OFFSET(NV_RAMFC_DMA_INST)), REG_RD32(NV_PFIFO_CACHE1_DMA_INSTANCE));
    REG_WR32((U032)(CtxtPtr + (CurrentChID * 32) + SF_OFFSET(NV_RAMFC_DMA_METHOD)), REG_RD32(NV_PFIFO_CACHE1_DMA_STATE));
    REG_WR32((U032)(CtxtPtr + (CurrentChID * 32) + SF_OFFSET(NV_RAMFC_DMA_FETCH_TRIG)), REG_RD32(NV_PFIFO_CACHE1_DMA_FETCH));
    REG_WR32((U032)(CtxtPtr + (CurrentChID * 32) + SF_OFFSET(NV_RAMFC_ENGINE_SUB_0)), REG_RD32(NV_PFIFO_CACHE1_ENGINE));
    REG_WR32((U032)(CtxtPtr + (CurrentChID * 32) + SF_OFFSET(NV_RAMFC_PULL1_ENGINE)), REG_RD32(NV_PFIFO_CACHE1_PULL1));
    
    //
    // If this is a push channel and put != get, make sure to set the push pending flag
    //
    if (REG_RD32(NV_PFIFO_CACHE1_PUSH1) & DRF_DEF(_PFIFO, _CACHE1_PUSH1, _MODE, _DMA))
    {    
        PushPending = REG_RD32(NV_PFIFO_DMA) & ~(1 << CurrentChID);
        if (REG_RD32(NV_PFIFO_CACHE1_DMA_PUT) != REG_RD32(NV_PFIFO_CACHE1_DMA_GET))
            PushPending |= (1 << CurrentChID);
        REG_WR32(NV_PFIFO_DMA, PushPending);
    }                    
    
    //
    // Bring in the context for the new channel from the fifo context ram.
    //
    DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM: Manually restoring the FIFO context on ChID: ", ChID);

    //
    // Update the channel and if it's DMA, set the mode
    //
    REG_WR_DRF_NUM(_PFIFO, _CACHE1_PUSH1, _CHID, ChID);
    if ((pFifoHalPvtInfo->Mode & (1 << ChID)) && (ChID != (NUM_FIFOS_NV04 - 1)))
        FLD_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH1, _MODE, _DMA); 
    
    REG_WR32(NV_PFIFO_CACHE1_DMA_PUT, REG_RD32((U032)(CtxtPtr + (ChID * 32) + SF_OFFSET(NV_RAMFC_DMA_PUT))));
    REG_WR32(NV_PFIFO_CACHE1_DMA_GET, REG_RD32((U032)(CtxtPtr + (ChID * 32) + SF_OFFSET(NV_RAMFC_DMA_GET))));
    REG_WR32(NV_PFIFO_CACHE1_DMA_INSTANCE, REG_RD32((U032)(CtxtPtr + (ChID * 32) + SF_OFFSET(NV_RAMFC_DMA_INST))));
    REG_WR32(NV_PFIFO_CACHE1_DMA_STATE, REG_RD32((U032)(CtxtPtr + (ChID * 32) + SF_OFFSET(NV_RAMFC_DMA_METHOD))));
    REG_WR32(NV_PFIFO_CACHE1_DMA_FETCH, REG_RD32((U032)(CtxtPtr + (ChID * 32) + SF_OFFSET(NV_RAMFC_DMA_FETCH_TRIG))));
    REG_WR32(NV_PFIFO_CACHE1_ENGINE, REG_RD32((U032)(CtxtPtr + (ChID * 32) + SF_OFFSET(NV_RAMFC_ENGINE_SUB_0))));
    REG_WR32(NV_PFIFO_CACHE1_PULL1, REG_RD32((U032)(CtxtPtr + (ChID * 32) + SF_OFFSET(NV_RAMFC_PULL1_ENGINE))));
         
    //
    // If DMA, enable the DMA Pusher
    //
    if ((pFifoHalPvtInfo->Mode & (1 << ChID)) && (ChID != (NUM_FIFOS_NV04 - 1)))
        REG_WR_DRF_DEF(_PFIFO, _CACHE1_DMA_PUSH, _ACCESS, _ENABLED);

    //
    // In case there are dma pusher channels still pending, give this
    // new channel enough time to do something useful before it gets
    // yanked back out again.
    //
    REG_WR32(NV_PFIFO_TIMESLICE, 0x1fffff);     
           
    //
    // Restore CACHE1 state.
    //
    FIFOLOG(1, FifoPull, FifoReassign);
    REG_WR32(NV_PFIFO_CACHE1_PULL0, FifoPull);
    REG_WR32(NV_PFIFO_CACHE1_PUSH0, FifoPush);
    REG_WR32(NV_PFIFO_CACHES, FifoReassign);

    return (RM_OK);
}

//
// nvHalFifoGetExceptionData
//
RM_STATUS
nvHalFifoGetExceptionData_NV04(VOID *arg)
{
    PFIFOGETEXCEPTIONDATAARG_000 pFifoGetExceptionDataArg = (PFIFOGETEXCEPTIONDATAARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFIFOEXCEPTIONDATA pFifoExceptionData;
    U032 GetPtr;

    //
    // Verify interface revision.
    //
    if (pFifoGetExceptionDataArg->id != FIFO_GET_EXCEPTION_DATA_000)
        return (RM_ERR_VERSION_MISMATCH);

	pHalHwInfo = pFifoGetExceptionDataArg->pHalHwInfo;
    pFifoExceptionData = pFifoGetExceptionDataArg->pExceptionData;

    //
    // Fill in exception data.
    //
    pFifoExceptionData->Reason = REG_RD32(NV_PFIFO_CACHE1_PULL0);
    pFifoExceptionData->ChID = REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _CHID);
    GetPtr = REG_RD32(NV_PFIFO_CACHE1_GET) >> 2;
    pFifoExceptionData->GetPtr = GetPtr;
    pFifoExceptionData->SubChannel =
        (((REG_RD32(NV_PFIFO_CACHE1_METHOD(GetPtr))) >> DRF_SHIFT(NV_PFIFO_CACHE1_METHOD_SUBCHANNEL)) & 
         DRF_MASK(NV_PFIFO_CACHE1_METHOD_SUBCHANNEL));
    pFifoExceptionData->Method = REG_RD32(NV_PFIFO_CACHE1_METHOD(GetPtr)) & 0x1FFC;
    pFifoExceptionData->Data = REG_RD32(NV_PFIFO_CACHE1_DATA(GetPtr));

    return (RM_OK);
}

//
// nvHalFifoService
//
RM_STATUS
nvHalFifoService_NV04(VOID *arg)
{
    PFIFOSERVICEARG_000 pFifoServiceArg = (PFIFOSERVICEARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFIFOEXCEPTIONDATA pFifoExceptionData;
    PFIFOHALINFO pFifoHalInfo;
    PFIFOHALINFO_NV04 pFifoHalPvtInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo;

    //
    // Verify interface revision.
    //
    if (pFifoServiceArg->id != FIFO_SERVICE_000)
        return (RM_ERR_VERSION_MISMATCH);
    
 	pHalHwInfo = pFifoServiceArg->pHalHwInfo;
    pFifoExceptionData = pFifoServiceArg->pExceptionData;
    pFifoHalInfo = pHalHwInfo->pFifoHalInfo;
    pFifoHalPvtInfo = (PFIFOHALINFO_NV04)pHalHwInfo->pFifoHalPvtInfo;
    pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;

    //
    // Now service any exceptions that we'd like to handle w/i the HAL.
    //
    if (pFifoServiceArg->intr & DRF_DEF(_PFIFO, _INTR_0, _RUNOUT, _PENDING))
    {
        U032 GetPtr;
        U032 ChID;
        U032 SubChannel;
        U032 Type;
        U032 Reason;
        U032 Method;
        U032 Data;
        U032 FifoPush, wasDmaChannel = 0;

        //
        // Deal with data in runout.
        //
        DBG_PRINT_STRING(DEBUGLEVEL_USERERRORS, "NVRM: Cache ranout.  Waiting for cache to drain.\n\r");
        DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM:         CACHE1 ChID = ", REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _CHID));

        //
        // Don't allow another channel to switch in
        //
        REG_WR_DRF_DEF(_PFIFO_, CACHES,       _REASSIGN, _DISABLED);

        //
        // Disable CACHE1_PUSH0, so we're able to safely resubmit the runout method/data
        // back into the CACHE1 below.
        // 
        FifoPush = REG_RD32(NV_PFIFO_CACHE1_PUSH0);
        REG_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH0, _ACCESS,   _DISABLED);
        
        //
        // If this is a DMA channel, start to shut down the current pushing
        //
        if (REG_RD32(NV_PFIFO_CACHE1_PUSH1) & DRF_DEF(_PFIFO, _CACHE1_PUSH1, _MODE, _DMA))
        {
            FLD_WR_DRF_DEF(_PFIFO, _CACHE1_DMA_PUSH, _ACCESS, _DISABLED);
            wasDmaChannel = 1;      // started this interrupt as a DMA channel
        }
            
        //
        // First wait for cache to drain and the dma pusher to be idle
        //
        if ((REG_RD_DRF(_PFIFO, _CACHE1_STATUS, _LOW_MARK) == NV_PFIFO_CACHE1_STATUS_LOW_MARK_EMPTY) &&
            (REG_RD_DRF(_PFIFO, _CACHE1_DMA_PUSH, _STATE) == NV_PFIFO_CACHE1_DMA_PUSH_STATE_IDLE))
        {            
            //
            // Cache is empty.  Deal with data in runout.
            //
            REG_WR_DRF_DEF(_PFIFO, _CACHE1_PULL0, _ACCESS,   _DISABLED);
            FIFOLOG(1, 0, 0);

            //
            // Since the CACHE1 has been idled, let's move its PUT/GET to the top
            // of the FIFO avoiding any overflow issues during the resubmit.
            //
#ifdef DEBUG
            if (REG_RD32(NV_PFIFO_CACHE1_PUT) != REG_RD32(NV_PFIFO_CACHE1_GET))
                DBG_BREAKPOINT();
#endif // DEBUG

            REG_WR32(NV_PFIFO_CACHE1_PUT, 0x0);
            REG_WR32(NV_PFIFO_CACHE1_GET, 0x0);

            //
            // Because we've taken the trouble to idle everything, rather than dump
            // a single method/data into the CACHE1 and wait, we'll resubmit all the
            // outstanding runout method/data back into the CACHE1.
            //
            DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM: RunOut_PUT        = ", REG_RD32(NV_PFIFO_RUNOUT_PUT));
            DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM: RunOut_GET        = ", REG_RD32(NV_PFIFO_RUNOUT_GET));

            while (REG_RD32(NV_PFIFO_RUNOUT_PUT) != REG_RD32(NV_PFIFO_RUNOUT_GET))
            {
                //
                // Read FIFO state.
                //
                GetPtr     = REG_RD32(NV_PFIFO_RUNOUT_GET);
                Data       = REG_RD32(pFbHalPvtInfo->fifoRunoutAddr + GetPtr);
                DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM:       RunOut Method = ", Data);

                ChID       = SF_VAL(_RAMRO, _CHID, Data);
                Type       = SF_VAL(_RAMRO, _TYPE, Data);
                Reason     = SF_VAL(_RAMRO, _REASON, Data);
                Method     = SF_VAL(_RAMRO, _METHOD, Data) & 0x1FFF;
                SubChannel = SF_VAL(_RAMRO, _SUBCHANNEL, Data) & 0x7;

                Data       = REG_RD32(pFbHalPvtInfo->fifoRunoutAddr + GetPtr + 4);
                DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM:       RunOut Data   = ", Data);

                //
                // Set user cache state to look just as if the runout came
                // from the bottom on the FIFO.  This keeps the OBJECT_CHANGED
                // bits in order.
                //
                if ((Type   == NV_RAMRO_TYPE_WRITE)
                    && (Reason != NV_RAMRO_REASON_ILLEGAL_ACCESS)
                    && (Reason != NV_RAMRO_REASON_RESERVED_ACCESS))
                {
                    if ((ChID < NUM_FIFOS_NV04) && pFifoHalPvtInfo->InUse)
                    {
                        U032 Cache1Put;

                        //
                        // Since the fifo engine/resmgr no longer tracks object context on a per-subchannel
                        // basis, the only thing we can do with runout methods is to send them back down
                        // the main user fifo.
                        //
                        // Do we need to force a channel change?
                        //
                    
                        if (REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _CHID) != ChID)
                        {
                            nvHalFifoContextSwitch_NV04(pHalHwInfo, ChID);

                            //
                            // If we started out the interrupt as a DMA channel and have switched into
                            // a PIO channel, make sure to clear the SUSPEND bit (but don't reenable). 
                            // The HW likes to see this bit cleared after an intr and since we now look
                            // like a PIO channel, we'll just clear it here.
                            // 
                            if (wasDmaChannel && (REG_RD_DRF(_PFIFO, _CACHE1_PUSH1, _MODE) == 0))
                                FLD_WR_DRF_DEF(_PFIFO, _CACHE1_DMA_PUSH, _STATUS, _RUNNING);
                        }

                        //
                        // Resubmit
                        //
                        Cache1Put = REG_RD_DRF(_PFIFO, _CACHE1_PUT, _ADDRESS);
                        DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO,
                                                   "NVRM: Cache runout resubmit to CACHE1 addr:", Cache1Put << 2);

                        REG_WR32(NV_PFIFO_CACHE1_METHOD(Cache1Put), 
                            Method | DRF_NUM(_PFIFO, _CACHE0_METHOD, _SUBCHANNEL, SubChannel));
                        REG_WR32(NV_PFIFO_CACHE1_DATA(Cache1Put), Data);

                        //
                        // Update the CACHE1 Put ptr.
                        // There are no overflow worries, since we started at the top of the CACHE1
                        //
                        Cache1Put++;
                        REG_WR_DRF_NUM(_PFIFO, _CACHE1_PUT, _ADDRESS, Cache1Put);
                    }
                    else
                    {
                        DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM: Access to free channel:", ChID);
                        DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "                 sub channel:", SubChannel);
                        DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "                      offset:", Method);
                        DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "                        data:", Data);
                        DBG_BREAKPOINT();
                    }
                }
            
                //
                // Advance the RunOut get pointer.
                //
                GetPtr = (GetPtr + 8) & pFbHalPvtInfo->fifoRunoutMask;
                REG_WR32(NV_PFIFO_RUNOUT_GET, GetPtr);
                GetPtr = REG_RD32(NV_PFIFO_RUNOUT_GET);      // flush delay to update runout_status
            }

            //
            // Clear condition if no more data in runout.
            //
            if (REG_RD32(NV_PFIFO_RUNOUT_STATUS) & DRF_DEF(_PFIFO, _RUNOUT_STATUS, _LOW_MARK, _EMPTY))
            {
                DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM: RunOut has CAUGHT UP:", GetPtr);
                REG_WR_DRF_DEF(_PFIFO, _INTR_0, _RUNOUT, _RESET);
            } else {
                DBG_PRINT_STRING_VALUE(DEBUGLEVEL_TRACEINFO, "NVRM: RunOut should be CAUGHT UP:", GetPtr);
                DBG_BREAKPOINT();
            }
        }
        else
        {
            //
            // Enable the puller to empty the cache.
            //
            FIFOLOG(1, 1, 0);
            REG_WR_DRF_DEF(_PFIFO_, CACHE1_PULL0, _ACCESS, _ENABLED);
        }

        // restore CACHE1_PUSH0 state
        REG_WR32(NV_PFIFO_CACHE1_PUSH0, FifoPush);
    }
    return (RM_OK);
}

//
// nvHalFifoAccess
//
RM_STATUS
nvHalFifoAccess_NV04(VOID *arg)
{
    PFIFOACCESSARG_000 pFifoAccessArg = (PFIFOACCESSARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFIFOACCESSINFO pFifoAccessInfo;

    //
    // Verify interface revision.
    //
    if (pFifoAccessArg->id != FIFO_ACCESS_000)
        return (RM_ERR_VERSION_MISMATCH);

	pHalHwInfo = pFifoAccessArg->pHalHwInfo;
    pFifoAccessInfo = pFifoAccessArg->pAccessInfo;

    switch (pFifoAccessArg->cmd) {
    case FIFO_ACCESS_DISABLE:
        pFifoAccessInfo->FifoReassign = REG_RD32(NV_PFIFO_CACHES);
        pFifoAccessInfo->FifoPush = REG_RD32(NV_PFIFO_CACHE1_PUSH0);
        pFifoAccessInfo->FifoPull = REG_RD32(NV_PFIFO_CACHE1_PULL0);
        REG_WR_DRF_DEF(_PFIFO, _CACHES,       _REASSIGN, _DISABLED);
        REG_WR_DRF_DEF(_PFIFO, _CACHE1_PUSH0, _ACCESS,   _DISABLED);
        REG_WR_DRF_DEF(_PFIFO, _CACHE1_PULL0, _ACCESS,   _DISABLED);
        break;
    case FIFO_ACCESS_ENABLE:
        REG_WR32(NV_PFIFO_CACHE1_PULL0, pFifoAccessInfo->FifoPull);
        REG_WR32(NV_PFIFO_CACHE1_PUSH0, pFifoAccessInfo->FifoPush);
        REG_WR32(NV_PFIFO_CACHES, pFifoAccessInfo->FifoReassign);
        break;
    default:
        return (RM_ERR_BAD_ARGUMENT);
    }
    return (RM_OK);
}

//
// nvHalFifoHashAdd
//
RM_STATUS
nvHalFifoHashAdd_NV04(VOID *arg)
{
    PFIFOHASHADDARG_000 pFifoHashAddArg = (PFIFOHASHADDARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFIFOHALINFO pFifoHalInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo;
    PHWREG nvAddr;
    HASH_TABLE_ENTRY *hwHashTable;

    // ASSERTIONS

    //
    // Verify interface revision.
    //
    if (pFifoHashAddArg->id != FIFO_HASH_ADD_000)
        return (RM_ERR_VERSION_MISMATCH);

	pHalHwInfo = pFifoHashAddArg->pHalHwInfo;
    pFifoHalInfo = pHalHwInfo->pFifoHalInfo; 
    pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;
    nvAddr = pHalHwInfo->nvBaseAddr;
    hwHashTable = (HASH_TABLE_ENTRY *)((U008*)(nvAddr) + pFbHalPvtInfo->hashTableAddr);

    REG_WR32_DIRECT(&hwHashTable[pFifoHashAddArg->entry].ht_ObjectHandle, pFifoHashAddArg->handle);
    REG_WR32_DIRECT(&hwHashTable[pFifoHashAddArg->entry].ht_Context, (pFifoHashAddArg->instance & SF_MASK(NV_RAMHT_INSTANCE)) |
                                                   (pFifoHashAddArg->engine << SF_SHIFT(NV_RAMHT_ENGINE)) |
                                                   (pFifoHashAddArg->chid << SF_SHIFT(NV_RAMHT_CHID)) |
                                                   (NV_RAMHT_STATUS_VALID << SF_SHIFT(NV_RAMHT_STATUS)));
    
    return (RM_OK);
}

//
// nvHalHashDelete
//
RM_STATUS
nvHalFifoHashDelete_NV04(VOID *arg)
{
    PFIFOHASHDELETEARG_000 pFifoHashDeleteArg = (PFIFOHASHDELETEARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo;
    HASH_TABLE_ENTRY *hwHashTable;
    PHWREG nvAddr;

    // ASSERTIONS

    //
    // Verify interface revision.
    //
    if (pFifoHashDeleteArg->id != FIFO_HASH_DELETE_000)
        return (RM_ERR_VERSION_MISMATCH);

	pHalHwInfo = pFifoHashDeleteArg->pHalHwInfo;
    nvAddr = pHalHwInfo->nvBaseAddr;
    pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;
    hwHashTable = (HASH_TABLE_ENTRY *)((U008*)(nvAddr) + pFbHalPvtInfo->hashTableAddr);

    REG_WR32_DIRECT(&hwHashTable[pFifoHashDeleteArg->entry].ht_ObjectHandle, 0);
    REG_WR32_DIRECT(&hwHashTable[pFifoHashDeleteArg->entry].ht_Context, 0);

    return (RM_OK);
}

RM_STATUS
nvHalFifoHashFunc_NV04(VOID *arg)
{
    PFIFOHASHFUNCARG_000 pFifoHashFuncArg = (PFIFOHASHFUNCARG_000)arg;

    // ASSERTIONS

    //
    // Verify interface revision.
    //
    if (pFifoHashFuncArg->id != FIFO_HASH_FUNC_000)
        return (RM_ERR_VERSION_MISMATCH);

    pFifoHashFuncArg->result = FIFO_HASH(pFifoHashFuncArg->handle, pFifoHashFuncArg->chid);

    return (RM_OK);    
}

RM_STATUS
nvHalFifoHashSearch_NV04(VOID *arg)
{
    PFIFOHASHSEARCHARG_000 pFifoHashSearchArg = (PFIFOHASHSEARCHARG_000)arg;
    PHALHWINFO pHalHwInfo;
    PPRAMHALINFO pPramHalInfo;
    PFBHALINFO_NV04 pFbHalPvtInfo;
    HASH_TABLE_ENTRY *hwHashTable;
    PHWREG nvAddr;
    U032 Entry;

    // ASSERTIONS

    //
    // Verify interface revision.
    //
    if (pFifoHashSearchArg->id != FIFO_HASH_SEARCH_000)
        return (RM_ERR_VERSION_MISMATCH);

	pHalHwInfo = pFifoHashSearchArg->pHalHwInfo;
    pFbHalPvtInfo = (PFBHALINFO_NV04)pHalHwInfo->pFbHalPvtInfo;
    nvAddr = pHalHwInfo->nvBaseAddr;
    pPramHalInfo = pHalHwInfo->pPramHalInfo; 
    hwHashTable = (HASH_TABLE_ENTRY *)((U008*)(nvAddr) + pFbHalPvtInfo->hashTableAddr);

    pFifoHashSearchArg->result = 0x0;

    // Attempt to find a valid entry in the Hash (checking Name and ChID)
    for (Entry = 0; Entry < pPramHalInfo->HashDepth; Entry++)
    {
        if (REG_RD32_DIRECT(&hwHashTable[Entry].ht_ObjectHandle) == pFifoHashSearchArg->handle)
        {
            U032 chid, valid;
            U032 context = REG_RD32_DIRECT(&hwHashTable[Entry].ht_Context);
             
            chid  = context >> SF_SHIFT(NV_RAMHT_CHID) & SF_MASK(NV_RAMHT_CHID);
            valid = context >> SF_SHIFT(NV_RAMHT_STATUS) & SF_MASK(NV_RAMHT_STATUS);

            if ((valid == NV_RAMHT_STATUS_VALID) && (chid == pFifoHashSearchArg->chid))
            {
                pFifoHashSearchArg->result = context;
                break;
            }
        }
    }

    return (RM_OK);
}
