//
// Common Resource Compiler Tool
//
// [v-danwh],[matthewt]
//

#ifndef _INCLUDE_TOOLRC_CMN_H
#define _INCLUDE_TOOLRC_CMN_H

#include "projtool.h"		// the CBuildTool classes
#include "optnrc.h"			// our COMMON resource compiler tool options

class BLD_IFACE CRCCompilerTool : public CBuildTool
{
	DECLARE_DYNAMIC (CRCCompilerTool)

public:
	CRCCompilerTool();

	// -> from CBuildTool
	virtual UINT PerformBuildActions(UINT type, UINT stage, CActionSlobList & lstActions,
						     		 DWORD attrib, CErrorContext & EC);

	virtual BOOL GenerateDependencies(CActionSlob * pAction, FileRegHandle frhFile, CErrorContext & EC);
	virtual BOOL DontWriteDependencies( ConfigurationRecord* pcr) { return TRUE; }

	// Return the files generated by the rc compiler tool
	virtual BOOL GenerateOutput(UINT type, CActionSlobList & actions, CErrorContext & EC);

	// Affects our output?
	virtual BOOL AffectsOutput(UINT idProp);

 	// generate command lines for a resource compiler, doing all the good ordering things
	BOOL GetCommandLines(CActionSlobList &, CPtrList &, DWORD, CErrorContext &);
	// <- from CBuildTool

	virtual BOOL IsScannable() {return TRUE;}

	virtual void GetIncludePaths(CProjItem * pItem, CString & str);

protected:
	virtual void WriteInferenceRuleMacro(CActionSlob * pAction);

	enum ResTokens 
	{
		TOKEN_EOF,
		TOKEN_NEWLINE,
		TOKEN_HASHSIGN,
		TOKEN_WORD,
		TOKEN_INCLUDE,
		TOKEN_BITMAP,
		TOKEN_CURSOR,
		TOKEN_ICON,
		TOKEN_TYPELIB,
		TOKEN_LOADONCALL,
		TOKEN_PRELOAD,
		TOKEN_FIXED,
		TOKEN_MOVEABLE,
		TOKEN_DISCARDABLE,
		TOKEN_FONT,
		TOKEN_RCINCLUDE,
		TOKEN_COMMENT,
		TOKEN_PURE,
		TOKEN_IMPURE,
		TOKEN_STOP_SCAN,
		TOKEN_START_SCAN,
		TOKEN_ACCELERATORS,
		TOKEN_DIALOG,
		TOKEN_DLGINIT,
		TOKEN_MENU,
		TOKEN_RCDATA,
		TOKEN_STRINGTABLE,
		TOKEN_BEGIN,
		TOKEN_END,
		TOKEN_VERSIONINFO,
		TOKEN_ERROR, 
		TOKEN_UNDEF, 
		TOKEN_DEFINE,
		TOKEN_LANGUAGE,
		TOKEN_GUIDELINES,
		TOKEN_TOOLBAR,
		TOKEN_DIALOGEX,
		TOKEN_MENUEX
	};
		
	static ResTokens GetNextToken(const TCHAR * pMax, const TCHAR * & pCurrent,
								  const TCHAR * & pTokenStart);

private:
	static void InitTokenMap();
	static BOOL m_bTokenMapIsInit;
	static CMapStringToPtr m_mapResTokens;
};

// NT RC Compiler Tool
class BLD_IFACE CRCCompilerNTTool : public CRCCompilerTool 
{
	DECLARE_DYNAMIC (CRCCompilerNTTool)

public:
	//	Ensure that the tool will build an MFC project item.
	//	Likely to entail doing such things as munging tool options, eg. the libs for linker
	virtual BOOL PerformSettingsWizard(CProjItem *, BOOL fDebug, int iUseMFC);
};

#endif // _INCLUDE_TOOLRC_CMN_H
