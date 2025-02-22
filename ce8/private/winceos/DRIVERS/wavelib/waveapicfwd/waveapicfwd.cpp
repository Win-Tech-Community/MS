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
#define FORWARD(fn) extern "C" void fn(){}

FORWARD(AudioUpdateFromRegistry)
FORWARD(sndPlaySoundW)
FORWARD(PlaySoundW)

FORWARD(waveOutGetNumDevs)
FORWARD(waveOutGetDevCaps)
FORWARD(waveOutGetVolume)
FORWARD(waveOutSetVolume)
FORWARD(waveOutGetErrorText)
FORWARD(waveOutClose)
FORWARD(waveOutPrepareHeader)
FORWARD(waveOutUnprepareHeader)
FORWARD(waveOutWrite)
FORWARD(waveOutPause)
FORWARD(waveOutRestart)
FORWARD(waveOutReset)
FORWARD(waveOutBreakLoop)
FORWARD(waveOutGetPosition)
FORWARD(waveOutGetPitch)
FORWARD(waveOutSetPitch)
FORWARD(waveOutGetPlaybackRate)
FORWARD(waveOutSetPlaybackRate)
FORWARD(waveOutGetProperty)
FORWARD(waveOutSetProperty)
FORWARD(waveOutGetID)
FORWARD(waveOutMessage)
FORWARD(waveOutOpen)
FORWARD(waveInGetNumDevs)
FORWARD(waveInGetDevCaps)
FORWARD(waveInGetErrorText)
FORWARD(waveInClose)
FORWARD(waveInPrepareHeader)
FORWARD(waveInUnprepareHeader)
FORWARD(waveInAddBuffer)
FORWARD(waveInStart)
FORWARD(waveInStop)
FORWARD(waveInReset)
FORWARD(waveInGetPosition)
FORWARD(waveInGetID)
FORWARD(waveInMessage)
FORWARD(waveInOpen)
FORWARD(waveInGetProperty)
FORWARD(waveInSetProperty)

FORWARD(mixerGetControlDetails)
FORWARD(mixerGetDevCaps)
FORWARD(mixerGetID)
FORWARD(mixerGetLineControls)
FORWARD(mixerGetLineInfo)
FORWARD(mixerGetNumDevs)
FORWARD(mixerMessage)
FORWARD(mixerOpen)
FORWARD(mixerSetControlDetails)
FORWARD(mixerClose)

