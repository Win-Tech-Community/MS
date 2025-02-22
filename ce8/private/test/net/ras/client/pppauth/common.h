//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft shared
// source or premium shared source license agreement under which you licensed
// this source code. If you did not accept the terms of the license agreement,
// you are not authorized to use this source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the SOURCE.RTF on your install media or the root of your tools installation.
// THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
#ifndef __COMMON_H_
#define __COMMON_H_

#include <windows.h>

#define RAS_STR_NULL TEXT("NULL")

BOOL
GetRemoteServerIpAddress(
    IN TCHAR    *ServerName, 
    IN BOOL     ipFamily,
    OUT TCHAR   *ServerIp
    );

#endif //__CONNECT_H_
