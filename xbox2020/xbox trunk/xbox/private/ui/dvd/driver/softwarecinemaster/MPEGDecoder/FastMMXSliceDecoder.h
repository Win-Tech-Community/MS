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

#ifndef FASTMMXSLICEDECODER_H
#define FASTMMXSLICEDECODER_H

#include "GenericMMXSliceDecoder.h"
#include "GenericMMXMotionComp.h"

class QFastMMXSliceDecoder : public GenericPackedIntraMMXSliceDecoder
	{
	protected:
		int									motionVectorMask;

		MMXShort16							mby[16];
		MMXShort16							mbuv[8];

		BPTR									fbp, ifbp;
		int									fbstride;
		bool									needsFrameData;

		GenericMMXMotionComp			 * motionComp;
		GenericMMXYUVVideoConverter *	yuvConverter;

		void ClearBlocks(void);
		void MotionCompensation(int mx, int my, bool copyY, bool copyUV);
		void ParseIntraMacroblock(int mx, int my);

		bool AttemptDirectAccess(void);
		void DoneDirectAccess(void);
	public:
		QFastMMXSliceDecoder(VideoBitStream * bitStream,
			                  GenericMMXMotionComp * motionComp = NULL,
									GenericMMXMacroBlockIDCTDecoder * idctDecoder = NULL,
									GenericMMXYUVVideoConverter	*	yuvConverter = NULL);
		~QFastMMXSliceDecoder(void);

		bool BeginFrameDecoding(FrameStore * pred, FrameStore * succ, FrameStore * curr, PictureDisplayBuffer * display, bool hurryUp);

		SPUDisplayBuffer * CreateSPUDisplayBuffer(void) {return new FullWidthMMXSPUDisplayBuffer();}
		FrameStore * AllocFrameStore(PictureCodingType type, bool stripeOptimized);
	};


#endif

