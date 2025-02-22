#pragma once


// CD audio type conversions

#define CDAUDIO_BYTES_PER_FRAME         2352
#define CDAUDIO_BYTES_PER_SECOND        176400
#define CDAUDIO_BYTES_PER_MINUTE        10584000

#define CDAUDIO_FRAMES_PER_SECOND       75
#define CDAUDIO_FRAMES_PER_MINUTE       4500

// MCI time format conversion macros

#define MCI_MSF_MINUTE(msf)             ((BYTE)(msf))
#define MCI_MSF_SECOND(msf)             ((BYTE)(((WORD)(msf)) >> 8))
#define MCI_MSF_FRAME(msf)              ((BYTE)((msf)>>16))

#define MCI_MAKE_MSF(m, s, f)           ((DWORD)(((BYTE)(m) | \
                                        ((WORD)(s)<<8)) | \
                                        (((DWORD)(BYTE)(f))<<16)))

__inline DWORD MsfToFrames(DWORD dwMsf)
{
    return MCI_MSF_MINUTE(dwMsf) * CDAUDIO_FRAMES_PER_MINUTE +
           MCI_MSF_SECOND(dwMsf) * CDAUDIO_FRAMES_PER_SECOND +
           MCI_MSF_FRAME(dwMsf);
}

__inline DWORD FramesToMsf(DWORD dwFrames)
{
    return MCI_MAKE_MSF(
        dwFrames / CDAUDIO_FRAMES_PER_MINUTE,
        (dwFrames % CDAUDIO_FRAMES_PER_MINUTE) / CDAUDIO_FRAMES_PER_SECOND,
        (dwFrames % CDAUDIO_FRAMES_PER_MINUTE) % CDAUDIO_FRAMES_PER_SECOND);
}

__inline DWORD TocValToMsf(LPBYTE ab)
{
    return MCI_MAKE_MSF(ab[1], ab[2], ab[3]);
}

__inline DWORD TocValToFrames(LPBYTE ab)
{
    return MsfToFrames(TocValToMsf(ab));
}

struct XCDROM_TOC
{
public:
	XCDROM_TOC();
	~XCDROM_TOC();

	void Delete();
	int GetTrackFromFrame(DWORD dwPosition) const;

    int LastTrack;
    DWORD TrackAddr [100];

#ifdef _CD_INFO
	void UpdateDiscID();

	TCHAR* rgszTrack [100];
	TCHAR* szTitle;
	TCHAR* szArtist;
	TCHAR* szID;
#endif

protected:
	void Clear();
};

typedef XCDROM_TOC* PXCDROM_TOC;

// FRAMES_PER_CHUNK should be kept small, to maximize granularity. We stop music on
// a chunk boundary.

// Some CD hardware (Thompson, .94 firmware revision) is happiest with 1 second reads.

#define FRAMES_PER_CHUNK (CDAUDIO_FRAMES_PER_SECOND)

#define CD_AUDIO_SEGMENTS_PER_BUFFER ((4*CDAUDIO_FRAMES_PER_SECOND)/FRAMES_PER_CHUNK)

#define BYTES_PER_CHUNK (FRAMES_PER_CHUNK * CDAUDIO_BYTES_PER_FRAME)
