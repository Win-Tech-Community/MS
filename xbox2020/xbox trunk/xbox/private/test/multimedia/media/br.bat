@echo off
REM Builds and copies everything to XBox and runs it.
REM -------------------------------------------------------------------------
call b.bat %1
xbreboot xe:\MEDIA.XBE
