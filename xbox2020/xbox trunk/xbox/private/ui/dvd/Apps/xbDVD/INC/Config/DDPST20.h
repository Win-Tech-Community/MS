////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Copyright 2000 Ravisent Technologies, Inc.  All Rights Reserved.           //
// HIGHLY CONFIDENTIAL INFORMATION:  This source code contains                //
// confidential and proprietary information of Ravisent Technologies, Inc.    //
// This source code is provided to Microsoft Corporation under a written      //
// confidentiality agreement between Ravisent and Microsoft.  This            //
// software may not be reproduced, distributed, modified, disclosed, used,    //
// displayed, stored in a retrieval system or transmitted in whole or in part,//
// in any form or by any means, electronic, mechanical, photocopying or       //
// otherwise, except as expressly authorized by Ravisent.  THE ONLY PERSONS   //
// WHO MAY HAVE ACCESS TO THIS SOFTWARE ARE THOSE PERSONS                     //
// AUTHORIZED BY RAVISENT, WHO HAVE EXECUTED AND DELIVERED A                  //
// WRITTEN CONFIDENTIALITY AGREEMENT TO RAVISENT, IN THE FORM                 //
// PRESCRIBED BY RAVISENT.                                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
//
//  DDP Layer Include File For ST20LITE
//
////////////////////////////////////////////////////////////////////

#ifndef DDPST20_H
#define DDPST20_H

////////////////////////////////////////////////////////////////////
//
//  Includes
//
////////////////////////////////////////////////////////////////////

#include "driver/dvdpldrv/Common/dvdpld32.h"
#include "boards/generic/vdgendrv.h"

////////////////////////////////////////////////////////////////////
//
//  Function Declarations
//
////////////////////////////////////////////////////////////////////

Error DDP_Initialize(GenericProfile * profile);

#endif

