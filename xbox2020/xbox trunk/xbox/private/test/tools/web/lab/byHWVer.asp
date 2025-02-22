<%@ Language=JavaScript EnableSessionState=False%>
<!--**************************************************************************

Copyright (C) Microsoft Corporation.  All rights reserved.

The contents on this page are MICROSOFT CONFIDENTIAL

Module Name:

    byHWVer.asp

Abstract:

    Displays the current status of the lab machines

Arguments:

    none

Author:

    Josh Poley (jpoley)

**************************************************************************-->
<!--#include file ="include/lab.asp"-->
<%
    Response.AddHeader("Cache-Control", "no-cache");
    Response.AddHeader("Pragma", "no-cache");
    var row = 0;
    var html = "";
    var count = 0;
    var tip = "";

    var currentState = 0xFF;
    var currentBuild = "";
    var states = new Array;
    states[0] = "Crashed";
    states[1] = "Not Responding";
    states[2] = "Idle";
    states[3] = "Running";
    var blockNum = 0;

    // sql settings
    var SQLQuery;
    var where = "";
    var orderBy = "ORDER BY [Current HW Version] DESC, [Machine Name]";

    if(Request("where").Count >= 1) where = " WHERE " + Request("where");
    if(Request("order").Count >= 1) orderBy = " ORDER BY " + Request("order");

    SQLQuery = "SELECT * FROM BoxList "+where+" " + orderBy + ";";

    // connect & get records
    try {
        records.Open(SQLQuery, driver, 0, 1); // forward, read only
        }
    catch(e)
        {
        Response.Write("Error Communicating with the database<P>" + e.description + " (" + e.number +")");
        Response.End();
        }

    var TITLE = "<TABLE><TR><TD><IMG SRC='images/xtextbig.gif' HEIGHT=36></TD><TD> <SPAN STYLE='color:80C040;font:italic bold 30pt Arial'>By HW Ver</SPAN></TD></TABLE>";
%>
<HTML>
<HEAD>
    <TITLE>XBOX Lab</TITLE>
    <LINK REL="SHORTCUT ICON" HREF="xbox.ico">
    <LINK REL="stylesheet" TYPE="text/css" HREF="include/lab.css">
</HEAD>

<SCRIPT LANGUAGE="javascript" SRC="include/lab.js"></SCRIPT>
<BODY TOPMARGIN=0>

<!-- Begin Header Content -->
<!--#include file ="include/header.asp"-->
<!-- End Header Content -->

<%
while(!records.EOF)
    {
    count = 0;
    row = 0;
    currentState = parseInt(records("Current State"));
    if(!(currentState >=0 && currentState <=3))
        {
        records.MoveNext();
        continue;
        }

    ++blockNum;

    currentBuild = RTrim(records("Current HW Version"));

    Response.Write("\n\n\n\n<TABLE WIDTH=100% CELLPADDING=0 CELLSPACING=0 STYLE='border-top:1px solid #7CB021'><TD STYLE='cursor:hand' onClick='ExpandCollapse(BLOCK" + blockNum + ");'><H3>" + currentBuild + "</H3></TD><TD STYLE='text-align:right'></TD></TABLE>");
    %>

<BLOCKQUOTE ID=BLOCK<%=blockNum%>>
<TABLE CELLPADDING=3 CELLSPACING=0 BORDER=0 STYLE="table-layout:fixed">

<!-- Column header Row -->
<TR>
<TD WIDTH=15><IMG SRC="images\circle.gif"></TD>
<TH CLASS=ROWHEAD WIDTH=90>Machine</TH>
<TH CLASS=ROWHEAD WIDTH=100>Owner</TH>
<TH CLASS=ROWHEAD WIDTH=90>SW</TH>
<TH CLASS=ROWHEAD WIDTH=90>ROM</TH>
<TH CLASS=ROWHEAD WIDTH=95>Current State</TH>
<TH CLASS=ROWHEAD WIDTH=28>Info</TH>
<TD WIDTH=15 STYLE="margin-left:0;padding-left: 0; margin-right:0;padding-right: 0;"><IMG SRC="images\circle2.gif"></TD>
</TR>


<!-- Data Rows -->
<%
    while(!records.EOF)
        {
        currentState = parseInt(records("Current State"));
        if(!(currentState >=0 && currentState <=3))
            {
            records.MoveNext();
            continue;
            }

        if(RTrim(records("Current HW Version")) != currentBuild) break;

        tip = "<B>HW:</B> " + RTrim(records("Configuration Hardware")) + "<BR>";
        tip += "<B>VER:</B> " + RTrim(records("Current HW Version")) + "<BR>";
        if(currentState == 0)
            {
            tip += "<B>Stack:</B><BR>" + (""+records("Triage Notes")).replace(/\'|\"/g, "`").replace(/\r\n/g, "<BR>").replace(/\\/g, "/");
            }

        html = "<TR><TD></TD>";
        html += "<TD CLASS=ROW" + row + " onMouseOver='ToolTip(\""+tip+"\");' onMouseOut='ToolTip();'><A TITLE='Open Debugger' HREF=\"javascript:Run('%SystemRoot%/system32/cmd.exe /T:0A /K %_NTDRIVE%%_NTROOT%/public/tools/razzle.cmd REMOTE /C " + RTrim(records("Debugger")) + " " + RTrim(records("Machine Name")) + "')\">" + RTrim(records("Machine Name")) + "</A></TD>\n";
        html += "    <TD CLASS=ROW" + row + "><A HREF='mailto:" + RTrim(records("Owner")) + "'>"+RTrim(records("Owner"))+"</A></TD>\n";
        html += "    <TD CLASS=ROW" + row + ">" + RTrim(records("Current SW Version")) + "</TD>\n";
        html += "    <TD CLASS=ROW" + row + ">" + RTrim(records("Current ROM Version")) + "</TD>\n";
        html += "    <TD CLASS=ROW" + row + ">" + states[currentState] + "</TD>\n";
        html += "    <TD CLASS=ROW" + row + " ALIGN=CENTER><A HREF='editBox.asp?mac=" + RTrim(records("MAC Address")) + "'><IMG ALT='Edit / Details' SRC='images/edit.gif' BORDER=0></A></TD>\n";
        html += "    </TR>\n\n";

        Response.Write(html);
        records.MoveNext();
        row == 0 ? row = 1 : row = 0;
        ++count;
        }
%>
<TR>
<TD></TD>
<TD ALIGN=RIGHT><%=count%> Box<%=(count>1?"es":"&nbsp;&nbsp;")%></TD>
<TD COLSPAN=6></TD>
</TR>
</TABLE></BLOCKQUOTE>

<%  
    }

records.Close();
%>



<!-- Begin Footer Content -->
<!--#include file ="include/footer.asp"-->
<!-- End Footer Content -->
</BODY>
</HTML>
