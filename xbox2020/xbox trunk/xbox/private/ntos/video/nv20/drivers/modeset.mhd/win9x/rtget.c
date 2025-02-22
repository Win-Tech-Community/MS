/*
    FILE:   rtget.c
    DATE:   4/8/99

    This file holds code to get the restrction and timing list.
    If there isn't one -- just return the blank list (not a NULL
    ptr.)
*/

#include "cmntypes.h"
#include "modeext.h"
#include "modeset.h"
#include "mywin.h"
#include "utils.h"
#include "restime.h"
#include "regfuncs.h"
#include "debug.h"

// Just in cae we can't GlobalAlloc a list, we have a single entry one
// we can use here.
RESTIME     sRTList;

/*
    GetMasterRTList

    This routine extracts the Restriction and Timing list for the
    device requested from the registry. nRTListLen is the length
    in RESTIME structures of the array pointed to by lpRTList.
*/
LPRESTIME CFUNC
GetMasterRTList (LPDISPDATA lpDispData)
{
    int         i;
    long        lRet;
    ULONG       dwSubKey;
    ULONG       dwSize, dwValueNameSize;
    ULONG       hRTKey;
    char        szItem[MAX_KEY_LEN];
    char        szRTString[MAX_KEY_LEN];
    LPRESTIME   lpRTList;

    DBG_PRINT0(DL_0, "\r\nEntering GetMasterRTList.");

    if  (!(lpRTList = (LPRESTIME) MemoryAlloc (MAX_RESTIMES * sizeof(RESTIME))))
    {
        DBG_PRINT0 (DL_0, "\r\nAllocation of Restriction And Timing List Failed.");
        DBG_PRINT0 (DL_0, "\r\nSetting up a default list with no restrictions.");
        lpRTList = &sRTList;

        // Use the dwXRes field in the first array element as a count
        // of the number of restriction list entries.
        lpRTList[0].dwXRes = 0;
        return  (lpRTList);
    }

    // Use the dwXRes field in the first array element as a count
    // of the number of restriction list entries.
    lpRTList[0].dwXRes = 0;

    // First, find the path to the restriction and timing strings.
    if  (!(hRTKey = GetLocalNvidiaDisplaySubKey (lpDispData->lpBoardRegistryData)))
    {
        DBG_PRINT0(DL_0, "\r\nGetLocalDisplaySubKey failed. Returning empty RTList.");  
        return  (lpRTList);
    }

    // Start enumerating and parsing the R&T strings.
    for (dwSubKey = 0; TRUE; dwSubKey++)
    {
        // Zero out the strings
        for (i = 0; i < MAX_KEY_LEN; i++)
        {
            szItem[i] = 0;
            szRTString[i] = 0;
        }

        dwValueNameSize = MAX_KEY_LEN;
        dwSize = MAX_KEY_LEN;
        lRet = RegEnumValue (hRTKey, dwSubKey, szItem,
                            &dwValueNameSize, NULL, NULL,
                            szRTString, &dwSize);

        // If there was an error, it probably means that there are
        // no more values to enumerate. That's fine. We are done.
        if  (lRet != ERROR_SUCCESS)
            break;

        // Is this subkey an R&T string? It is if it begins "R&T"
        if  ((szItem[0] == 'R') && (szItem[1] == '&') && (szItem[2] == 'T'))
        {
            // If the R&T string parses legitimately, include it in the list.
            if  (lpRTList[0].dwXRes < (MAX_RESTIMES - 1))
            {
                if  (ParseRTString (lpRTList + lpRTList[0].dwXRes + 1, szRTString))
                {
                    DBG_PRINT1(DL_0, "\r\nR&T string %s parsed fine.", szRTString);
                    lpRTList[0].dwXRes++;
                }
            }
        }
    }

    // Close the key
    RegCloseKey (hRTKey);

    return  (lpRTList);
}


/*
    FreeMasterRTList

    This routine is called when the caller is done with the RTList.
*/
int CFUNC
FreeMasterRTList (LPRESTIME lpRTList)
{
    // The dwYRes field in the first array element is used as a flag
    // to indicate that the array was GlobalAlloced.
    if  (lpRTList != &sRTList)
    {
        DBG_PRINT0(DL_0, "\r\nCalling MemoryFree on RTList.");
        MemoryFree ((LPULONG) lpRTList);
    }

    return  (TRUE);
}

