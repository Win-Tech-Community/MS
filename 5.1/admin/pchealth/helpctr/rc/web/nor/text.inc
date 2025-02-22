<% @LANGUAGE="VBScript" @EnableSessionState="False"  %>
<% 'Option Explicit

Function GetString(ByVal sStringName)
	If InStr(sStringName, "L_") <> 1 Then sStringName = "L_" & sStringName & "_Text"

	'' Texts
	Const L_StartRemoteAssistance_Text  		= "Start Fjernhjelp"
	Const L_ProductName_Text			= "Fjernhjelp"
	Const L_Title1Paragraph1_Text		= "Yte hjelp med Fjernhjelp"
	Const L_Paragraph1_Text				= "Noen ganger er den beste m�ten � hjelpe noen med � l�se et problem � demonstrere l�sningen. Fjernhjelp er en sikker forbindelse du kan bruke til � lede en venn frem til l�sningen p� et dataproblem."
	Const L_Paragraph2_Text				= "Les merknadene nedenfor hvis dette er f�rste gang."
	Const L_StartRAMessage_Text			= "<font color=""#000000"" size=""2"">Klikk </font><b><font color=""#000000"" size=""2""><b>Start Fjernhjelp</b></font></b><font color=""#000000"" size=""2""> for � koble til din venns datamaskin</font>"
	Const L_StartRAButton_Text			= "Start Fjernhjelp"
	Const L_JScriptNotAvail1_Text		= "Gjeldende sikkerhetsinnstillinger for Internet Explorer er angitt for strengt til at du kan bruke Fjernhjelp. Hvis du vil bruke Fjernhjelp, m� du endre innstillingene eller angi omr�det som et klarert omr�de."
	Const L_IEHelp_Text					= "Se i Hjelp i Internet Explorer hvis du vil ha informasjon om hvordan du endrer sikkerhetsinnstillinger."
	Const L_TicketError1_Text			= "Fjernhjelp-invitasjonen mangler eller er ugyldig. Du trenger en gyldig invitasjon for � bruke Fjernhjelp."
	Const L_InstallIE_Text				= "Du m� installere Internet Explorer 5.5 for � kunne godta Fjernhjelp-invitasjoner."
	Const L_TicketErrorMsg_Text			= "Hvis du vil l�re mer om Fjernhjelp, klikker du <B>Start</B> i Windows XP, klikker <B>Hjelp og st�tte</B> og skriver <B>Fjernhjelp</B> inn i boksen <B>S�k</B>."
	
	Const L_NotesTitle_Text				= "Merknader"
	Const L_NotesLine1_Text				= "Godta bare invitasjoner fra personer du stoler p�."
	
	Const L_NotesLine2_Text				= "B�de du og personen du hjelper, m� v�re koblet til Internett n�r dere bruker Fjernhjelp. Hvis personen som sendte denne invitasjonen, er tilgjengelig for � godta en tilkoblingsforesp�rsel, vil du kunne se hans eller hennes dataskjerm, og prate med ham eller henne i sanntid."
	
	Const L_NotesLine6_Text				= "Dette er en sikker enveisforbindelse. Personen hvis datamaskin du kobler til, vil ikke p� noe tidspunkt kunne bruke sin datamaskin til � f� tilgang til din maskin. Hvis du arbeider p� et lokalnett, vil en brannmur kunne hindre deg i � bruke Fjernhjelp. Hvis dette er tilfellet, kontakter du systemansvarlig for � f� mer informasjon."
	
	Const L_LearnXP_Text				= "Hvis du vil l�re mer om Fjernhjelp, klikker du <B>Start</B> i Windows XP, klikker <B>Hjelp og st�tte</B> og skriver <B>Fjernhjelp</B> inn i boksen <B>S�k</B>."
	
	Const L_ContactUsMsg_Text			= "Kontakt oss"
	

	Const L_XPNewsletterMsg_Text		= "Gratis nyhetsbrev"
	Const L_EmailPage_Text				= "Send denne siden med e-post"
	
	Const L_CopyRightMsg_Text			= "(C) 2001 Microsoft Corporation. Med enerett. Vilk�r for bruk."
	
	Const L_PrivacyMsg_Text				= "Personvernerkl�ring"

	Const L_AccMsg_Text					= "Tilgjengelighet"

	Const L_NotIEError1_Text			= "Hvis du vil godta Fjernhjelp-invitasjoner, m� du installere Internet Explorer 5.5 eller senere."

	Const L_NotXPError1_Text			= "Microsoft Fjernhjelp er en funksjon i Windows&nbsp;XP. Du m� installere Windows&nbsp;XP for � kunne bruke Fjernhjelp."

	Const L_IELinkMsg_Text				= "Last ned den seneste versjonen av Internet Explorer"
	Const L_XPLinkMsg_Text				= "Hvis du vil l�re mer om Windows XP, g�r du til "
	Const L_XPLinkMsg2_Text				= "Web-omr�det for Microsoft Windows"
	Const L_XPLinkMsg3_Text				= "."
	
	Const L_IntroMsg1_Text              = "Laster ned en komponent som er n�dvendig for � bruke Fjernhjelp. Hvis du har et  28,8 kbps-modem kan nedlastingen ta et minutt."
    Const L_IntroMsg2_Text              = "Aktiv skripting m� v�re aktivert hvis Fjernhjelp skal kj�res. Hvis denne siden ikke bekrefter fullf�rt nedlasting etter at den beregnede nedlastingstiden er g�tt, kontrollerer du at skripting er aktivert."
    Const L_IntroMsg3_Text              = "Hvis du vil aktivere aktiv skripting"
    Const L_IntroMsg4_Text              = "Klikk <B>Alternativer for Internett</B> p� <B>Verkt�y</B>-menyen i Internet Explorer."
    Const L_IntroMsg5_Text              = "Klikk kategorien <B>Sikkerhet</B>."
    Const L_IntroMsg6_Text              = "Klikk <STRONG>Internett</STRONG>-ikonet, og klikk deretter <STRONG>Egendefinert niv�</STRONG>."
    Const L_IntroMsg7_Text              = "I seksjonen Skript g�r klikker du <STRONG>Aktiver</STRONG> under <STRONG>Aktiv skripting</STRONG>."
    
	' **************************************
	' Links - No need for localization
	' **************************************
	Const L_AccLink_Text				= "http://www.microsoft.com/enable/"		
	Const L_XPLink_Text					= "http://www.microsoft.com/windowsxp/default.asp"
	Const L_PrivacyLink_Text			= "http://www.microsoft.com/info/privacy.htm"
	Const L_ContactUsLink_Text			= "http://register.microsoft.com/contactus30/contactus.asp?domain=windows&amp;lcid=1033&amp;cu=http://register.microsoft.com/contactus30/contactus.asp?domain=windows"
	Const L_MailTo1_Text				= "mailto:?subject=En kobling fra Microsoft&body=Denne koblingen er fra Web-omr�det for Microsoft Windows XP"
	Const L_CopyRightLink_Text			= "http://www.microsoft.com/info/cpyright.htm"
	Const L_XPNewsletterLink_Text		= "http://www.microsoft.com/windowsxp/newsletters.asp"
	Const L_LinkToIE_Text				= "http://www.microsoft.com/windows/ie/default.htm"
	'*************************************	
	
	GetString = Eval(sStringName)
End Function

%>