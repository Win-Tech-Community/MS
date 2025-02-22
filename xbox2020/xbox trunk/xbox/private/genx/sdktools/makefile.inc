
!IFNDEF NO_STRICT
STRICT=1
!ENDIF

TARGETSRCS=$(SDK_INC_PATH)\imagehlp.h     \
           $(SDK_INC_PATH)\dbghelp.h

sdkinc: $(TARGETSRCS)

# imagehlp.h
$O\imagehlp.h: imagehlp.x makefile.inc
    type << > $@
/*++ BUILD Version: ????     Increment this if a change has global effects

$(COPYRIGHT_STRING)

Module Name:

    imagehlp.h

Abstract:

    This module defines the prototypes and constants required for the image
    help routines.

Revision History:

--*/

#ifndef _IMAGEHLP_
#define _IMAGEHLP_

#if _MSC_VER > 1020
#pragma once
#endif

<<
    hextract -o $@ -xt hide_line -lt show_imagehlp -bt begin_imagehlp end_imagehlp imagehlp.x
    type << >> $@

#endif // _IMAGEHLP_
<<

# dbghelp.h

$O\dbghelp.h: imagehlp.x makefile.inc
    type << > $@
/*++ BUILD Version: ????     Increment this if a change has global effects

$(COPYRIGHT_STRING)

Module Name:

    dbghelp.h

Abstract:

    This module defines the prototypes and constants required for the image
    help routines.

    Contains debugging support routines that are redistributable.

Revision History:

--*/

#ifndef _DBGHELP_
#define _DBGHELP_

#if _MSC_VER > 1020
#pragma once
#endif

<<
    hextract -o $@ -xt hide_line -lt show_dbghelp -bt begin_dbghelp end_dbghelp imagehlp.x
    type << >> $@

#endif // _DGGHELP_
<<

{$(O)}.h{$(SDK_INC_PATH)}.h:
    del /f /q $@
    copy $? $@
