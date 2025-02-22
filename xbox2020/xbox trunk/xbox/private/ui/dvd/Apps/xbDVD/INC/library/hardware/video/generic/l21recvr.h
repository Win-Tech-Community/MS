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

// FILE:			library\hardware\video\generic\l21recvr.h
// AUTHOR:		S. Herr
// COPYRIGHT:	(c) 2000 VIONA Development.  All Rights Reserved.
// CREATED:		02.03.2000
//
// PURPOSE:		Line 21 Data Stream Receiver Base Class
//
// HISTORY:

#ifndef L21RECVR_H
#define L21RECVR_H

#include "library/common/prelude.h"

#ifndef ONLY_EXTERNAL_VISIBLE

class Line21Receiver
	{
	public:
		virtual Error AddCloseCaptionData(BOOL startField, BYTE __far * data, int num) = 0;
		virtual Error FlushCloseCaptionBuffer(void) = 0;
		virtual Error StartCloseCaptionTransfer(void) = 0;
		virtual Error StopCloseCaptionTransfer(void) = 0;
	};

#endif

#endif
