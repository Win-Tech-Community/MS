/**********************************************************************
 *<
	FILE: pthelp.cpp

	DESCRIPTION:  A point helper implementation

	CREATED BY: 

	HISTORY: created 14 July 1995

 *>	Copyright (c) 1995, All Rights Reserved.
 **********************************************************************/

#include "helpers.h"

//------------------------------------------------------

#define AXIS_LENGTH 20.0f

void AxisViewportRect(ViewExp *vpt, const Matrix3 &tm, float length, Rect *rect);
void DrawAxis(ViewExp *vpt, const Matrix3 &tm, float length, BOOL sel=FALSE, BOOL frozen=FALSE);
Box3 GetAxisBox(ViewExp *vpt, const Matrix3 &tm,float length,int resetTM);

class PointHelpObject: public HelperObject {
	public:			
		// Class vars
		static HWND hParams;
		static IObjParam *iObjParams;
		static int dlgShowAxis;
		static float dlgAxisLength;

		// Snap suspension flag (TRUE during creation only)
		BOOL suspendSnap;
					
		// Params
		BOOL showAxis;
		float axisLength;
 		int extDispFlags;

		//  inherited virtual methods for Reference-management
		RefResult NotifyRefChanged( Interval changeInt, RefTargetHandle hTarget, 
		   PartID& partID, RefMessage message );		
	
		PointHelpObject();
		~PointHelpObject();
		
		// From BaseObject
		int HitTest(TimeValue t, INode* inode, int type, int crossing, int flags, IPoint2 *p, ViewExp *vpt);
		void Snap(TimeValue t, INode* inode, SnapInfo *snap, IPoint2 *p, ViewExp *vpt);
		void SetExtendedDisplay(int flags);
		int Display(TimeValue t, INode* inode, ViewExp *vpt, int flags);
		CreateMouseCallBack* GetCreateMouseCallBack();
		void BeginEditParams( IObjParam *ip, ULONG flags,Animatable *prev);
		void EndEditParams( IObjParam *ip, ULONG flags,Animatable *next);

		// From Object
		ObjectState Eval(TimeValue time);
		void InitNodeName(TSTR& s) { s = GetString(IDS_DB_POINT); }
		ObjectHandle ApplyTransform(Matrix3& matrix) {return this;}
		Interval ObjectValidity(TimeValue t) {return FOREVER;}
		int CanConvertToType(Class_ID obtype) {return FALSE;}
		Object* ConvertToType(TimeValue t, Class_ID obtype) {assert(0);return NULL;}		
		void GetWorldBoundBox(TimeValue t, INode *mat, ViewExp *vpt, Box3& box );
		void GetLocalBoundBox(TimeValue t, INode *mat, ViewExp *vpt, Box3& box );
		int DoOwnSelectHilite()	{ return 1; }

		// Animatable methods
		void DeleteThis() { delete this; }
		Class_ID ClassID() { return Class_ID(POINTHELP_CLASS_ID,0); }  
		void GetClassName(TSTR& s) { s = TSTR(GetString(IDS_DB_POINTHELPER_CLASS)); }
		int IsKeyable(){ return 0;}
		
		// From ref
		RefTargetHandle Clone(RemapDir& remap = NoRemap());
		IOResult Load(ILoad *iload);
		IOResult Save(ISave *isave);
	};				


// class variable for point class.
HWND PointHelpObject::hParams = NULL;
IObjParam *PointHelpObject::iObjParams;

int PointHelpObject::dlgShowAxis = TRUE;
float PointHelpObject::dlgAxisLength = AXIS_LENGTH;

void resetPointParams() 
{
	PointHelpObject::dlgShowAxis = TRUE;
	PointHelpObject::dlgAxisLength = AXIS_LENGTH;
}


class PointHelpObjClassDesc:public ClassDesc {
	public:
	int 			IsPublic() { return 1; }
	void *			Create(BOOL loading = FALSE) { return new PointHelpObject; }
	const TCHAR *	ClassName() { return GetString(IDS_DB_POINT_CLASS); }
	SClass_ID		SuperClassID() { return HELPER_CLASS_ID; }
	Class_ID		ClassID() { return Class_ID(POINTHELP_CLASS_ID,0); }
	const TCHAR* 	Category() { return _T("");  }
	void			ResetClassParams(BOOL fileReset) { if(fileReset) resetPointParams(); }
	};

static PointHelpObjClassDesc pointHelpObjDesc;

ClassDesc* GetPointHelpDesc() { return &pointHelpObjDesc; }

// in prim.cpp  - The dll instance handle
extern HINSTANCE hInstance;


BOOL CALLBACK PointParamProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
	{
	PointHelpObject *po = (PointHelpObject*)GetWindowLong(hWnd,GWL_USERDATA);
	if (!po && msg!=WM_INITDIALOG) return FALSE;

	switch (msg) {
		case WM_INITDIALOG: {
			po = (PointHelpObject*)lParam;
			SetWindowLong(hWnd,GWL_USERDATA,lParam);
			CheckDlgButton(hWnd,IDC_SHOWAXIS,po->showAxis);
			
			ISpinnerControl *spin = 
				GetISpinner(GetDlgItem(hWnd,IDC_AXISLENGHSPIN));
			spin->SetLimits(10,1000,FALSE);
			spin->SetScale(0.1f);
			spin->SetValue(po->axisLength,FALSE);
			spin->LinkToEdit(GetDlgItem(hWnd,IDC_AXISLENGTH),EDITTYPE_FLOAT);
			ReleaseISpinner(spin);
			return FALSE;
			}

		case CC_SPINNER_CHANGE: {
			ISpinnerControl *spin = (ISpinnerControl*)lParam;
			po->axisLength = spin->GetFVal();
			po->NotifyDependents(FOREVER,PART_OBJ,REFMSG_CHANGE);
			po->iObjParams->RedrawViews(po->iObjParams->GetTime());
			break;
			}

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDC_SHOWAXIS:
					po->showAxis = IsDlgButtonChecked(hWnd,IDC_SHOWAXIS);
					po->NotifyDependents(FOREVER,PART_OBJ,REFMSG_CHANGE);
					po->iObjParams->RedrawViews(po->iObjParams->GetTime());
					break;
				}
			break;
		
		default:
			return FALSE;
		}
	
	return TRUE;
	} 

void PointHelpObject::BeginEditParams(
		IObjParam *ip, ULONG flags,Animatable *prev)
	{	
	iObjParams = ip;
	if (!hParams) {
		hParams = ip->AddRollupPage( 
				hInstance, 
				MAKEINTRESOURCE(IDD_POINTPARAM),
				PointParamProc, 
				GetString(IDS_DB_PARAMETERS), 
				(LPARAM)this );
		ip->RegisterDlgWnd(hParams);
	} else {
		SetWindowLong(hParams,GWL_USERDATA,(LONG)this);
		CheckDlgButton(hParams,IDC_SHOWAXIS,showAxis);
		ISpinnerControl *spin = 
			GetISpinner(GetDlgItem(hParams,IDC_AXISLENGHSPIN));
		spin->SetValue(axisLength,FALSE);
		ReleaseISpinner(spin);
		}
	}
		
void PointHelpObject::EndEditParams(
		IObjParam *ip, ULONG flags,Animatable *next)
	{	
	dlgShowAxis = IsDlgButtonChecked(hParams, IDC_SHOWAXIS );
	ISpinnerControl *spin = GetISpinner(GetDlgItem(hParams,IDC_AXISLENGHSPIN));
	dlgAxisLength = spin->GetFVal();
	ReleaseISpinner(spin);
	if (flags&END_EDIT_REMOVEUI) {
		ip->UnRegisterDlgWnd(hParams);
		ip->DeleteRollupPage(hParams);
		hParams = NULL;
	} else {
		SetWindowLong(hParams,GWL_USERDATA,0);
		}
	iObjParams = NULL;
	}


PointHelpObject::PointHelpObject()
	{	
	showAxis = dlgShowAxis;
	axisLength = dlgAxisLength;
	suspendSnap = FALSE;
	}

PointHelpObject::~PointHelpObject()
	{	
	}

class PointHelpObjCreateCallBack: public CreateMouseCallBack {
	PointHelpObject *ob;
	public:
		int proc( ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat );
		void SetObj(PointHelpObject *obj) { ob = obj; }
	};

int PointHelpObjCreateCallBack::proc(ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat ) {	

	#ifdef _OSNAP
	if (msg == MOUSE_FREEMOVE)
	{
		#ifdef _3D_CREATE
			vpt->SnapPreview(m,m,NULL, SNAP_IN_3D);
		#else
			vpt->SnapPreview(m,m,NULL, SNAP_IN_PLANE);
		#endif
	}
	#endif

	if (msg==MOUSE_POINT||msg==MOUSE_MOVE) {
		switch(point) {
			case 0:
				ob->suspendSnap = TRUE;
				#ifdef _3D_CREATE	
					mat.SetTrans(vpt->SnapPoint(m,m,NULL,SNAP_IN_3D));
				#else	
					mat.SetTrans(vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE));
				#endif
				break;
			case 1:
				#ifdef _3D_CREATE	
					mat.SetTrans(vpt->SnapPoint(m,m,NULL,SNAP_IN_3D));
				#else	
					mat.SetTrans(vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE));
				#endif
				if (msg==MOUSE_POINT) {
					ob->suspendSnap = FALSE;
					return 0;
					}
				break;			
			}
	} else 
	if (msg == MOUSE_ABORT) {		
		return CREATE_ABORT;
		}
	return 1;
	}

static PointHelpObjCreateCallBack pointHelpCreateCB;

CreateMouseCallBack* PointHelpObject::GetCreateMouseCallBack() {
	pointHelpCreateCB.SetObj(this);
	return(&pointHelpCreateCB);
	}

void PointHelpObject::SetExtendedDisplay(int flags)
	{
	extDispFlags = flags;
	}

void PointHelpObject::GetLocalBoundBox(
		TimeValue t, INode* inode, ViewExp* vpt, Box3& box ) 
	{
	Matrix3 tm(1);
	tm.SetTrans(inode->GetObjectTM(t).GetTrans());
	if(showAxis)
		box = GetAxisBox(vpt,tm,showAxis?axisLength:0.0f, TRUE);
	else
		box = Box3(Point3(0,0,0), Point3(0,0,0));
	}

void PointHelpObject::GetWorldBoundBox(
		TimeValue t, INode* inode, ViewExp* vpt, Box3& box )
	{
	Matrix3 tm;
	tm = inode->GetObjectTM(t);
	if(!(extDispFlags & EXT_DISP_ZOOM_EXT) && showAxis)
		box = GetAxisBox(vpt,tm,showAxis?axisLength:0.0f, FALSE);
	else
		box = Box3(tm.GetTrans(), tm.GetTrans());
	}


// From BaseObject
int PointHelpObject::HitTest(TimeValue t, INode *inode, int type, int crossing, int flags, IPoint2 *p, ViewExp *vpt) {
	Matrix3 tm(1);	
	HitRegion hitRegion;
	DWORD	savedLimits;
	Point3 pt(0,0,0);

	vpt->getGW()->setTransform(tm);
	GraphicsWindow *gw = vpt->getGW();	
	Material *mtl = gw->getMaterial();

   	tm = inode->GetObjectTM(t);		
	MakeHitRegion(hitRegion, type, crossing, 4, p);

	gw->setRndLimits(((savedLimits = gw->getRndLimits())|GW_PICK)&~GW_ILLUM);
	gw->setHitRegion(&hitRegion);
	gw->clearHitCode();

	if (showAxis) {
		DrawAxis(vpt,tm,axisLength);
		}
	vpt->getGW()->setTransform(tm);
	vpt->getGW()->marker(&pt,X_MRKR);

	gw->setRndLimits(savedLimits);
	
	if((hitRegion.type != POINT_RGN) && !hitRegion.crossing)
		return TRUE;
	return gw->checkHitCode();
	}

void PointHelpObject::Snap(TimeValue t, INode* inode, SnapInfo *snap, IPoint2 *p, ViewExp *vpt)
	{
	if(suspendSnap)
		return;

	Matrix3 tm = inode->GetObjectTM(t);	
	GraphicsWindow *gw = vpt->getGW();	
	gw->setTransform(tm);

	Matrix3 invPlane = Inverse(snap->plane);

	// Make sure the vertex priority is active and at least as important as the best snap so far
	if(snap->vertPriority > 0 && snap->vertPriority <= snap->priority) {
		Point2 fp = Point2((float)p->x, (float)p->y);
		Point2 screen2;
		IPoint3 pt3;

		Point3 thePoint(0,0,0);
		// If constrained to the plane, make sure this point is in it!
		if(snap->snapType == SNAP_2D || snap->flags & SNAP_IN_PLANE) {
			Point3 test = thePoint * tm * invPlane;
			if(fabs(test.z) > 0.0001)	// Is it in the plane (within reason)?
				return;
			}
		gw->wTransPoint(&thePoint,&pt3);
		screen2.x = (float)pt3.x;
		screen2.y = (float)pt3.y;

		// Are we within the snap radius?
		int len = (int)Length(screen2 - fp);
		if(len <= snap->strength) {
			// Is this priority better than the best so far?
			if(snap->vertPriority < snap->priority) {
				snap->priority = snap->vertPriority;
				snap->bestWorld = thePoint * tm;
				snap->bestScreen = screen2;
				snap->bestDist = len;
				}
			else
			if(len < snap->bestDist) {
				snap->priority = snap->vertPriority;
				snap->bestWorld = thePoint * tm;
				snap->bestScreen = screen2;
				snap->bestDist = len;
				}
			}
		}
	}


int PointHelpObject::Display(TimeValue t, INode* inode, ViewExp *vpt, int flags) {
	Matrix3 tm(1);
	Point3 pt(0,0,0);
	vpt->getGW()->setTransform(tm);
	tm = inode->GetObjectTM(t);		
	if (showAxis) {
		DrawAxis(vpt,tm,axisLength,inode->Selected(),inode->IsFrozen());
		}
	vpt->getGW()->setTransform(tm);
	if(!inode->IsFrozen())
		vpt->getGW()->setColor(LINE_COLOR,GetUIColor(COLOR_POINT_OBJ));
	vpt->getGW()->marker(&pt,X_MRKR);
	return(0);
	}



//
// Reference Managment:
//

// This is only called if the object MAKES references to other things.
RefResult PointHelpObject::NotifyRefChanged(Interval changeInt, RefTargetHandle hTarget, 
     PartID& partID, RefMessage message ) 
    {
	return(REF_SUCCEED);
	}

ObjectState PointHelpObject::Eval(TimeValue time){
	return ObjectState(this);
	}

RefTargetHandle PointHelpObject::Clone(RemapDir& remap) {
	PointHelpObject* newob = new PointHelpObject();	
	newob->showAxis = showAxis;
	newob->axisLength = axisLength;
	return(newob);
	}


#define SHOW_AXIS_CHUNK		0x0100
#define AXIS_LENGTH_CHUNK	0x0110

IOResult PointHelpObject::Load(ILoad *iload)
	{
	ULONG nb;
	IOResult res = IO_OK;

	while (IO_OK==(res=iload->OpenChunk())) {
		switch (iload->CurChunkID()) {
			case SHOW_AXIS_CHUNK:
				res = iload->Read(&showAxis,sizeof(showAxis),&nb);
				break;
			case AXIS_LENGTH_CHUNK:
				res = iload->Read(&axisLength,sizeof(axisLength),&nb);
				break;
			}

		res = iload->CloseChunk();
		if (res!=IO_OK)  return res;
		}
	
	return IO_OK;
	}

IOResult PointHelpObject::Save(ISave *isave)
	{
	ULONG nb;

	isave->BeginChunk(SHOW_AXIS_CHUNK);
	isave->Write(&showAxis,sizeof(showAxis),&nb);
	isave->EndChunk();

	isave->BeginChunk(AXIS_LENGTH_CHUNK);
	isave->Write(&axisLength,sizeof(axisLength),&nb);
	isave->EndChunk();
	
	return IO_OK;
	}


/*--------------------------------------------------------------------*/
// 
// Stole this from scene.cpp
// Probably couldn't hurt to make an API...
//
//


void Text( ViewExp *vpt, TCHAR *str, Point3 &pt )
	{	
	vpt->getGW()->text( &pt, str );	
	}

static void DrawAnAxis( ViewExp *vpt, Point3 axis )
	{
	Point3 v1, v2, v[3];	
	v1 = axis * (float)0.9;
	if ( axis.x != 0.0 || axis.y != 0.0 ) {
		v2 = Point3( axis.y, -axis.x, axis.z ) * (float)0.1;
	} else {
		v2 = Point3( axis.x, axis.z, -axis.y ) * (float)0.1;
		}
	
	v[0] = Point3(0.0,0.0,0.0);
	v[1] = axis;
	vpt->getGW()->polyline( 2, v, NULL, NULL, FALSE, NULL );	
	v[0] = axis;
	v[1] = v1+v2;
	vpt->getGW()->polyline( 2, v, NULL, NULL, FALSE, NULL );
	v[0] = axis;
	v[1] = v1-v2;
	vpt->getGW()->polyline( 2, v, NULL, NULL, FALSE, NULL );
	}

#define ZFACT (float).005;

void DrawAxis( ViewExp *vpt, const Matrix3 &tm, float length, BOOL sel, BOOL frozen )
	{
	Matrix3 tmn = tm;
	float zoom;
	int limits;	

	// Get width of viewport in world units:  --DS
	zoom = vpt->GetScreenScaleFactor(tmn.GetTrans())*ZFACT;
	
	tmn.Scale( Point3(zoom,zoom,zoom) );
	vpt->getGW()->setTransform( tmn );	

	limits = vpt->getGW()->getRndLimits();
	vpt->getGW()->setRndLimits( limits & ~GW_Z_BUFFER );

	if (sel) {
		vpt->getGW()->setColor( TEXT_COLOR, GetUIColor(COLOR_SELECTION) );
		vpt->getGW()->setColor( LINE_COLOR, GetUIColor(COLOR_SELECTION) );
	} else if (!frozen) {
		vpt->getGW()->setColor( TEXT_COLOR, GetUIColor(COLOR_POINT_AXES) );
		vpt->getGW()->setColor( LINE_COLOR, GetUIColor(COLOR_POINT_AXES) );
		}
	
	Text( vpt, _T("x"), Point3(length,0.0f,0.0f) ); 
	DrawAnAxis( vpt, Point3(length,0.0f,0.0f) );	
	
	Text( vpt, _T("y"), Point3(0.0f,length,0.0f) ); 
	DrawAnAxis( vpt, Point3(0.0f,length,0.0f) );	
	
	Text( vpt, _T("z"), Point3(0.0f,0.0f,length) ); 
	DrawAnAxis( vpt, Point3(0.0f,0.0f,length) );	
	
	vpt->getGW()->setRndLimits( limits );
	}

Box3 GetAxisBox(ViewExp *vpt, const Matrix3 &tm,float length,int resetTM)
	{
	Matrix3 tmn = tm;
	Box3 box;
	float zoom;

	// Get width of viewport in world units:  --DS
	zoom = vpt->GetScreenScaleFactor(tmn.GetTrans())*ZFACT;
	if (zoom==0.0f) zoom = 1.0f;
//	tmn.Scale(Point3(zoom,zoom,zoom));
	length *= zoom;
	if(resetTM)
		tmn.IdentityMatrix();

	box += Point3(0.0f,0.0f,0.0f) * tmn;
	box += Point3(length,0.0f,0.0f) * tmn;
	box += Point3(0.0f,length,0.0f) * tmn;
	box += Point3(0.0f,0.0f,length) * tmn;	
	box += Point3(-length/5.f,0.0f,0.0f) * tmn;
	box += Point3(0.0f,-length/5.f,0.0f) * tmn;
	box += Point3(0.0f,0.0f,-length/5.0f) * tmn;
	box.EnlargeBy(10.0f/zoom);
	return box;
	}


inline void EnlargeRectIPoint3( RECT *rect, IPoint3& pt )
	{
	if ( pt.x < rect->left )   rect->left   = pt.x;
	if ( pt.x > rect->right )  rect->right  = pt.x;
	if ( pt.y < rect->top )    rect->top    = pt.y;
	if ( pt.y > rect->bottom ) rect->bottom = pt.y;
	}

// This is a guess - need to find real w/h.
#define FONT_HEIGHT	11
#define FONT_WIDTH  9	


static void AxisRect( GraphicsWindow *gw, Point3 axis, Rect *rect )
	{
	Point3 v1, v2, v;	
	IPoint3 iv;
	v1 = axis * (float)0.9;
	if ( axis.x != 0.0 || axis.y != 0.0 ) {
		v2 = Point3( axis.y, -axis.x, axis.z ) * (float)0.1;
	} else {
		v2 = Point3( axis.x, axis.z, -axis.y ) * (float)0.1;
		}
	v = axis;
	gw->wTransPoint( &v, &iv );
	EnlargeRectIPoint3( rect, iv);

	iv.x += FONT_WIDTH;
	iv.y -= FONT_HEIGHT;
	EnlargeRectIPoint3( rect, iv);

	v = v1+v2;
	gw->wTransPoint( &v, &iv );
	EnlargeRectIPoint3( rect, iv);
	v = v1-v2;
	gw->wTransPoint( &v, &iv );
	EnlargeRectIPoint3( rect, iv);
	}


void AxisViewportRect(ViewExp *vpt, const Matrix3 &tm, float length, Rect *rect)
	{
	Matrix3 tmn = tm;
	float zoom;
	IPoint3 wpt;
	Point3 pt;
	GraphicsWindow *gw = vpt->getGW();

	// Get width of viewport in world units:  --DS
	zoom = vpt->GetScreenScaleFactor(tmn.GetTrans())*ZFACT;
	
	tmn.Scale( Point3(zoom,zoom,zoom) );
	gw->setTransform( tmn );	
	pt = Point3(0.0f, 0.0f, 0.0f);
	gw->wTransPoint( &pt, &wpt );
	rect->left = rect->right  = wpt.x;
	rect->top  = rect->bottom = wpt.y;

	AxisRect( gw, Point3(length,0.0f,0.0f),rect );	
	AxisRect( gw, Point3(0.0f,length,0.0f),rect );	
	AxisRect( gw, Point3(0.0f,0.0f,length),rect );	

	rect->right  += 2;
	rect->bottom += 2;
	rect->left   -= 2;
	rect->top    -= 2;
	}



