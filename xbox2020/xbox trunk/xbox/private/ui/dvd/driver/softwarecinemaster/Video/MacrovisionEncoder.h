////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Copyright 2000-2001 STMicroelectronics, Inc.  All Rights Reserved.         //
// HIGHLY CONFIDENTIAL INFORMATION:  This source code contains                //
// confidential and proprietary information of STMicroelectronics, Inc.       //
// This source code is provided to Microsoft Corporation under a written      //
// confidentiality agreement between STMicroelectronics and Microsoft.  This  //
// software may not be reproduced, distributed, modified, disclosed, used,    //
// displayed, stored in a retrieval system or transmitted in whole or in part,//
// in any form or by any means, electronic, mechanical, photocopying or       //
// otherwise, except as expressly authorized by STMicroelectronics. THE ONLY  //
// PERSONS WHO MAY HAVE ACCESS TO THIS SOFTWARE ARE THOSE PERSONS             //
// AUTHORIZED BY RAVISENT, WHO HAVE EXECUTED AND DELIVERED A                  //
// WRITTEN CONFIDENTIALITY AGREEMENT TO STMicroelectronics, IN THE FORM       //
// PRESCRIBED BY STMicroelectronics.                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef MACROVISIONENCODER_H
#define MACROVISIONENCODER_H

#include "driver\SoftwareCinemaster\Common\Prelude.h"
#undef INITGUIDS
#include "ctvout.h"
#include "tvcaps.h"
#include "tvmvis.h"
#include "tvstat.h"

class MacrovisionEncoder
	{
	public:
		virtual ~MacrovisionEncoder(void) {}
		virtual bool Initialize(void) = 0;
		virtual bool SetMacrovisionLevel(int level) = 0;
	};

class WindowsMacrovisionEncoder : public MacrovisionEncoder
	{
	protected:
		DWORD						macrovisionKey;
		int						prevMacrovisionLevel;
		bool						macrovisionEnabled;
		HINSTANCE user32Inst;
	public:
		WindowsMacrovisionEncoder(void);
		~WindowsMacrovisionEncoder(void);

		bool Initialize(void);
		bool SetMacrovisionLevel(int level);
	};

#endif

