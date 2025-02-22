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
/* This header file machine-generated by mktyplib.exe */
/* Interface to type library: tom */

#ifndef _tom_H_
#define _tom_H_

DEFINE_GUID(LIBID_tom,0x8CC497C9L,0xA1DF,0x11CE,0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D);

interface ITextSelection;

interface ITextRange;

interface ITextFont;

interface ITextPara;

interface ITextStoryRanges;

typedef enum {
    tomFalse = 0,
    tomTrue = -1,
    tomUndefined = -9999999,
    tomToggle = -9999998,
    tomAutoColor = -9999997,
    tomDefault = -9999996,
    tomBackward = -1073741823,
    tomForward = 1073741823,
    tomMove = 0,
    tomExtend = 1,
    tomNoSelection = 0,
    tomSelectionIP = 1,
    tomSelectionNormal = 2,
    tomSelectionFrame = 3,
    tomSelectionColumn = 4,
    tomSelectionRow = 5,
    tomSelectionBlock = 6,
    tomSelectionInlineShape = 7,
    tomSelectionShape = 8,
    tomSelStartActive = 1,
    tomSelAtEOL = 2,
    tomSelOvertype = 4,
    tomSelActive = 8,
    tomSelReplace = 16,
    tomEnd = 0,
    tomStart = 32,
    tomCollapseEnd = 0,
    tomCollapseStart = 1,
    tomNone = 0,
    tomSingle = 1,
    tomWords = 2,
    tomDouble = 3,
    tomDotted = 4,
    tomLineSpaceSingle = 0,
    tomLineSpace1pt5 = 1,
    tomLineSpaceDouble = 2,
    tomLineSpaceAtLeast = 3,
    tomLineSpaceExactly = 4,
    tomLineSpaceMultiple = 5,
    tomAlignLeft = 0,
    tomAlignCenter = 1,
    tomAlignRight = 2,
    tomAlignJustify = 3,
    tomAlignDecimal = 3,
    tomAlignBar = 4,
    tomSpaces = 0,
    tomDots = 1,
    tomDashes = 2,
    tomLines = 3,
    tomTabBack = -3,
    tomTabNext = -2,
    tomTabHere = -1,
    tomListNone = 0,
    tomListBullet = 1,
    tomListNumberAsArabic = 2,
    tomListNumberAsLCLetter = 3,
    tomListNumberAsUCLetter = 4,
    tomListNumberAsLCRoman = 5,
    tomListNumberAsUCRoman = 6,
    tomListNumberAsKatakanaAIUEOdbl = 7, // GuyBark Juptier: Added this and bumped the later sequence number.
    tomListNumberAsKatakanaIROHAdbl = 8, // GuyBark Juptier: Added this and bumped the later sequence number.
    tomListNumberAsSequence = 9,
    tomListParentheses = 65536,
    tomListPeriod = 131072,
    tomListPlain = 196608,
    tomCharacter = 1,
    tomWord = 2,
    tomSentence = 3,
    tomParagraph = 4,
    tomLine = 5,
    tomStory = 6,
    tomScreen = 7,
    tomSection = 8,
    tomColumn = 9,
    tomRow = 10,
    tomWindow = 11,
    tomCell = 12,
    tomCharFormat = 13,
    tomParaFormat = 14,
    tomTable = 15,
    tomObject = 16,
    tomMatchWord = 2,
    tomMatchCase = 4,
    tomMatchPattern = 8,
    tomUnknownStory = 0,
    tomMainTextStory = 1,
    tomFootnotesStory = 2,
    tomEndnotesStory = 3,
    tomCommentsStory = 4,
    tomTextFrameStory = 5,
    tomEvenPagesHeaderStory = 6,
    tomPrimaryHeaderStory = 7,
    tomEvenPagesFooterStory = 8,
    tomPrimaryFooterStory = 9,
    tomFirstPageHeaderStory = 10,
    tomFirstPageFooterStory = 11,
    tomNoAnimation = 0,
    tomLasVegasLights = 1,
    tomBlinkingBackground = 2,
    tomSparkleText = 3,
    tomMarchingBlackAnts = 4,
    tomMarchingRedAnts = 5,
    tomShimmer = 6,
    tomWipeDown = 7,
    tomWipeRight = 8,
    tomAnimationMax = 8,
    tomLowerCase = 0,
    tomUpperCase = 1,
    tomTitleCase = 2,
    tomSentenceCase = 4,
    tomToggleCase = 5,
    tomReadOnly = 256,
    tomShareDenyRead = 512,
    tomShareDenyWrite = 1024,
    tomPasteFile = 4096,
    tomCreateNew = 16,
    tomCreateAlways = 32,
    tomOpenExisting = 48,
    tomOpenAlways = 64,
    tomTruncateExisting = 80,
    tomRTF = 1,
    tomText = 2,
    tomHTML = 3,
    tomWordDocument = 4
} tomConstants;

DEFINE_GUID(IID_ITextDocument,0x8CC497C0L,0xA1DF,0x11CE,0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D);

/* Definition of interface: ITextDocument */
#undef INTERFACE
#define INTERFACE ITextDocument

DECLARE_INTERFACE_(ITextDocument, IDispatch)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;
#endif

    /* ITextDocument methods */
    STDMETHOD(GetName)(THIS_ BSTR FAR* pName) PURE;
    STDMETHOD(GetSelection)(THIS_ ITextSelection FAR* FAR* ppSel) PURE;
    STDMETHOD(GetStoryCount)(THIS_ long FAR* pCount) PURE;
    STDMETHOD(GetStoryRanges)(THIS_ ITextStoryRanges FAR* FAR* ppStories) PURE;
    STDMETHOD(GetSaved)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetSaved)(THIS_ long Value) PURE;
    STDMETHOD(GetDefaultTabStop)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetDefaultTabStop)(THIS_ float Value) PURE;
    STDMETHOD(New)(THIS) PURE;
    STDMETHOD(Open)(THIS_ VARIANT FAR* pVar, long Flags, long CodePage) PURE;
    STDMETHOD(Save)(THIS_ VARIANT FAR* pVar, long Flags, long CodePage) PURE;
    STDMETHOD(Freeze)(THIS_ long FAR* pCount) PURE;
    STDMETHOD(Unfreeze)(THIS_ long FAR* pCount) PURE;
    STDMETHOD(BeginEditCollection)(THIS) PURE;
    STDMETHOD(EndEditCollection)(THIS) PURE;
    STDMETHOD(Undo)(THIS_ long Count, long FAR* prop) PURE;
    STDMETHOD(Redo)(THIS_ long Count, long FAR* prop) PURE;
    STDMETHOD(Range)(THIS_ long cp1, long cp2, ITextRange FAR* FAR* ppRange) PURE;
    STDMETHOD(RangeFromPoint)(THIS_ long x, long y, ITextRange FAR* FAR* ppRange) PURE;
};

DEFINE_GUID(IID_ITextRange,0x8CC497C2L,0xA1DF,0x11CE,0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D);

/* Definition of interface: ITextRange */
#undef INTERFACE
#define INTERFACE ITextRange

DECLARE_INTERFACE_(ITextRange, IDispatch)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;
#endif

    /* ITextRange methods */
    STDMETHOD(GetText)(THIS_ BSTR FAR* pbstr) PURE;
    STDMETHOD(SetText)(THIS_ BSTR bstr) PURE;
    STDMETHOD(GetChar)(THIS_ long FAR* pch) PURE;
    STDMETHOD(SetChar)(THIS_ long ch) PURE;
    STDMETHOD(GetDuplicate)(THIS_ ITextRange FAR* FAR* ppRange) PURE;
    STDMETHOD(GetFormattedText)(THIS_ ITextRange FAR* FAR* ppRange) PURE;
    STDMETHOD(SetFormattedText)(THIS_ ITextRange FAR* pRange) PURE;
    STDMETHOD(GetStart)(THIS_ long FAR* pcpFirst) PURE;
    STDMETHOD(SetStart)(THIS_ long cpFirst) PURE;
    STDMETHOD(GetEnd)(THIS_ long FAR* pcpLim) PURE;
    STDMETHOD(SetEnd)(THIS_ long cpLim) PURE;
    STDMETHOD(GetFont)(THIS_ ITextFont FAR* FAR* pFont) PURE;
    STDMETHOD(SetFont)(THIS_ ITextFont FAR* pFont) PURE;
    STDMETHOD(GetPara)(THIS_ ITextPara FAR* FAR* pPara) PURE;
    STDMETHOD(SetPara)(THIS_ ITextPara FAR* pPara) PURE;
    STDMETHOD(GetStoryLength)(THIS_ long FAR* pcch) PURE;
    STDMETHOD(GetStoryType)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(Collapse)(THIS_ long bStart) PURE;
    STDMETHOD(Expand)(THIS_ long Unit, long FAR* pDelta) PURE;
    STDMETHOD(GetIndex)(THIS_ long Unit, long FAR* pIndex) PURE;
    STDMETHOD(SetIndex)(THIS_ long Unit, long Index, long Extend) PURE;
    STDMETHOD(SetRange)(THIS_ long cpActive, long cpOther) PURE;
    STDMETHOD(InRange)(THIS_ ITextRange FAR* pRange, long FAR* pb) PURE;
    STDMETHOD(InStory)(THIS_ ITextRange FAR* pRange, long FAR* pb) PURE;
    STDMETHOD(IsEqual)(THIS_ ITextRange FAR* pRange, long FAR* pb) PURE;
    STDMETHOD(Select)(THIS) PURE;
    STDMETHOD(StartOf)(THIS_ long Unit, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(EndOf)(THIS_ long Unit, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(Move)(THIS_ long Unit, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveStart)(THIS_ long Unit, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveEnd)(THIS_ long Unit, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveWhile)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveStartWhile)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveEndWhile)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveUntil)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveStartUntil)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveEndUntil)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(FindText)(THIS_ BSTR bstr, long cch, long Flags, long FAR* pLength) PURE;
    STDMETHOD(FindTextStart)(THIS_ BSTR bstr, long cch, long Flags, long FAR* pLength) PURE;
    STDMETHOD(FindTextEnd)(THIS_ BSTR bstr, long cch, long Flags, long FAR* pLength) PURE;
    STDMETHOD(Delete)(THIS_ long Unit, long Count, long FAR* pDelta) PURE;
    STDMETHOD(Cut)(THIS_ VARIANT FAR* pVar) PURE;
    STDMETHOD(Copy)(THIS_ VARIANT FAR* pVar) PURE;
    STDMETHOD(Paste)(THIS_ VARIANT FAR* pVar, long Format) PURE;
    STDMETHOD(CanPaste)(THIS_ VARIANT FAR* pVar, long Format, long FAR* pb) PURE;
    STDMETHOD(CanEdit)(THIS_ long FAR* pbCanEdit) PURE;
    STDMETHOD(ChangeCase)(THIS_ long Type) PURE;
    STDMETHOD(GetPoint)(THIS_ long Type, long FAR* px, long FAR* py) PURE;
    STDMETHOD(SetPoint)(THIS_ long x, long y, long Type, long Extend) PURE;
    STDMETHOD(ScrollIntoView)(THIS_ long Value) PURE;
    STDMETHOD(GetEmbeddedObject)(THIS_ IUnknown * FAR* ppv) PURE;
};

DEFINE_GUID(IID_ITextSelection,0x8CC497C1L,0xA1DF,0x11CE,0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D);

/* Definition of interface: ITextSelection */
#undef INTERFACE
#define INTERFACE ITextSelection

DECLARE_INTERFACE_(ITextSelection, ITextRange)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;

    /* ITextRange methods */
    STDMETHOD(GetText)(THIS_ BSTR FAR* pbstr) PURE;
    STDMETHOD(SetText)(THIS_ BSTR bstr) PURE;
    STDMETHOD(GetChar)(THIS_ long FAR* pch) PURE;
    STDMETHOD(SetChar)(THIS_ long ch) PURE;
    STDMETHOD(GetDuplicate)(THIS_ ITextRange FAR* FAR* ppRange) PURE;
    STDMETHOD(GetFormattedText)(THIS_ ITextRange FAR* FAR* ppRange) PURE;
    STDMETHOD(SetFormattedText)(THIS_ ITextRange FAR* pRange) PURE;
    STDMETHOD(GetStart)(THIS_ long FAR* pcpFirst) PURE;
    STDMETHOD(SetStart)(THIS_ long cpFirst) PURE;
    STDMETHOD(GetEnd)(THIS_ long FAR* pcpLim) PURE;
    STDMETHOD(SetEnd)(THIS_ long cpLim) PURE;
    STDMETHOD(GetFont)(THIS_ ITextFont FAR* FAR* pFont) PURE;
    STDMETHOD(SetFont)(THIS_ ITextFont FAR* pFont) PURE;
    STDMETHOD(GetPara)(THIS_ ITextPara FAR* FAR* pPara) PURE;
    STDMETHOD(SetPara)(THIS_ ITextPara FAR* pPara) PURE;
    STDMETHOD(GetStoryLength)(THIS_ long FAR* pcch) PURE;
    STDMETHOD(GetStoryType)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(Collapse)(THIS_ long bStart) PURE;
    STDMETHOD(Expand)(THIS_ long Unit, long FAR* pDelta) PURE;
    STDMETHOD(GetIndex)(THIS_ long Unit, long FAR* pIndex) PURE;
    STDMETHOD(SetIndex)(THIS_ long Unit, long Index, long Extend) PURE;
    STDMETHOD(SetRange)(THIS_ long cpActive, long cpOther) PURE;
    STDMETHOD(InRange)(THIS_ ITextRange FAR* pRange, long FAR* pb) PURE;
    STDMETHOD(InStory)(THIS_ ITextRange FAR* pRange, long FAR* pb) PURE;
    STDMETHOD(IsEqual)(THIS_ ITextRange FAR* pRange, long FAR* pb) PURE;
    STDMETHOD(Select)(THIS) PURE;
    STDMETHOD(StartOf)(THIS_ long Unit, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(EndOf)(THIS_ long Unit, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(Move)(THIS_ long Unit, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveStart)(THIS_ long Unit, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveEnd)(THIS_ long Unit, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveWhile)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveStartWhile)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveEndWhile)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveUntil)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveStartUntil)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(MoveEndUntil)(THIS_ VARIANT FAR* Cset, long Count, long FAR* pDelta) PURE;
    STDMETHOD(FindText)(THIS_ BSTR bstr, long cch, long Flags, long FAR* pLength) PURE;
    STDMETHOD(FindTextStart)(THIS_ BSTR bstr, long cch, long Flags, long FAR* pLength) PURE;
    STDMETHOD(FindTextEnd)(THIS_ BSTR bstr, long cch, long Flags, long FAR* pLength) PURE;
    STDMETHOD(Delete)(THIS_ long Unit, long Count, long FAR* pDelta) PURE;
    STDMETHOD(Cut)(THIS_ VARIANT FAR* pVar) PURE;
    STDMETHOD(Copy)(THIS_ VARIANT FAR* pVar) PURE;
    STDMETHOD(Paste)(THIS_ VARIANT FAR* pVar, long Format) PURE;
    STDMETHOD(CanPaste)(THIS_ VARIANT FAR* pVar, long Format, long FAR* pb) PURE;
    STDMETHOD(CanEdit)(THIS_ long FAR* pbCanEdit) PURE;
    STDMETHOD(ChangeCase)(THIS_ long Type) PURE;
    STDMETHOD(GetPoint)(THIS_ long Type, long FAR* px, long FAR* py) PURE;
    STDMETHOD(SetPoint)(THIS_ long x, long y, long Type, long Extend) PURE;
    STDMETHOD(ScrollIntoView)(THIS_ long Value) PURE;
    STDMETHOD(GetEmbeddedObject)(THIS_ IUnknown * FAR* ppv) PURE;
#endif

    /* ITextSelection methods */
    STDMETHOD(GetFlags)(THIS_ long FAR* pFlags) PURE;
    STDMETHOD(SetFlags)(THIS_ long Flags) PURE;
    STDMETHOD(GetType)(THIS_ long FAR* pType) PURE;
    STDMETHOD(MoveLeft)(THIS_ long Unit, long Count, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(MoveRight)(THIS_ long Unit, long Count, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(MoveUp)(THIS_ long Unit, long Count, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(MoveDown)(THIS_ long Unit, long Count, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(HomeKey)(THIS_ long Unit, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(EndKey)(THIS_ long Unit, long Extend, long FAR* pDelta) PURE;
    STDMETHOD(TypeText)(THIS_ BSTR bstr) PURE;
};

DEFINE_GUID(IID_ITextFont,0x8CC497C3L,0xA1DF,0x11CE,0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D);

/* Definition of interface: ITextFont */
#undef INTERFACE
#define INTERFACE ITextFont

DECLARE_INTERFACE_(ITextFont, IDispatch)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;
#endif

    /* ITextFont methods */
    STDMETHOD(GetDuplicate)(THIS_ ITextFont FAR* FAR* ppFont) PURE;
    STDMETHOD(SetDuplicate)(THIS_ ITextFont FAR* pFont) PURE;
    STDMETHOD(CanChange)(THIS_ long FAR* pB) PURE;
    STDMETHOD(IsEqual)(THIS_ ITextFont FAR* pFont, long FAR* pB) PURE;
    STDMETHOD(Reset)(THIS_ long Value) PURE;
    STDMETHOD(GetStyle)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetStyle)(THIS_ long Value) PURE;
    STDMETHOD(GetAllCaps)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetAllCaps)(THIS_ long Value) PURE;
    STDMETHOD(GetAnimation)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetAnimation)(THIS_ long Value) PURE;
    STDMETHOD(GetBackColor)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetBackColor)(THIS_ long Value) PURE;
    STDMETHOD(GetBold)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetBold)(THIS_ long Value) PURE;
    STDMETHOD(GetEmboss)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetEmboss)(THIS_ long Value) PURE;
    STDMETHOD(GetForeColor)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetForeColor)(THIS_ long Value) PURE;
    STDMETHOD(GetHidden)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetHidden)(THIS_ long Value) PURE;
    STDMETHOD(GetEngrave)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetEngrave)(THIS_ long Value) PURE;
    STDMETHOD(GetItalic)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetItalic)(THIS_ long Value) PURE;
    STDMETHOD(GetKerning)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetKerning)(THIS_ float Value) PURE;
    STDMETHOD(GetLanguageID)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetLanguageID)(THIS_ long Value) PURE;
    STDMETHOD(GetName)(THIS_ BSTR FAR* pbstr) PURE;
    STDMETHOD(SetName)(THIS_ BSTR bstr) PURE;
    STDMETHOD(GetOutline)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetOutline)(THIS_ long Value) PURE;
    STDMETHOD(GetPosition)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetPosition)(THIS_ float Value) PURE;
    STDMETHOD(GetProtected)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetProtected)(THIS_ long Value) PURE;
    STDMETHOD(GetShadow)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetShadow)(THIS_ long Value) PURE;
    STDMETHOD(GetSize)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetSize)(THIS_ float Value) PURE;
    STDMETHOD(GetSmallCaps)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetSmallCaps)(THIS_ long Value) PURE;
    STDMETHOD(GetSpacing)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetSpacing)(THIS_ float Value) PURE;
    STDMETHOD(GetStrikeThrough)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetStrikeThrough)(THIS_ long Value) PURE;
    STDMETHOD(GetSubscript)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetSubscript)(THIS_ long Value) PURE;
    STDMETHOD(GetSuperscript)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetSuperscript)(THIS_ long Value) PURE;
    STDMETHOD(GetUnderline)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetUnderline)(THIS_ long Value) PURE;
    STDMETHOD(GetWeight)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetWeight)(THIS_ long Value) PURE;
};

DEFINE_GUID(IID_ITextPara,0x8CC497C4L,0xA1DF,0x11CE,0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D);

/* Definition of interface: ITextPara */
#undef INTERFACE
#define INTERFACE ITextPara

DECLARE_INTERFACE_(ITextPara, IDispatch)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;
#endif

    /* ITextPara methods */
    STDMETHOD(GetDuplicate)(THIS_ ITextPara FAR* FAR* ppPara) PURE;
    STDMETHOD(SetDuplicate)(THIS_ ITextPara FAR* pPara) PURE;
    STDMETHOD(CanChange)(THIS_ long FAR* pB) PURE;
    STDMETHOD(IsEqual)(THIS_ ITextPara FAR* pPara, long FAR* pB) PURE;
    STDMETHOD(Reset)(THIS_ long Value) PURE;
    STDMETHOD(GetStyle)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetStyle)(THIS_ long Value) PURE;
    STDMETHOD(GetAlignment)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetAlignment)(THIS_ long Value) PURE;
    STDMETHOD(GetHyphenation)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetHyphenation)(THIS_ long Value) PURE;
    STDMETHOD(GetFirstLineIndent)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(GetKeepTogether)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetKeepTogether)(THIS_ long Value) PURE;
    STDMETHOD(GetKeepWithNext)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetKeepWithNext)(THIS_ long Value) PURE;
    STDMETHOD(GetLeftIndent)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(GetLineSpacing)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(GetLineSpacingRule)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(GetListAlignment)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetListAlignment)(THIS_ long Value) PURE;
    STDMETHOD(GetListLevelIndex)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetListLevelIndex)(THIS_ long Value) PURE;
    STDMETHOD(GetListStart)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetListStart)(THIS_ long Value) PURE;
    STDMETHOD(GetListTab)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetListTab)(THIS_ float Value) PURE;
    STDMETHOD(GetListType)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetListType)(THIS_ long Value) PURE;
    STDMETHOD(GetNoLineNumber)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetNoLineNumber)(THIS_ long Value) PURE;
    STDMETHOD(GetPageBreakBefore)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetPageBreakBefore)(THIS_ long Value) PURE;
    STDMETHOD(GetRightIndent)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetRightIndent)(THIS_ float Value) PURE;
    STDMETHOD(SetIndents)(THIS_ float StartIndent, float LeftIndent, float RightIndent) PURE;
    STDMETHOD(SetLineSpacing)(THIS_ long LineSpacingRule, float LineSpacing) PURE;
    STDMETHOD(GetSpaceAfter)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetSpaceAfter)(THIS_ float Value) PURE;
    STDMETHOD(GetSpaceBefore)(THIS_ float FAR* pValue) PURE;
    STDMETHOD(SetSpaceBefore)(THIS_ float Value) PURE;
    STDMETHOD(GetWidowControl)(THIS_ long FAR* pValue) PURE;
    STDMETHOD(SetWidowControl)(THIS_ long Value) PURE;
    STDMETHOD(GetTabCount)(THIS_ long FAR* pCount) PURE;
    STDMETHOD(AddTab)(THIS_ float tbPos, long tbAlign, long tbLeader) PURE;
    STDMETHOD(ClearAllTabs)(THIS) PURE;
    STDMETHOD(DeleteTab)(THIS_ float tbPos) PURE;
    STDMETHOD(GetTab)(THIS_ long iTab, float FAR* ptbPos, long FAR* ptbAlign, long FAR* ptbLeader) PURE;
};

DEFINE_GUID(IID_ITextStoryRanges,0x8CC497C5L,0xA1DF,0x11CE,0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D);

/* Definition of interface: ITextStoryRanges */
#undef INTERFACE
#define INTERFACE ITextStoryRanges

DECLARE_INTERFACE_(ITextStoryRanges, IDispatch)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IDispatch methods */
    STDMETHOD(GetTypeInfoCount)(THIS_ UINT FAR* pctinfo) PURE;

    STDMETHOD(GetTypeInfo)(
      THIS_
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo) PURE;

    STDMETHOD(GetIDsOfNames)(
      THIS_
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid) PURE;

    STDMETHOD(Invoke)(
      THIS_
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr) PURE;
#endif

    /* ITextStoryRanges methods */
    STDMETHOD(_NewEnum)(THIS_ IUnknown * FAR* ppunkEnum) PURE;
    STDMETHOD(Item)(THIS_ long Index, ITextRange FAR* FAR* ppRange) PURE;
    STDMETHOD(GetCount)(THIS_ long FAR* pCount) PURE;
};

#endif

