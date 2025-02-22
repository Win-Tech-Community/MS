////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Copyright 2000-2001 STMicroelectronics, Inc.  All Rights Reserved.         //
// HIGHLY CONFIDENTIAL INFORMATION:  This source code contains                //
// confidential and proprietary information of STMicroelectronics, Inc.       //
// This source code is provided to Microsoft Corporation under a written      //
// confidentiality agreement between STMicroelectronics and Microsoft.  This  //
// software may not be reproduced, distributed, modified, disclosed, used,    //
// displayed, stored in a retrieval system or transmitted in whole or in part,//
// in any form or by any means, electronic, mechanical, photocopying or       //
// otherwise, except as expressly authorized by STMicroelectronics. THE ONLY  //
// PERSONS WHO MAY HAVE ACCESS TO THIS SOFTWARE ARE THOSE PERSONS             //
// AUTHORIZED BY RAVISENT, WHO HAVE EXECUTED AND DELIVERED A                  //
// WRITTEN CONFIDENTIALITY AGREEMENT TO STMicroelectronics, IN THE FORM       //
// PRESCRIBED BY STMicroelectronics.                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
//
//  DVDDiskPlayerClass
//
//  Implements the player interface for DVDs
//
////////////////////////////////////////////////////////////////////

#ifndef DVDDISKPLAYER_H
#define DVDDISKPLAYER_H

#include "CDDiskPlayer.h"
#include "DVDDiskSeq.h"
#include "Config/DiskPlayerFactory.h"

#pragma warning(disable : 4250)

class DVDDiskPlayerClass : public CDDiskPlayerClass, protected DVDDiskSequencer, protected WinPort
	{
	protected:
		BOOL stillPhase;
		DVDFileSystem * dvdfs;

		virtual Error StartStillPhase(WORD delay);
		virtual Error CancelStillPhase(void);

		void Message(WPARAM wParam, LPARAM dParam);
		virtual Error InternalGetMode(DVDPlayerMode & mode);
		virtual Error IsPlayingForward(BOOL & forward);

		//
		//  Freezing stuff
		//

		class DVDFreezeState : public DDPFreezeState
			{
			public:
				DVDDSFreezeState dsFreezeState;
			};

		virtual Error DiskIsEncrypted(BOOL & enc);

		virtual Error GoTitle(WORD title, DWORD flags = DDPSPF_NONE);

		virtual Error GoPartOfTitle(WORD title, WORD part);

	public:
		DVDDiskPlayerClass(WinPortServer * server, UnitSet units, DVDDiskPlayerFactory * factory);

		~DVDDiskPlayerClass(void);

		virtual Error Init(WinPortServer * server, GenericProfile * profile, DVDDiskType diskType, DVDFileSystem * dvdfs, BYTE region);

		virtual Error GetMode(DVDPlayerMode & mode);

		virtual Error GetExtendedPlayerState(ExtendedPlayerState * eps);

		virtual Error StopStillPhase(void);

		virtual Error Exit(Error err = GNR_OK);

		virtual Error CallMenu(VTSMenuType menu);

		virtual Error PausePlayback(void);

		virtual Error ResumePlayback(void);

		virtual Error AdvanceFrame(void);

		virtual Error AdvanceFrameBy(int n);

		virtual Error SetPlaybackSpeed(WORD speed);

		virtual Error GetPlaybackSpeed(WORD & speed);

		virtual Error GetAudioStreamAttributes(WORD stream, DVDAudioStreamFormat	& attributes);

		virtual Error GetSubPictureStreamAttributes(WORD stream, DVDSubPictureStreamFormat	& attributes);

		virtual Error StartPresentation(DWORD flags);

		virtual Error GetCurrentLocation(DVDLocation & location);

		virtual Error GetCurrentDuration(DVDLocation & location);

		virtual Error GetTitleDuration(WORD title, DVDTime & duration);

		virtual Error MenuAvail(VTSMenuType menu, BOOL & avail);

		virtual Error GetUOPs(DWORD & uops);

		virtual Error UOPPermitted(int uops, BOOL & permitted);

		virtual Error GetTitleSearchUOPs(WORD title, DWORD & uops);

		virtual Error TitleSearchUOPPermitted(WORD title, int uops, BOOL & permitted);

		virtual Error NumberOfTitles(WORD & num);

		virtual Error NumberOfPartOfTitle(WORD title, WORD & num);

		virtual Error GetAvailStreams(BYTE & audio, DWORD & subPicture);

		virtual Error GetCurrentAudioStream(WORD & stream);

		virtual Error GetCurrentSubPictureStream(WORD & stream);

		virtual Error IsCurrentSubPictureEnabled(BOOL & enabled);

		virtual Error GetNumberOfAngles(WORD title, WORD & num);

		virtual Error GetCurrentAngle(WORD & angles);

		virtual Error ClearGPRMs(void);		// NOT virtual

		virtual Error TitlePlay(WORD title, DWORD flags = DDPSPF_NONE);

		virtual Error PTTPlay(WORD title, WORD part);

		virtual Error GoTrack(WORD track, WORD titleGroupNumber);

		virtual Error TimePlay(WORD title, DVDTime time);

		virtual Error GoUpProgramChain(void);

		virtual Error TimeSearch(DVDTime time);

		virtual Error PTTSearch(WORD part);

		virtual Error GoPrevProgram(void);

		virtual Error GoTopProgram(void);

		virtual Error GoNextProgram(void);

		virtual Error ExtendedPlay(DWORD flags, WORD title, WORD ptt, DVDTime time);

		virtual Error StartForwardScan(WORD speed);

		virtual Error StartBackwardScan(WORD speed);

		virtual Error GetScanSpeed(WORD & speed);

		virtual Error StopScan(void);

		virtual Error StartReversePlayback(void);

		virtual Error StartTrickplay(void);

		virtual Error ResumeFromSystemSpace(void);

		virtual Error ButtonUp(void);

		virtual Error ButtonDown(void);

		virtual Error ButtonLeft(void);

		virtual Error ButtonRight(void);

		virtual Error ButtonSelectAt(WORD x, WORD y);

		virtual Error ButtonActivate(void);

		virtual Error ButtonSelectAndActivate(WORD button);

		virtual Error ButtonSelectAtAndActivate(WORD x, WORD y);

		virtual Error IsButtonAt(WORD x, WORD y, BOOL & isButton);

		virtual Error HasPositionalButtons(BOOL & hasButtons);

		virtual Error MenuLanguageSelect(WORD language);

		virtual Error GetMenuLanguage(WORD & lang);

		virtual Error AudioStreamChange(WORD stream);

		virtual Error SubPictureStreamChange(WORD stream, BOOL enable);

		virtual Error AngleChange(WORD angle);

		virtual Error ParentalLevelSelect(WORD level);

		virtual Error ParentalCountrySelect(WORD country);

		virtual Error GetCurrentDisplayMode(DisplayPresentationMode & mode);

		virtual Error SetDisplayMode(DisplayPresentationMode mode);

		virtual Error GetCurrentVideoStandard(VideoStandard & standard);

		virtual Error SelectInitialLanguage(WORD audioLanguage, WORD audioExtension, WORD subPictureLanguage, WORD subPictureExtension);

		virtual Error TransferDiskKey(void);

		virtual Error GetCurrentBitrate(DWORD & bitrate);

		virtual Error GetCurrentButtonState(WORD & minButton, WORD & numButtons, WORD & currentButton);

		virtual Error Freeze (DDPFreezeState * state, DWORD & size);

		virtual Error Defrost(DDPFreezeState * state, DWORD & size, DWORD flags);

		virtual Error SetBreakpoint(WORD title, WORD ptt, DVDTime time, DWORD flags, DWORD & id);

		virtual Error ClearBreakpoint(DWORD id);

		virtual Error SetAudioStreamSelectionPreferences(DWORD flags);
	};

#pragma warning(default : 4250)

#endif
