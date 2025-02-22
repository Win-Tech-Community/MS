//////////////////////////////////////////////////////////////////////////
//  D3D10Test.cpp
//  created:	2005/06/08
//
//  purpose: 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"

#include "D3D10Test.h"

CD3D10TestFramework::CD3D10TestFramework()
	: m_bSDKTest( false )
{
}

void CD3D10TestFramework::InitOptionVariables()
{
	CD3DTestFramework::InitOptionVariables();
	
	int id = AddOptionCategory( "D3D10" );
	RegisterOptionVariable( _T( "SDK" ), _T( "Run in SDK mode. Includes additional test conditions for SDK validation." ), &m_bSDKTest, false, OPTION_VALUE_CONSTANT, id );

	UnRegisterOptionVariable( "SrcOnly" );
	m_D3DOptions.SrcOnly = true;
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
