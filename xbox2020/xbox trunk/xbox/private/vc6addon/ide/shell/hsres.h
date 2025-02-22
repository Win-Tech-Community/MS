/*

	HSRES.H
	=======

	Copyright 1996, Microsoft Corp.

	The following are helpstring ids for the 
	automation methods and properties.
	See include\ids.h for more information...

*/

#define MIN_HELPSTRING_ID	10000 // Copied from ids.h
#define MAX_HELPSTRING_ID	11000

// Help string constants for IApplication
#define IDS_HS_APPLICATION							MIN_HELPSTRING_ID
#define IDS_HS_APPLICATION_HEIGHT					(IDS_HS_APPLICATION+1)
#define IDS_HS_APPLICATION_WIDTH					(IDS_HS_APPLICATION+2)
#define IDS_HS_APPLICATION_TOP						(IDS_HS_APPLICATION+3)
#define IDS_HS_APPLICATION_LEFT						(IDS_HS_APPLICATION+4)
#define IDS_HS_APPLICATION_NAME						(IDS_HS_APPLICATION+5)
#define IDS_HS_APPLICATION_TEXTEDITOR				(IDS_HS_APPLICATION+6)
#define IDS_HS_APPLICATION_VERSION					(IDS_HS_APPLICATION+7)
#define IDS_HS_APPLICATION_PATH						(IDS_HS_APPLICATION+8)
#define IDS_HS_APPLICATION_CURRENTDIRECTORY			(IDS_HS_APPLICATION+9)
#define IDS_HS_APPLICATION_FULLNAME					(IDS_HS_APPLICATION+10)
#define IDS_HS_APPLICATION_ACTIVEDOCUMENT			(IDS_HS_APPLICATION+11)
#define IDS_HS_APPLICATION_WINDOWS					(IDS_HS_APPLICATION+12)
#define IDS_HS_APPLICATION_DOCUMENTS				(IDS_HS_APPLICATION+13)
#define IDS_HS_APPLICATION_ACTIVEWINDOW				(IDS_HS_APPLICATION+14)
#define IDS_HS_APPLICATION_WINDOWSTATE				(IDS_HS_APPLICATION+15)
#define IDS_HS_APPLICATION_DEBUGGER					(IDS_HS_APPLICATION+16)
#define IDS_HS_APPLICATION_PROJECTS					(IDS_HS_APPLICATION+17)
#define IDS_HS_APPLICATION_DEFAULTCONFIGURATIONS	(IDS_HS_APPLICATION+18)
#define IDS_HS_APPLICATION_VISIBLE					(IDS_HS_APPLICATION+19)
#define IDS_HS_APPLICATION_ACTIVEPROJECT			(IDS_HS_APPLICATION+20)
#define IDS_HS_APPLICATION_ACTIVE					(IDS_HS_APPLICATION+21)
#define IDS_HS_APPLICATION_GETPACKAGEEXTENSION		(IDS_HS_APPLICATION+22)
#define IDS_HS_APPLICATION_QUIT						(IDS_HS_APPLICATION+23)
#define IDS_HS_APPLICATION_PRINTTOOUTPUTWINDOW		(IDS_HS_APPLICATION+24)
#define IDS_HS_APPLICATION_EXECUTECOMMAND			(IDS_HS_APPLICATION+25)
#define IDS_HS_APPLICATION_ADDCOMMANDBARBUTTON		(IDS_HS_APPLICATION+26)
#define IDS_HS_APPLICATION_ADDKEYBINDING			(IDS_HS_APPLICATION+27)
#define IDS_HS_APPLICATION_BUILD					(IDS_HS_APPLICATION+28)
#define IDS_HS_APPLICATION_REBUILDALL				(IDS_HS_APPLICATION+29)
#define IDS_HS_APPLICATION_SETADDININFO				(IDS_HS_APPLICATION+30)
#define IDS_HS_APPLICATION_ADDCOMMAND				(IDS_HS_APPLICATION+31)
#define IDS_HS_APPLICATION_ENABLEMODELESS			(IDS_HS_APPLICATION+32)
#define IDS_HS_APPLICATION_CLEAN					(IDS_HS_APPLICATION+33)
#define IDS_HS_APPLICATION_ERRORS					(IDS_HS_APPLICATION+34)
#define IDS_HS_APPLICATION_WARNINGS					(IDS_HS_APPLICATION+35)
#define IDS_HS_APPLICATION_ADDPROJECT				(IDS_HS_APPLICATION+36)
#define IDS_HS_APPLICATION_EXECUTE     				(IDS_HS_APPLICATION+37)
#define IDS_HS_APPLICATION_max						(IDS_HS_APPLICATION+38)


// Helpstring constants for IApplicationEvents
#define IDS_HS_APPLICATION_EVENTS							IDS_HS_APPLICATION_max
#define IDS_HS_APPLICATION_EVENTS_BEFOREBUILDSTART			(IDS_HS_APPLICATION_EVENTS+1)
#define IDS_HS_APPLICATION_EVENTS_BUILDFINISH				(IDS_HS_APPLICATION_EVENTS+2)
#define IDS_HS_APPLICATION_EVENTS_BEFOREAPPLICATIONSHUTDOWN	(IDS_HS_APPLICATION_EVENTS+3)
#define IDS_HS_APPLICATION_EVENTS_DOCUMENTOPEN				(IDS_HS_APPLICATION_EVENTS+4)
#define IDS_HS_APPLICATION_EVENTS_BEFOREDOCUMENTCLOSE		(IDS_HS_APPLICATION_EVENTS+5)
#define IDS_HS_APPLICATION_EVENTS_DOCUMENTSAVE				(IDS_HS_APPLICATION_EVENTS+6)
#define IDS_HS_APPLICATION_EVENTS_NEWDOCUMENT				(IDS_HS_APPLICATION_EVENTS+7)
#define IDS_HS_APPLICATION_EVENTS_WINDOWACTIVATE			(IDS_HS_APPLICATION_EVENTS+8)
#define IDS_HS_APPLICATION_EVENTS_WINDOWDEACTIVATE			(IDS_HS_APPLICATION_EVENTS+9)
#define IDS_HS_APPLICATION_EVENTS_WORKSPACEOPEN				(IDS_HS_APPLICATION_EVENTS+10)
#define IDS_HS_APPLICATION_EVENTS_WORKSPACECLOSE			(IDS_HS_APPLICATION_EVENTS+11)
#define IDS_HS_APPLICATION_EVENTS_NEWWORKSPACE				(IDS_HS_APPLICATION_EVENTS+12)
#define IDS_HS_APPLICATION_EVENTS_max						(IDS_HS_APPLICATION_EVENTS+13)

// Helpstring contants for IDocuments
#define IDS_HS_DOCUMENTS			IDS_HS_APPLICATION_EVENTS_max
#define IDS_HS_DOCUMENTS_COUNT		(IDS_HS_DOCUMENTS+1)
#define IDS_HS_DOCUMENTS_ITEM		(IDS_HS_DOCUMENTS+3)
#define IDS_HS_DOCUMENTS_SAVEALL	(IDS_HS_DOCUMENTS+4)
#define IDS_HS_DOCUMENTS_CLOSEALL	(IDS_HS_DOCUMENTS+5)
#define IDS_HS_DOCUMENTS_ADD		(IDS_HS_DOCUMENTS+6)
#define IDS_HS_DOCUMENTS_OPEN		(IDS_HS_DOCUMENTS+7)
#define IDS_HS_DOCUMENTS_max		(IDS_HS_DOCUMENTS+8)

// Helpstrings constants for IWindows
#define IDS_HS_WINDOWS				IDS_HS_DOCUMENTS_max
#define IDS_HS_WINDOWS_COUNT		(IDS_HS_WINDOWS+1)
#define IDS_HS_WINDOWS_ITEM			(IDS_HS_WINDOWS+2)
#define IDS_HS_WINDOWS_ARRANGE		(IDS_HS_WINDOWS+3)
#define IDS_HS_WINDOWS_CLOSEALL		(IDS_HS_WINDOWS+4)
#define IDS_HS_WINDOWS_max			(IDS_HS_WINDOWS+5)

// Helpstring constants for IWindowEvent
#define IDS_HS_WINDOW_EVENT				IDS_HS_WINDOWS_max
#define IDS_HS_WINDOW_EVENT_ACTIVATE	(IDS_HS_WINDOW_EVENT+1)
#define IDS_HS_WINDOW_EVENT_DEACTIVATE	(IDS_HS_WINDOW_EVENT+2)
#define IDS_HS_WINDOW_EVENT_max			(IDS_HS_WINDOW_EVENT+3)

// Helpstring constants for IProjects
#define IDS_HS_PROJECTS			IDS_HS_WINDOW_EVENT_max
#define IDS_HS_PROJECTS_COUNT	(IDS_HS_PROJECTS+1)
#define IDS_HS_PROJECTS_ITEM	(IDS_HS_PROJECTS+2)
#define IDS_HS_PROJECTS_max		(IDS_HS_PROJECTS+3)

// Helpstrings constants for Shell.ODL
#define IDS_HS_SHELL				IDS_HS_PROJECTS_max
#define IDS_HS_SHELL_TYPELIBRARY	(IDS_HS_SHELL+1)
#define IDS_HS_SHELL_max			(IDS_HS_SHELL+2)





