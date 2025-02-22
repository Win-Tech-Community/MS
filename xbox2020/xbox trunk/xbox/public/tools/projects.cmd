@echo off
if not "%_echo%" == "" echo on
if not "%verbose%"=="" echo on

REM ---------------------------------------------------------------------------
REM   PROJECTS.CMD
REM
REM By adding your project to this file, anyone will be able to do "ntenlist
REM <your project name>" to automatically enlist in the correct location in
REM the tree. "project" is the name of the project. "slm_root" is the server
REM where it exists. "proj_path" is where the project lives in the source tree.
REM
REM Don't forget to update the graphical tree at the bottom of this file.
REM
REM Finally, you might also want to create an alias so users will be able to
REM jump right to your project w/o typing the full path. See
REM \nt\private\developr\ntcue.pub. The only caveat, don't use an alias that
REM is also the name of some utility.
REM
REM ---------------------------------------------------------------------------

set project=
set slm_root=
set proj_path=
goto %1 2>nul

:ntos
           set project=ntos&      set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\ntos
goto end
:private
           set project=private&   set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private
goto end
:public
           set project=public&    set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\public
goto end
:sdk
           set project=SDK&       set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\Private\SDK
goto end
:sdktools
           set project=sdktools&  set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\sdktools
goto end
:usb
           set project=usb&       set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\ntos\dd\wdm\usb
goto end
:test
           set project=test&      set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\test
goto end
:ui
           set project=ui&        set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\ui
goto end
:directx
           set project=directx&   set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\windows\directx
goto end
:win2000
           set project=win2000&   set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\win2000
goto end
:atg
           set project=atg&       set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\atg
goto end
:xdktest
           set project=xdktest&   set slm_root=\\CPITGCFS01\XBOX&       set proj_path=%_ntroot%\private\xdktest
goto end

쳐컴bldrules
쳐컴bldrules
쳐컴private
�   쳐컴amovie
�   �   읕컴filters.ks (ksuser)
�   쳐컴asn1
�   쳐컴atg
�   쳐컴basestor
�   쳐컴bpc
�   �   쳐컴bda
�   �   쳐컴bpccomm
�   �   쳐컴bpcui
�   �   쳐컴ca
�   �   쳐컴common
�   �   쳐컴ds
�   �   쳐컴epgldr
�   �   쳐컴filters
�   �   쳐컴quartz
�   �   쳐컴vbi
�   �   읕컴vidsvr
�   쳐컴ca
�   쳐컴cluster
�   쳐컴ddk
�   쳐컴dfs.ds
�   쳐컴ds
�   쳐컴dsmigrat
�   쳐컴dsui
�   쳐컴eventlog
�   쳐컴eventsystem
�   쳐컴fax
�   쳐컴imaging2
�   쳐컴inet
�   �   쳐컴athena
�   �   쳐컴controls
�   �   쳐컴digest
�   �   쳐컴icw
�   �   쳐컴iis
�   �   쳐컴iisrearc
�   �   쳐컴mshtml
�   �   쳐컴netmtng
�   �   쳐컴setup (iesetup)
�   �   쳐컴urlmon
�   �   쳐컴vml
�   �   쳐컴wininet
�   �   읕컴xml
�   쳐컴infosoft
�   쳐컴intlwb
�   쳐컴ispu
�   쳐컴mapistub
�   쳐컴mobile
�   쳐컴mvdm
�   쳐컴msagent
�   쳐컴net
�   �   쳐컴routing
�   �   쳐컴sfm
�   �   쳐컴sockets
�   �   읕컴ui
�   �       읕컴nwc
�   쳐컴nlgwb
�   쳐컴ntos
�   �   쳐컴arcinst
�   �   쳐컴dd
�   �   �   쳐컴sound
�   �   �   �   읕컴creative
�   �   �   읕컴wdm
�   �   �       쳐컴capture
�   �   �       �   읕컴atiwdm
�   �   �       쳐컴dvd
�   �   �       쳐컴input
�   �   �       쳐컴usb
�   �   �       읕컴1394
�   �   쳐컴ks
�   �   쳐컴miniport
�   �   �   쳐컴adaptec
�   �   �   쳐컴flashpnt
�   �   �   쳐컴slcd
�   �   �   읕컴symbios
�   �   쳐컴ndis
�   �   �   쳐컴netoem
�   �   �   쳐컴npfddi
�   �   �   읕컴testprot
�   �   쳐컴rdr2
�   �   �   읕컴mfiomi
�   �   쳐컴streams
�   �   쳐컴w32
�   �   �   쳐컴cslpk
�   �   �   쳐컴ntcon
�   �   �   쳐컴ntgdi
�   �   �   �   쳐컴mstypeo
�   �   �   �   읕컴printers
�   �   �   �       읕컴rasprint
�   �   �   �           읕컴mini
�   �   �   읕컴ntuser
�   �   읕컴wow64
�   쳐컴ntrk
�   쳐컴nw
�   쳐컴oleds
�   쳐컴ole2ui32
�   쳐컴ole32
�   쳐컴oleutest
�   쳐컴os2
�   쳐컴pnpu
�   쳐컴posix
�   쳐컴printer5
�   �   읕컴oemdrv
�   �       쳐컴broth
�   �       �   쳐컴hbp
�   �       쳐컴canon
�   �       쳐컴epson
�   �       쳐컴hp
�   �       �   쳐컴hpclj
�   �       �   쳐컴hplj5si
�   �       �   읕컴hpmini
�   �       쳐컴lexmk
�   �       읕컴xerox
�   �           읕컴nseries
�   쳐컴query
�   쳐컴redist
�   �   읕컴msagent
�   쳐컴remoteboot
�   쳐컴rpc
�   쳐컴samples
�   쳐컴sdktools
�   �   읕컴vctools
�   쳐컴security
�   쳐컴tapi
�   쳐컴unimodem
�   쳐컴utils
�   쳐컴win2000
�   쳐컴windbg64
�   쳐컴windows
�   �    쳐컴base
�   �    쳐컴cmd
�   �    쳐컴danim
�   �    쳐컴directx
�   �    쳐컴ep
�   �    쳐컴media
�   �    �   읕컴drivers
�   �    �       읕컴creatdll
�   �    쳐컴ole
�   �    쳐컴opengl
�   �    쳐컴reality
�   �    쳐컴sam
�   �    쳐컴setup
�   �    쳐컴shell
�   �    쳐컴spooler
�   �    �   읕컴monitors
�   �    �       읕컴hpmon
�   �    쳐컴tshoot
�   �    쳐컴tts
�   �    쳐컴win4help
�   �    쳐컴winnls
�   �    읕컴wmi
�   쳐컴wx86
�   읕컴xdktest
쳐컴public
�   읕컴spec
쳐컴test
쳐컴ui
읕컴nttest
    쳐컴basetest
    쳐컴basetool
    읕컴guitest
    
:end
