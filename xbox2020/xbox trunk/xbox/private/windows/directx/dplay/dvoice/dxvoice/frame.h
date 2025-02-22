/*==========================================================================
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:		frame.h
 *  Content:	declaration of the CFrame and CFramePool classes
 *		
 *  History:
 *   Date		By		Reason
 *   ====		==		======
 * 07/16/99		pnewson	Created
 * 09/01/2000   georgioc started xbox port/rewrite
 ***************************************************************************/

#ifndef _FRAME_H_
#define _FRAME_H_

#include <dvoicep.h>
#include "dvshared.h"

// forward declaration
class CFramePool;

//
// we need to be able to return 0 length frames for silence. SO the number of frames
// we preallocate needs to be larger than the max number of speech frames we expect
// buffered at any time
//

#define FRAME_POOL_MAX_FRAMES   DV_CT_FRAMES_PER_PERIOD*2

#define VSIG_FRAME		'MRFV'
#define VSIG_FRAME_FREE	'MRF_'

// This class is designed to manage one frame of sound data.
//
// tag: fr
volatile class CFrame
{
private:

	DWORD				m_dwSignature;

    // Length of the data within the frame.  There may be less then a whole
    // frame worth of data in the buffer due to compression/decompression may
    // result in a slightly different size buffer.
    WORD m_wFrameLength;

	// The size of this frame.  It would be easier to make
	// this a class constant, but we're probably going to want to 
	// toy with the frame sizes while we're optimizing, and
	// we may even get really fancy in the future and have
	// the client and server negotiate the frame size at connection
	// time, all of which will be easier if we bite the bullet now
	// and make this a member variable.  Note this is constant,
	// so once a frame is instantiated, it's size is permanently set.
	WORD m_wFrameSize;

	// The client number this frame is coming from or
	// going to.
	WORD m_wClientId;

	// The frame sequence number.
	BYTE m_wSeqNum;

	// The message number the frame is part of
    BYTE m_bMsgNum;

    // The target of the frame
    PDVID m_pdvidTargets;
    DWORD m_dwNumTargets;
    DWORD m_dwMaxTargets;

    bool m_fOwned;

	// A flag to specify that this frame contains nothing but silence.
	// When this flag is set, the data in the frame buffer should not 
	// be used - it's probably not valid.
	BYTE m_bIsSilence;

	// A pointer to the frame's data
	BYTE* m_pbData;

	// If this frame is part of a managed frame pool, this
	// member will be non-null.
	CFramePool* m_pFramePool;

	// A flag to indicate if this frame was "lost". This is
	// used to distinguish the silent frames pulled from the
	// queue between messages from the dead space caused by 
	// a known lost packet.
	bool m_fIsLost;


	// don't allow copy construction or assignment of these
	// structures, as this would kill our performance, and
	// we don't want to do it by accident
	CFrame(const CFrame& fr);
	CFrame& operator=(const CFrame& fr);

public:

    __inline void *__cdecl operator new(size_t size)
    {
        return ExAllocatePoolWithTag(size, 'etnv');
    }

    __inline void __cdecl operator delete(void *pv)
    {
        ExFreePool(pv);
    }

    LIST_ENTRY  m_FramePoolEntry;

	// This constructor sets all the frame's info, and allocates
	// the data buffer, but does not set the data inside the buffer
	// to anything.  Defaults are provided for all the parameters
	// except for the frame size.  Note: no default constructor,
	// since you must specify the frame size.
	CFrame(WORD wFrameSize, 
		WORD wClientNum = 0,
		BYTE wSeqNum = 0,
        BYTE bMsgNum = 0,
		BYTE bIsSilence = 0,
		CFramePool *pFramePool = NULL);

	// A frame which manages user ownded memory
	CFrame();

	// The destructor cleans up the memory allocated by the
	// constructor
	~CFrame();

	inline DWORD GetNumTargets() const { return m_dwNumTargets; };
	inline const PDVID GetTargetList() const { return m_pdvidTargets; };

    // Length of the data within the buffer
    WORD GetFrameLength() const { return m_wFrameLength; }

	// returns the frame size, (the length of the data buffer)
	WORD GetFrameSize() const { return m_wFrameSize; }

	HRESULT SetEqual( const CFrame &frSourceFrame );

	// These are just a bunch of set and get functions for 
	// the simple parts of the class, the client id, the
	// sequence number, the silence flag, etc.
    HRESULT GetTargets( PDVID pdvidTargets, PDWORD pdwNumTargets ) const;
    HRESULT SetTargets( PDVID pdvidTargets, DWORD dwNumTargets );
    
    BYTE GetMsgNum() const { return m_bMsgNum; }
    void SetMsgNum( BYTE msgNum ) { m_bMsgNum = msgNum; }
	void SetClientId(WORD wClientId) {	m_wClientId = wClientId; }
	WORD GetClientId() const {	return m_wClientId;	}
	void SetSeqNum(BYTE wSeqNum) {	m_wSeqNum = wSeqNum; }
	BYTE GetSeqNum() const { return m_wSeqNum; }
	void SetIsSilence(BYTE bIsSilence) { m_bIsSilence = bIsSilence; }
    void SetFrameLength(const WORD &length) { m_wFrameLength = length; }
	BYTE GetIsSilence() const { return m_bIsSilence; }
	bool GetIsLost() const { return m_fIsLost;	}
	void SetIsLost(bool fIsLost) {	m_fIsLost = fIsLost; }
	
	// Now we have the functions which handle the data.  This
	// class is pretty trusting, because it will give out the
	// pointer to it's data.  This is to avoid all non-required
	// buffer copies.  For example, when you hand a buffer to
	// a wave in function, you can give it the pointer to this
	// buffer, and it will fill in the frame's buffer directly.
	// Between this function and the GetFrameSize() and 
	// GetFrameLength() functions, you can do anything you want 
	// with the buffer.
	BYTE* GetDataPointer() const { return m_pbData; }

	// This copies the data from another frame into this frame
	void CopyData(const CFrame& fr)
	{
		memcpy(m_pbData, fr.GetDataPointer(), fr.GetFrameLength() );
        m_wFrameLength = fr.GetFrameLength();
	}

	void UserOwn_SetData( BYTE *pbData, DWORD dwLength )
	{
		m_pbData = pbData;
		m_wFrameLength = (WORD)dwLength;
		m_wFrameSize = (WORD)dwLength;
	}

	void UserOwn_SetTargets( PDVID pdvidTargets, DWORD dwNumTargets )
	{
		m_pdvidTargets = pdvidTargets;
		m_dwNumTargets = dwNumTargets;
		m_dwMaxTargets = dwNumTargets;
	}

	// This copies data from a buffer into this frame's
	// buffer.
	void CopyData(const BYTE* pbData, WORD wFrameLength);

	// If this frame is part of a frame pool managed by a
	// CFramePool object, then call this function when you 
	// are done with the frame and want to return it to the
	// pool.
    void Return();

	void SetFramePool(CFramePool* pFramePool) { m_pFramePool = pFramePool;	}
};

// This class manages a pool of frames, to reduce memory requirements.
// Only a few buffers are actually in use at any time by the queue
// class, and yet it may have to allocate hundreds of them unless 
// a class such as this is used to manage their reuse.
volatile class CFramePool
{
private:
	// the pool is simply a vector of frame objects
    
    LIST_ENTRY m_FramePool;

	// All the frames in the pool must be the same size,
	// which is stored here.
	WORD m_wFrameSize;

	#if defined(DEBUG) || defined(DBG)
    // Used to detect runaway frame pool usage.
    LONG m_lCount;
    #endif
	
public:

    __inline void *__cdecl operator new(size_t size)
    {
        return ExAllocatePoolWithTag(size, 'etnv');
    }

    __inline void __cdecl operator delete(void *pv)
    {
        ExFreePool(pv);
    }



	// Each frame pool manages frames of a certain size,
	// so they can be easily reused. If you need multiple
	// different frame sizes, you'll need more than one 
	// frame pool.
	CFramePool(WORD wFrameSize); 
	~CFramePool();

	// Use Get to retrieve a frame from the pool.
	CFrame* Get();

	// Call Return to give a frame back to the frame pool. 
	// This may set a pointer to null and enter a critical
	// section, as described in Get() above.
	void Return(CFrame* pFrame);
};


#endif /* _FRAME_H_ */
