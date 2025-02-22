
//
//  patchprv.h
//
//  Private interface options for creating patch files.
//
//  Author: Tom McGuire (tommcg) 2/98
//
//  Copyright (C) Microsoft, 1997-2000.
//
//  MICROSOFT CONFIDENTIAL
//

#ifndef _PATCHPRV_H_
#define _PATCHPRV_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PATCH_SIGNATURE     '91AP'          // PA19 patch signature

#define PATCH_VERSION_TEXT  "5.2.9347.0"

#define PATCH_RESOURCE_VER  5,2,9347,0      // major, minor, build#, qfe#

//
//  DONT FORGET TO CHANGE THE DLL VERSION NUMBER IN SRC_DLL.INC !!!!
//


typedef struct _RIFT_ENTRY {
    ULONG OldFileRva;
    ULONG NewFileRva;
    } RIFT_ENTRY, *PRIFT_ENTRY;

typedef struct _RIFT_TABLE {
    ULONG       RiftEntryCount;
    ULONG       RiftEntryAlloc;
    PRIFT_ENTRY RiftEntryArray;
    PUCHAR      RiftUsageArray;
    } RIFT_TABLE, *PRIFT_TABLE;

typedef struct _PATCH_HEADER_OLD_FILE_INFO {
    HANDLE              OldFileHandle;
    ULONG               OldFileSize;
    ULONG               OldFileCrc;
    ULONG               PatchDataSize;
    ULONG               IgnoreRangeCount;
    PPATCH_IGNORE_RANGE IgnoreRangeArray;
    ULONG               RetainRangeCount;
    PPATCH_RETAIN_RANGE RetainRangeArray;
    RIFT_TABLE          RiftTable;
    } HEADER_OLD_FILE_INFO, *PHEADER_OLD_FILE_INFO;

typedef struct _PATCH_HEADER_INFO {
    ULONG Signature;
    ULONG OptionFlags;
    ULONG ExtendedOptionFlags;
    ULONG NewFileCoffBase;
    ULONG NewFileCoffTime;
    ULONG NewFileResTime;
    ULONG NewFileTime;
    ULONG NewFileSize;
    ULONG NewFileCrc;
    ULONG OldFileCount;
    PHEADER_OLD_FILE_INFO OldFileInfoArray;
    PPATCH_INTERLEAVE_MAP* InterleaveMapArray;
    ULONG WindowSize;
    } PATCH_HEADER_INFO, *PPATCH_HEADER_INFO;


BOOL
ProgressCallbackWrapper(
    IN PPATCH_PROGRESS_CALLBACK ProgressCallback,
    IN PVOID                    CallbackContext,
    IN ULONG                    CurrentPosition,
    IN ULONG                    MaximumPosition
    );

BOOL
WINAPIV
NormalizeOldFileImageForPatching(
    IN PVOID FileMappedImage,
    IN ULONG FileSize,
    IN ULONG OptionFlags,
    IN PVOID OptionData,
    IN ULONG NewFileCoffBase,
    IN ULONG NewFileCoffTime,
    IN ULONG IgnoreRangeCount,
    IN PPATCH_IGNORE_RANGE IgnoreRangeArray,
    IN ULONG RetainRangeCount,
    IN PPATCH_RETAIN_RANGE RetainRangeArray,
    ...
    );

BOOL
WINAPIV
TransformOldFileImageForPatching(
    IN OUT PULONG TransformOptions,
    IN OUT PVOID  OldFileMapped,
    IN     ULONG  OldFileSize,
    IN     ULONG  NewFileResTime,
    IN     PRIFT_TABLE RiftTable,
    ...
    );

BOOL
DecodePatchHeader(
    IN  PVOID               PatchHeader,
    IN  ULONG               PatchHeaderMaxSize,
    IN  HANDLE              SubAllocator,
    OUT PULONG              PatchHeaderActualSize,
    OUT PPATCH_HEADER_INFO *HeaderInfo
    );

ULONG
EncodePatchHeader(
    IN  PPATCH_HEADER_INFO HeaderInfo,
    OUT PVOID              PatchHeaderBuffer
    );

//
//  The following is a private flag to indicate external rift data is being
//  specified in the OptionData->OldFileSymbolPathArray[ OldFileIndex ] field
//  (really a PRIFT_TABLE pointer).
//

#define PATCH_SYMBOL_EXTERNAL_RIFT      PATCH_SYMBOL_RESERVED1

//
//  The following is an internal flag stored in the patch header to indicate
//  the ExtendedOptionFlags field is present (non-zero) in the header.  It is
//  never necessary to specify this flag when creating a patch.
//

#define PATCH_OPTION_EXTENDED_OPTIONS   PATCH_OPTION_RESERVED1

//
//  Following are flags in the ExtendedOptionFlags field.
//

#define PATCH_TRANSFORM_NO_RELOCS       0x00000001  // don't xform relocs
#define PATCH_TRANSFORM_NO_IMPORTS      0x00000002  // don't xform imports
#define PATCH_TRANSFORM_NO_EXPORTS      0x00000004  // don't xform exports
#define PATCH_TRANSFORM_NO_RELJMPS      0x00000008  // don't xform E9 or 0F 8x instructions
#define PATCH_TRANSFORM_NO_RELCALLS     0x00000010  // don't xform E8 instructions
#define PATCH_TRANSFORM_NO_RESOURCE     0x00000020  // don't xform resources

#define PATCH_TRANSFORM_CREATION        0x10000000  // validate PE structures during patch creation
                                                    // (not encoded in patch header for decoder)

#define PATCH_TRANSFORM_ANY_PE          0x20000000  // during patch creation, any PE transforms done?

#define PATCH_OPTION_SPECIFIED_WINDOW   0x00010000  // lzx window size encoded

//
//  Following error indicates patch creator should try again with
//  PATCH_TRANSFORM_NO_RESOURCE enabled.
//

#define PATCH_ERROR_RETRY_NO_RESOURCE   ERROR_PATCH_CREATE_RESERVED_07


VOID
__fastcall
RiftQsort(
    PRIFT_ENTRY LowerBound,
    PRIFT_ENTRY UpperBound
    );


#ifdef __cplusplus
}
#endif

#endif // _PATCHPRV_H_

