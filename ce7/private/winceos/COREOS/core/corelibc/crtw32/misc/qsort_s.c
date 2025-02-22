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
/***
*qsort_s.c - implementation of the quicksort algorithm
*
*
*Purpose:
*   To implement the qsort_s() routine for sorting arrays.
*
*******************************************************************************/

/***
*qsort_s(base, num, wid, comp, context) - quicksort function for sorting arrays
*
*Purpose:
*   quicksort the array of elements
*   side effects:  sorts in place
*   maximum array size is number of elements times size of elements,
*   but is limited by the virtual address space of the processor
*
*Entry:
*   char *base = pointer to base of array
*   size_t num  = number of elements in the array
*   size_t width = width in bytes of each array element
*   int (*comp)() = pointer to function returning analog of strcmp for
*           strings, but supplied by user for comparing the array elements.
*           it accepts 2 pointers to elements, together with a pointer to a context.
*           Returns neg if 1<2, 0 if 1=2, pos if 1>2.
*   void *context - pointer to the context in which the function is
*           called. This context is passed to the comparison function.
*
*Exit:
*   returns void
*
*Exceptions:
*    Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

#ifdef __USE_CONTEXT
#error __USE_CONTEXT should be undefined
#endif

#define __USE_CONTEXT
#include "qsort.c"
