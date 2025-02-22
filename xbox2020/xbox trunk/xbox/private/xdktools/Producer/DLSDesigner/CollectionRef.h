///////////////////////////////////////////////////////////////////////////////////////////
//
//	CollectionRef.h
//	DLS Collection Reference node declaration
//	Created 3/17/98 Eric Whitcombe
//
///////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COLLECTION_REF__
#define __COLLECTION_REF__

#include "DLSDesignerDLL.h"
#include "DLSComponent.h"
#include "Collection.h"

class CCollectionRef : public IDMUSProdNode, public IDMUSProdReferenceNode,
					   public IDLSQueryInstruments
{
public:
	CCollectionRef(CDLSComponent* pComponent);
	~CCollectionRef();

    // IUnknown functions
    HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, LPVOID *ppv );
    ULONG STDMETHODCALLTYPE AddRef();
    ULONG STDMETHODCALLTYPE Release();

    // IDMUSProdNode functions
	HRESULT STDMETHODCALLTYPE GetNodeImageIndex( short* pnNbrFirstImage );
    HRESULT STDMETHODCALLTYPE GetFirstChild( IDMUSProdNode** ppIFirstChildNode );
    HRESULT STDMETHODCALLTYPE GetNextChild( IDMUSProdNode* pIChildNode, IDMUSProdNode** ppINextChildNode );

    HRESULT STDMETHODCALLTYPE GetComponent( IDMUSProdComponent** ppIComponent );
    HRESULT STDMETHODCALLTYPE GetDocRootNode( IDMUSProdNode** ppIDocRootNode );
    HRESULT STDMETHODCALLTYPE SetDocRootNode( IDMUSProdNode* pIDocRootNode );
    HRESULT STDMETHODCALLTYPE GetParentNode( IDMUSProdNode** ppIParentNode );
    HRESULT STDMETHODCALLTYPE SetParentNode( IDMUSProdNode* pIParentNode );
    HRESULT STDMETHODCALLTYPE GetNodeId( GUID* pguid );
    HRESULT STDMETHODCALLTYPE GetNodeName( BSTR* pbstrName );
    HRESULT STDMETHODCALLTYPE GetNodeNameMaxLength( short* pnMaxLength );
    HRESULT STDMETHODCALLTYPE ValidateNodeName( BSTR bstrName );
    HRESULT STDMETHODCALLTYPE SetNodeName( BSTR bstrName );
	HRESULT STDMETHODCALLTYPE GetNodeListInfo( DMUSProdListInfo* pListInfo );

    HRESULT STDMETHODCALLTYPE GetEditorClsId( CLSID* pclsid );
    HRESULT STDMETHODCALLTYPE GetEditorTitle( BSTR* pbstrTitle );
    HRESULT STDMETHODCALLTYPE GetEditorWindow( HWND* hWndEditor );
    HRESULT STDMETHODCALLTYPE SetEditorWindow( HWND hWndEditor );

	HRESULT STDMETHODCALLTYPE UseOpenCloseImages( BOOL* pfUseOpenCloseImages );

    HRESULT STDMETHODCALLTYPE GetRightClickMenuId( HINSTANCE* phInstance, UINT* pnResourceId );
    HRESULT STDMETHODCALLTYPE OnRightClickMenuInit( HMENU hMenu );
    HRESULT STDMETHODCALLTYPE OnRightClickMenuSelect( long lCommandId );

    HRESULT STDMETHODCALLTYPE DeleteChildNode( IDMUSProdNode* pIChildNode, BOOL fPromptUser );
    HRESULT STDMETHODCALLTYPE InsertChildNode( IDMUSProdNode* pIChildNode );
    HRESULT STDMETHODCALLTYPE DeleteNode( BOOL fPromptUser );

	HRESULT STDMETHODCALLTYPE OnNodeSelChanged( BOOL fSelected );

	HRESULT STDMETHODCALLTYPE CreateDataObject( IDataObject** ppIDataObject );
	HRESULT STDMETHODCALLTYPE CanCut();
	HRESULT STDMETHODCALLTYPE CanCopy();
	HRESULT STDMETHODCALLTYPE CanDelete();
	HRESULT STDMETHODCALLTYPE CanDeleteChildNode( IDMUSProdNode* pIChildNode );
	HRESULT STDMETHODCALLTYPE CanPasteFromData( IDataObject* pIDataObject, BOOL* pfWillSetReference );
	HRESULT STDMETHODCALLTYPE PasteFromData( IDataObject* pIDataObject );
	HRESULT STDMETHODCALLTYPE CanChildPasteFromData( IDataObject* pIDataObject, IDMUSProdNode* pIChildNode, BOOL* pfWillSetReference );
	HRESULT STDMETHODCALLTYPE ChildPasteFromData( IDataObject* pIDataObject, IDMUSProdNode* pIChildNode );

	HRESULT STDMETHODCALLTYPE GetObject( REFCLSID rclsid, REFIID riid, void** ppvObject ); 

    // IDMUSProdReferenceNode functions
	HRESULT STDMETHODCALLTYPE GetReferencedFile( IDMUSProdNode** ppIDocRootNode );
	HRESULT STDMETHODCALLTYPE SetReferencedFile( IDMUSProdNode* pIDocRootNode );

	// IDLSQueryInstruments functions
	HRESULT STDMETHODCALLTYPE ResetInstrumentList();
	

	BOOL	STDMETHODCALLTYPE GetNextInstrument(BYTE *pbMSB, 
												BYTE *pbLSB, 
												BYTE *pcPC, 
												BOOL *pfDrums, 
												signed char *pszName, 
												DWORD dwMaxLen);
	
	BOOL	STDMETHODCALLTYPE GetInstrumentName(BYTE bMSB, 
												BYTE bLSB, 
												BYTE cPC, 
												BOOL fDrums, 
												signed char *pszName, 
												DWORD dwMaxLen);

	HRESULT	STDMETHODCALLTYPE GetObjectDescriptor(DWORD dwDescSize,
												  void *pObjectDesc);

	HRESULT	STDMETHODCALLTYPE GetRegionWaveName(BYTE bMSB, 
												BYTE bLSB, 
												BYTE bPC, 
												BOOL fDrums, 
												BYTE bMIDINote, 
												BSTR* pbstrName);
public:
	CCollection*			m_pCollection;//the referenced collection

private:
	DWORD					m_dwInstrumentIndex;
    DWORD					m_dwRef;
	IDMUSProdNode*			m_pIDocRootNode;
	IDMUSProdNode*		    m_pIParentNode;
	CDLSComponent*			m_pComponent;
};

#endif // __COLLECTION_REF__