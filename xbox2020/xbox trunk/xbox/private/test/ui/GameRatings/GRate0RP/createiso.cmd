@echo off
SET __TITLEID=00000010
SET __XBENAME=GRate0RP

@rmdir /s /q iso >nul
mkdir iso
mkdir iso\%__TITLEID%
xcopy %_NTBINDIR%\private\test\ui\GameRatings\%__XBENAME%\tdata\*.* iso\%__TITLEID% /S /E /I /H /Y
copy %_NT386TREE%\dump\%__XBENAME%.xbe iso\default.xbe
gdfimage iso .\%__XBENAME%.iso
rmdir /s /q iso
goto end

:end
SET __TITLEID=
SET __XBENAME=
