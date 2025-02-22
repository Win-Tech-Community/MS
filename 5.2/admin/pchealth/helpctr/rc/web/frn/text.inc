<% @LANGUAGE="VBScript" @EnableSessionState="False"  %>
<% 'Option Explicit

Function GetString(ByVal sStringName)
	If InStr(sStringName, "L_") <> 1 Then sStringName = "L_" & sStringName & "_Text"

	'' Texts
	Const L_StartRemoteAssistance_Text  		= "D�marrer l'assistance � distance"
	Const L_ProductName_Text			= "Assistance � distance"
	Const L_Title1Paragraph1_Text		= "Aide sur l'utilisation de l'assistance � distance"
	Const L_Paragraph1_Text				= "Parfois, la meilleure fa�on d'aider quelqu'un � r�soudre un probl�me consiste � lui montrer la solution. L'assistance � distance est une connexion s�curis�e que vous pouvez utiliser pour montrer � un ami comment obtenir le r�sultat souhait� sur son ordinateur."
	Const L_Paragraph2_Text				= "Si vous utilisez cette fonctionnalit� pour la premi�re fois, consultez les notes ci-dessous."
	Const L_StartRAMessage_Text			= "<font color=""#000000"" size=""2"">Pour vous connecter � l'ordinateur d'un ami, cliquez sur </font><b><font color=""#000000"" size=""2""><b> D�marrer l'assistance � distance.</b></font></b>"
	Const L_StartRAButton_Text			= "D�marrer l'assistance � distance"
	Const L_JScriptNotAvail1_Text		= "Les param�tres de s�curit� actuels d'Internet Explorer ne permettent pas d'utiliser l'assistance � distance. Pour utiliser l'assistance � distance, modifiez ces param�tres ou ajoutez ce site en tant que  site de confiance."
	Const L_IEHelp_Text					= "Pour plus d'informations sur la modification des param�tres de s�curit�, consultez l'aide d'Internet Explorer."
	Const L_TicketError1_Text			= "Votre invitation d'assistance � distance est absente ou n'est pas valide. Pour utiliser l'assistance � distance, vous devez avoir une invitation valide."
	Const L_InstallIE_Text				= "Pour pouvoir accepter une invitation d'assistance � distance, vous devez installer Internet Explorer 5.5."
	Const L_TicketErrorMsg_Text			= "Pour en apprendre davantage sur l'assistance � distance, cliquez sur <B>D�marrer</B> dans Windows XP, cliquez sur <B>Aide et support</B>, puis entrez <B>Assistance � distance</B> dans la zone de saisie <B>Rechercher</B>."
	
	Const L_NotesTitle_Text				= "Notes"
	Const L_NotesLine1_Text				= "N'acceptez les invitations que des personnes en qui vous avez confiance."
	
	Const L_NotesLine2_Text				= "Vous-m�me et la personne que vous aidez devez �tre connect�s � Internet afin d'utiliser l'assistance � distance. Si la personne qui a envoy� cette invitation peut accepter votre demande de connexion � son  ordinateur, vous pourrez voir son �cran et dialoguer avec elle en temps r�el."
	
	Const L_NotesLine6_Text				= "Ceci est une connexion s�curis�e unidirectionnelle. L'utilisateur de l'ordinateur distant auquel vous �tes connect� ne pourra � aucun moment acc�der � votre ordinateur. Si vous travaillez sur un r�seau local ou d'entreprise, les pare-feu peuvent vous emp�cher d'utiliser l'assistance � distance. Dans ce cas, contactez votre administrateur r�seau avant d'utiliser l'assistance � r�seau."
	
	Const L_LearnXP_Text				= "Pour en apprendre davantage sur l'assistance � distance, cliquez sur <B>D�marrer</B> dans Windows XP, cliquez sur <B>Aide et support</B>, puis entrez <B>Assistance � distance</B> dans la zone de saisie <B>Rechercher</B>."
	
	Const L_ContactUsMsg_Text			= "Nous contacter"
	

	Const L_XPNewsletterMsg_Text		= "Lettres d'information gratuites"
	Const L_EmailPage_Text				= "Envoyer cette page par courrier �lectronique"
	
	Const L_CopyRightMsg_Text			= "(C) 2001 Microsoft Corporation. Tous droits r�serv�s. Conditions d'utilisation."
	
	Const L_PrivacyMsg_Text				= "D�claration de confidentialit�"

	Const L_AccMsg_Text					= "Accessibilit�"

	Const L_NotIEError1_Text			= "Pour pouvoir accepter une invitation d'assistance � distance, vous devez installer Internet Explorer 5.5 ou une version ult�rieure."

	Const L_NotXPError1_Text			= "L'assistance � distance est une fonctionnalit� de Microsoft Windows&nbsp;XP. Afin de pouvoir utiliser Windows, vous devez installer Windows&nbsp;XP."

	Const L_IELinkMsg_Text				= "T�l�charger la derni�re version d'Internet Explorer."
	Const L_XPLinkMsg_Text				= "Pour en savoir plus sur Windows XP, allez sur le site"
	Const L_XPLinkMsg2_Text				= "Web de Microsoft Windows"
	Const L_XPLinkMsg3_Text				= "."
	
	Const L_IntroMsg1_Text              = "T�l�chargement d'un composant requis pour utiliser l'assistance � distance. Si vous avez un modem 28.8 Kbits/s, le t�l�chargement pourrait durer une minute."
    Const L_IntroMsg2_Text              = "Pour ex�cuter l'assistance � distance, Active Scripting doit �tre activ�. Si apr�s la p�riode de t�l�chargement estim� cette page ne confirme pas que la fin du t�l�chargement, v�rifiez que le script est activ�."
    Const L_IntroMsg3_Text              = "Pour activer Active Scripting"
    Const L_IntroMsg4_Text              = "Cliquez sur le menu <B>Outils</B> dans Internet Explorer, cliquez sur <B>Options Internet</B>."
    Const L_IntroMsg5_Text              = "Cliquez sur l'onglet <B>S�curit�</B>."
    Const L_IntroMsg6_Text              = "Cliquez sur l'ic�ne <STRONG>Internet</STRONG>, puis cliquez sur <STRONG>Personnaliser le niveau</STRONG>."
    Const L_IntroMsg7_Text              = "Dans la section Script, sous <STRONG>Active Scripting</STRONG>, cliquez sur <STRONG>Activer</STRONG>."
    
	' **************************************
	' Links - No need for localization
	' **************************************
	Const L_AccLink_Text				= "http://www.microsoft.com/enable/"		
	Const L_XPLink_Text					= "http://www.microsoft.com/windowsxp/default.asp"
	Const L_PrivacyLink_Text			= "http://www.microsoft.com/info/privacy.htm"
	Const L_ContactUsLink_Text			= "http://register.microsoft.com/contactus30/contactus.asp?domain=windows&amp;lcid=1033&amp;cu=http://register.microsoft.com/contactus30/contactus.asp?domain=windows"
	Const L_MailTo1_Text				= "mailto:?subject=Lien de Microsoft&body=Ce lien �mane du site Web de Microsoft Windows XP"
	Const L_CopyRightLink_Text			= "http://www.microsoft.com/info/cpyright.htm"
	Const L_XPNewsletterLink_Text		= "http://www.microsoft.com/windowsxp/newsletters.asp"
	Const L_LinkToIE_Text				= "http://www.microsoft.com/windows/ie/default.htm"
	'*************************************	
	
	GetString = Eval(sStringName)
End Function

%>