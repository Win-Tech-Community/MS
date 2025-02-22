#ifndef __IMGWELL_H__
#define __IMGWELL_H__

// The CImageWell class provides a convenient way to handle "tiled"
// bitmaps.

class CImageWell
{
public:
	CImageWell();
	CImageWell(UINT nBitmapID, CSize imageSize);
	~CImageWell();
	void SetBitmap (CBitmap *pBitmap, CSize imageSize);
	
	BOOL Open();
	BOOL IsOpen() { return m_dc.m_hDC != NULL; }
	void Close();
	BOOL Load(UINT nBitmapID, CSize imageSize);
	void Unload();
	
	BOOL CalculateMask();
	
	BOOL DrawImage(CDC* pDestDC, CPoint destPoint, UINT nImage,
		DWORD rop = 0); // rop==0 means image is drawn through a mask

	BOOL DrawMask(CDC* pDestDC, CPoint destPoint, UINT nImage, DWORD rop = NOTSRCCOPY);
	
protected:
		
	CSize m_imageSize;
	
	// We use either this pointer or our member bitmap:
	CBitmap *m_pbitmap;

	UINT m_nBitmapID;
	CBitmap m_bitmap;
	
	CDC m_dc;
	CBitmap m_mask;
	CDC m_maskDC;
};

#endif // __IMGWELL_H__
