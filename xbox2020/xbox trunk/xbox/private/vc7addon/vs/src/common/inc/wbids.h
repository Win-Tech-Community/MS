#ifndef _WBIDS_H_
#define _WBIDS_H_

#include "MsHtmCID.h"

//////////////////////////////////////////////////////////////////////////////
//
// GUID Identifiers, created by WebBrowse package
//
//////////////////////////////////////////////////////////////////////////////
#ifndef NOGUIDS

#ifdef DEFINE_GUID
  // WB package object CLSID
  DEFINE_GUID (guidWBPkg,
    0xe8b06f41, 0x6d01, 0x11d2, 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43);

  DEFINE_GUID (guidWBPkgCmd,
    0xe8b06f44, 0x6d01, 0x11d2, 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43);

  DEFINE_GUID (guidWBGrp,
    0xe8b06f42, 0x6d01, 0x11d2, 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43);

  DEFINE_GUID (guidFavGrp,
    0xe8b06f49, 0x6d01, 0x11d2, 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43);

  DEFINE_GUID (guidFavCmd,
    0xe8b06f4a, 0x6d01, 0x11d2, 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43);

  DEFINE_GUID(guidDynHelp, 
    0x2d2e0d17, 0xc8d0, 0x4744, 0x81, 0x6, 0xed, 0xca, 0x7f, 0x21, 0xc1, 0xac);

#else

#define guidWBPkg	      { 0xe8b06f41, 0x6d01, 0x11d2, { 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43 } }
#define guidWBPkgCmd    { 0xe8b06f44, 0x6d01, 0x11d2, { 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43 } }
#define guidWBGrp 	    { 0xe8b06f42, 0x6d01, 0x11d2, { 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43 } }
#define guidFavGrp 	    { 0xe8b06f49, 0x6d01, 0x11d2, { 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43 } }
#define guidFavCmd 	    { 0xe8b06f4a, 0x6d01, 0x11d2, { 0xaa, 0x7d, 0x00, 0xc0, 0x4f, 0x99, 0x03, 0x43 } }
#define guidDynHelp	    { 0x2d2e0d17, 0xc8d0, 0x4744, { 0x81, 0x6, 0xed, 0xca, 0x7f, 0x21, 0xc1, 0xac } }

#endif //DEFINE_GUID

#endif //NOGUIDS

///////////////////////////////////////////////////////////////////////////////
// Menus

#define IDM_WBTLB_WEB             1
#define IDM_WBMNU_COMMAND_WELL    2
#define IDM_WBMNU_FONTSIZE        3
#define IDM_WB_OPENIE_CASCADE     4

#define IDM_WBCTX_DEFAULT         10
#define IDM_WBCTX_IMAGE           11
#define IDM_WBCTX_SELECTION       12
#define IDM_WBCTX_ANCHOR          13
//#define IDM_FAVCTX                20
#define IDM_VS_TOOL_FAVORITES     21

#define IDM_WB_ENCODING           25
#define IDM_WB_ENCODING_MORE      26
#define IDM_VS_DYNHELP		  27

#define IDM_WB_HELP_NAV           28

///////////////////////////////////////////////////////////////////////////////
// Menu Groups

#define IDG_WB_MAIN            100
#define IDG_WB_FAVORITES       101
#define IDG_WB_URL             102
#define IDG_WB_HELP            103
#define IDG_WB_OTHER           104
#define IDG_WB_NEW_WINDOW      105
#define IDG_WB_SHOW            106

#define IDG_WB_FONTSIZE           107
#define IDG_WB_MNUCMDS            108
#define IDG_WB_FONTSIZELIST       109
#define IDG_WB_OPENIE_CASCADE     110
#define IDG_WB_CMDWELL            111
#define IDG_WB_CMDWELL_MAINMENU   112

#define IDG_WB_BACK_FORWARD       113
#define IDG_WB_HOME_SEARCH        114

#define IDG_WB_CTX_DEF_0          119
#define IDG_WB_CTX_DEF_1          120
#define IDG_WB_CTX_DEF_2          121
#define IDG_WB_CTX_DEF_3          122
#define IDG_WB_CTX_DEF_4          123
#define IDG_WB_CTX_PROPS          124
#define IDG_WB_CTX_ANCHOR         125
#define IDG_WB_CTX_IMG_1          126
#define IDG_WB_CTX_IMG_2          127
#define IDG_WB_CTX_SEL_1          128
#define IDG_WB_CTX_ANC_1          129

// for MSDN
//#define IDG_WB_FAVWND             130

#define IDG_WB_HELP_TOC_NAV       131

#define IDG_FAV_ADDORG            144
#define IDG_VS_DYNHELP		  145
#define IDG_VS_DYNHELP_TB         146

#define IDG_WB_ENCODING           150
#define IDG_WB_ENCODING_AUTO      151
#define IDG_WB_ENCODING_MRU       152

#define IDG_WB_CP_ARABIC          155
#define IDG_WB_CP_BALTIC          156
#define IDG_WB_CP_CENTRAL_EURO    157
#define IDG_WB_CP_CHINESE_SIMPL   158
#define IDG_WB_CP_CHINESE_TRAD    159
#define IDG_WB_CP_CYRILLIC        160
#define IDG_WB_CP_GREEK           161
#define IDG_WB_CP_HEBREW          162
#define IDG_WB_CP_JAPANESE        163
#define IDG_WB_CP_KOREAN          164
#define IDG_WB_CP_THAI            165
#define IDG_WB_CP_TURKISH         166
#define IDG_WB_CP_UKRAINIAN       167
#define IDG_WB_CP_UNICODE         168
#define IDG_WB_CP_USERDEFINED     169
#define IDG_WB_CP_VIETNAMESE      170
#define IDG_WB_CP_WESTERN_EURO    171


///////////////////////////////////////////////////////////////////////////////
// Command IDs

#define icmdBack                  201 
#define icmdForward               202
#define icmdStop                  203
#define icmdRefresh               204
#define icmdHome                  205
#define icmdSearch                206
#define icmdURL                   207
#define icmdURLHandler            208
#define icmdFavWindow             210
#define icmdDocFavAdd             211
#define icmdAnchorFavAdd          212
#define icmdImgFavAdd             213
#define icmdFntSzSmallest         214
#define icmdFntSzSmaller          215
#define icmdFntSzMedium           216
#define icmdFntSzLarger           217
#define icmdFntSzLargest          218
#define icmdFontSize              219

#define icmdFavOpen               300
#define icmdFavRename             301
#define icmdOpenLinkNew           303

#define icmdFavAdd		  310
#define icmdFavOrganize		  311

#define icmdContextWindow         400

// help commands 

#define icmdSync                  401
#define icmdNext                  402
#define icmdPrev                  403

#define icmdIEFind                405

// Encoding commands

#define icmdCpFirst               410
#define icmdCpArabicASMO          410
#define icmdCpArabicDOS           411
#define icmdCpArabicISO           412
#define icmdCpArabicWIN           413
#define icmdCpBalticISO           414
#define icmdCpBalticWIN           415
#define icmdCpCentralEuroDOS      416
#define icmdCpCentralEuroISO      417
#define icmdCpCentralEuroWIN      418
#define icmdCpChineseSimplified   419
#define icmdCpChineseTraditional  420
#define icmdCpCyrillicDOS         421
#define icmdCpCyrillicISO         422
#define icmdCpCyrillicKOI8R       423
#define icmdCpCyrillicWIN         424
#define icmdCpGreekISO            425
#define icmdCpGreekWIN            426
#define icmdCpHebrewDOS           427
#define icmdCpHebrewISO           428
#define icmdCpHebrewWIN           429
#define icmdCpJapaneseAUTO        430
#define icmdCpJapaneseEUC         431
#define icmdCpJapaneseSHIFT_JIS   432
#define icmdCpKoreanAUTO          433
//#define icmdCpKorean              434
//#define icmdCpKoreanISO           435
#define icmdCpThaiWIN             436
#define icmdCpTurkishWIN          437
#define icmdCpTurkishISO          438
#define icmdCpUkrainian           439
//#define icmdCpUnicodeUTF7         440
#define icmdCpUnicodeUTF8         441
#define icmdCpVietnamese          442
#define icmdCpWesternEuroWIN      443
#define icmdCpWesternEuroISO      444
#define icmdCpUserDefined         445
#define icmdCpLast                445

#define icmdCpMRU1                460
#define icmdCpMRU2                461
#define icmdCpMRU3                462
#define icmdCpMRU4                463



// Directly mapped Trident Commands
#define icmdCpAuto                IDM_AUTODETECT

#define icmdOpenLink              IDM_FOLLOWLINKC
#define icmdOpenLinkExt           IDM_FOLLOWLINKN
#define icmdSaveTargetAs          IDM_SAVETARGET
#define icmdPrintTarget           IDM_PRINTTARGET

#define icmdSaveBgrndAs           IDM_SAVEBACKGROUND
#define icmdCopyBackground        IDM_COPYBACKGROUND

#define icmdViewSource            IDM_VIEWSOURCE

#define icmdShowPicture           IDM_SHOWPICTURE
#define icmdSavePicture           IDM_SAVEPICTURE
#define icmdCopyShortcut          IDM_COPYSHORTCUT

#define icmdProperties            IDM_PROPERTIES

#define icmdCloseWB               4998
#define icmdNavigate              4999
#define icmdOpenWB                5000
#define icmdWebBrowserFirst       5001
// don't define command > icmdWebBrowserFirst

///////////////////////////////////////////////////////////////////////////////
// Button Bitmap IDs

#define bmpidWebBrowser           1
#define bmpidBack                 2
#define bmpidForward              3
#define bmpidStop                 4
#define bmpidRefresh              5
#define bmpidHome                 6
#define bmpidSearch               7
#define bmpidFavWindow            8
#define bmpidFavAdd               9
#define bmpidFontSize             10
#define bmpidOpenLink             11
#define bmpidWebSave              12
#define bmpidPicSave              13
#define bmpidProperties           14
#define bmpidFavOrganize          15

#define bmpidSync                 16
#define bmpidPrev                 17
#define bmpidNext                 18
#define bmpidVsDynamicHelp        19

#endif //_WBIDS_H_