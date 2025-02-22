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
*tsplitpath_s.inl - general implementation of _tsplitpath_s
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file contains the general algorithm for _splitpath_s and its variants.
*
*Revision History:
*       06-24-04  AC    Created
*       07-16-04  AC    Fixed __cdecl
*       07-29-04  AC    Fixed mbs support and long path support
*       08-12-04  AC    Fixed small bug
*       09-24-04  MSL   Added return to silence flow analysis
*       10-30-04  AC    Just return ERANGE without calling _invalid_parameter
*                       if there is not enough space.
*                       VSW#363624
*       01-21-05  MSL   SAL Annotation
*       04-25-05  AC    Added debug filling
*                       VSW#2459
*       03-09-06  AC    Correctly handle long path name prefix
*                       VSW#580936
*
*******************************************************************************/
 
_FUNC_PROLOGUE
errno_t __cdecl _FUNC_NAME(
    _In_z_ const _CHAR *_Path,
    _Out_writes_opt_z_(_DriveSize) _CHAR *_Drive, _In_ size_t _DriveSize,
    _Out_writes_opt_z_(_DirSize) _CHAR *_Dir, _In_ size_t _DirSize,
    _Out_writes_opt_z_(_FilenameSize) _CHAR *_Filename, _In_ size_t _FilenameSize,
    _Out_writes_opt_z_(_ExtSize) _CHAR *_Ext, _In_ size_t _ExtSize
)
{
    const _CHAR *tmp;
    const _CHAR *last_slash;
    const _CHAR *dot;
    int drive_set = 0;
    size_t length = 0;
    int bEinval = 0;
 
    /* validation section */
    if (_Path == NULL)
    {
        goto error_einval;
    }
    if ((_Drive == NULL && _DriveSize != 0) || (_Drive != NULL && _DriveSize == 0))
    {
        goto error_einval;
    }
    if ((_Dir == NULL && _DirSize != 0) || (_Dir != NULL && _DirSize == 0))
    {
        goto error_einval;
    }
    if ((_Filename == NULL && _FilenameSize != 0) || (_Filename != NULL && _FilenameSize == 0))
    {
        goto error_einval;
    }
    if ((_Ext == NULL && _ExtSize != 0) || (_Ext != NULL && _ExtSize == 0))
    {
        goto error_einval;
    }
 
    /* extract drive letter and ':', if any */
    if (!drive_set)
    {
        size_t skip = _MAX_DRIVE - 2;
        tmp = _Path;
        while (skip > 0 && *tmp != 0)
        {
            skip--;
            tmp++;
        }
        if (*tmp == _T(':'))
        {
            if (_Drive != NULL)
            {
                if (_DriveSize < _MAX_DRIVE)
                {
                    goto error_erange;
                }
                _TCSNCPY_S(_Drive, _DriveSize, _Path, _MAX_DRIVE - 1);
            }
            _Path = tmp + 1;
        }
        else
        {
            if (_Drive != NULL)
            {
                _RESET_STRING(_Drive, _DriveSize);
            }
        }
    }
 
    /* extract path string, if any. _Path now points to the first character
     * of the path, if any, or the filename or extension, if no path was
     * specified.  Scan ahead for the last occurence, if any, of a '/' or
     * '\' path separator character.  If none is found, there is no path.
     * We will also note the last '.' character found, if any, to aid in
     * handling the extension.
     */
    last_slash = NULL;
    dot = NULL;
    tmp = _Path;
    for (; *tmp != 0; ++tmp)
    {
#if _MBS_SUPPORT
#pragma warning(push)
#pragma warning(disable:4127)
        if (_ISMBBLEAD(*tmp))
#pragma warning(pop)
        {
            tmp++;
        }
        else 
#endif
        {
            if (*tmp == _T('/') || *tmp == _T('\\'))
            {
                /* point to one beyond for later copy */
                last_slash = tmp + 1;
            }
            else if (*tmp == _T('.'))
            {
                dot = tmp;
            }
        }
    }
 
    if (last_slash != NULL) 
    {
        /* found a path - copy up through last_slash or max characters
         * allowed, whichever is smaller
         */
        if (_Dir != NULL) {
            length = (size_t)(last_slash - _Path);
            if (_DirSize <= length)
            {
                goto error_erange;
            }
            _TCSNCPY_S(_Dir, _DirSize, _Path, length);
        }
        _Path = last_slash;
    }
    else
    {
        /* there is no path */
        if (_Dir != NULL)
        {
            _RESET_STRING(_Dir, _DirSize);
        }
    }
 
    /* extract file name and extension, if any.  Path now points to the
     * first character of the file name, if any, or the extension if no
     * file name was given.  Dot points to the '.' beginning the extension,
     * if any.
     */
    if (dot != NULL && (dot >= _Path))
    {
        /* found the marker for an extension - copy the file name up to the '.' */
        if (_Filename)
        {
            length = (size_t)(dot - _Path);
            if (_FilenameSize <= length)
            {
                goto error_erange;
            }
            _TCSNCPY_S(_Filename, _FilenameSize, _Path, length);
        }

        /* now we can get the extension - remember that tmp still points
         * to the terminating NULL character of path.
         */
        if (_Ext)
        {
            length = (size_t)(tmp - dot);
            if (_ExtSize <= length)
            {
                goto error_erange;
            }
            _TCSNCPY_S(_Ext, _ExtSize, dot, length);
        }
    }
    else
    {
        /* found no extension, give empty extension and copy rest of
         * string into fname.
         */
        if (_Filename)
        {
            length = (size_t)(tmp - _Path);
            if (_FilenameSize <= length)
            {
                goto error_erange;
            }
            _TCSNCPY_S(_Filename, _FilenameSize, _Path, length);
        }
        if (_Ext)
        {
            _RESET_STRING(_Ext, _ExtSize);
        }
    }
 
    _RETURN_NO_ERROR;
 
error_einval:
    bEinval = 1;
 
error_erange:
    if (_Drive != NULL && _DriveSize > 0)
    {
        _RESET_STRING(_Drive, _DriveSize);
    }
    if (_Dir != NULL && _DirSize > 0)
    {
        _RESET_STRING(_Dir, _DirSize);
    }
    if (_Filename != NULL && _FilenameSize > 0)
    {
        _RESET_STRING(_Filename, _FilenameSize);
    }
    if (_Ext != NULL && _ExtSize > 0)
    {
        _RESET_STRING(_Ext, _ExtSize);
    }
 
    _VALIDATE_POINTER(_Path);
    if (bEinval)
    {
        _RETURN_EINVAL;
    }
    return (errno = ERANGE);
}
