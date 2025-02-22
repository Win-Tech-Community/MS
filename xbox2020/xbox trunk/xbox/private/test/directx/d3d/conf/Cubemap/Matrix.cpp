//////////////////////////////////////////////////////////////////////
// Matrix.cpp: implementation of the CMatrix class.
//////////////////////////////////////////////////////////////////////

#include "d3dlocus.h"
#include "cd3dtest.h"
#include "3dmath.h"
#include "Matrix.h"

CMatrix::CMatrix()
{
	Clear();
}

CMatrix::~CMatrix()
{
}

void CMatrix::Clear()
{
	ZeroMemory(&m_Matrix,sizeof(m_Matrix));
}

void CMatrix::Identity()
{
	Clear();
	m_Matrix._11=m_Matrix._22=m_Matrix._33=m_Matrix._44=1.0f;
}

void CMatrix::RotatePitch(float Deg)
{
	CMatrix RotateMatrix;

	RotateMatrix.Identity();
	RotateMatrix.m_Matrix._22=(float)cos((double)Deg*PI/180);
	RotateMatrix.m_Matrix._23=(float)sin((double)Deg*PI/180);
	RotateMatrix.m_Matrix._32=(float)-sin((double)Deg*PI/180);
	RotateMatrix.m_Matrix._33=(float)cos((double)Deg*PI/180);

	m_Matrix=(D3DMATRIX)((D3DXMATRIX)(RotateMatrix.m_Matrix)*(D3DXMATRIX)m_Matrix);
}

void CMatrix::RotateYaw(float Deg)
{
	CMatrix RotateMatrix;

	RotateMatrix.Identity();
	RotateMatrix.m_Matrix._11=(float)cos((double)Deg*PI/180);
	RotateMatrix.m_Matrix._13=(float)-sin((double)Deg*PI/180);
	RotateMatrix.m_Matrix._31=(float)sin((double)Deg*PI/180);
	RotateMatrix.m_Matrix._33=(float)cos((double)Deg*PI/180);

	m_Matrix=(D3DMATRIX)((D3DXMATRIX)(RotateMatrix.m_Matrix)*(D3DXMATRIX)m_Matrix);
}

void CMatrix::RotateRoll(float Deg)
{
	CMatrix RotateMatrix;

	RotateMatrix.Identity();
	RotateMatrix.m_Matrix._11=(float)cos((double)Deg*PI/180);
	RotateMatrix.m_Matrix._12=(float)sin((double)Deg*PI/180);
	RotateMatrix.m_Matrix._21=(float)-sin((double)Deg*PI/180);
	RotateMatrix.m_Matrix._22=(float)cos((double)Deg*PI/180);

	m_Matrix=(D3DMATRIX)((D3DXMATRIX)(RotateMatrix.m_Matrix)*(D3DXMATRIX)m_Matrix);
}

void CMatrix::Translate(D3DVECTOR Position)
{
	CMatrix TranslateMatrix;

	TranslateMatrix.Identity();
	TranslateMatrix.m_Matrix._41=Position.x;
	TranslateMatrix.m_Matrix._42=Position.y;
	TranslateMatrix.m_Matrix._43=Position.z;

	m_Matrix=(D3DMATRIX)((D3DXMATRIX)(TranslateMatrix.m_Matrix)*(D3DXMATRIX)m_Matrix);
}
