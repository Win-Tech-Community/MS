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
#include "TEST_WAVETEST.H"
#include "WaveInterOp.h"

#define BITSPERSAMPLE  8

#define CHANNELS       2
#define SAMPLESPERSEC  44100
#define BLOCKALIGN     CHANNELS * BITSPERSAMPLE / 8
#define AVGBYTESPERSEC SAMPLESPERSEC * BLOCKALIGN
#define SIZE           0

TESTPROCAPI PlaybackInteroperability( UINT uMsg, TPPARAM tpParam, LPFUNCTION_TABLE_ENTRY lpFTE ){
    BEGINTESTPROC

    // Test purpose: Verify that playSound and sndPlaySound properly parse/play
    // valid wave file with optional embedded chunks.

    if( g_bSkipOut ) return TPR_SKIP;

        // check for capture device
	if( !waveInGetNumDevs() )
       {
        	LOG( TEXT("ERROR: waveInGetNumDevs reported zero devices, we need at least one.") );
        	return TPR_SKIP;
       }

    BOOL          bLastTest              = FALSE;
    BOOL          bRunTest               = FALSE;
    DWORD         dwMaxTestNum            = 10;
    DWORD         dwTestNum               = 1;
    char*         data                   = NULL;
    DWORD         dwBufferLength;
    DWORD         dwExpectedPlayTime     = 1000; // in milliseconds
    DWORD         dwNumberOfBytesWritten = 0;
    DWORD         dwReturn               = TPR_PASS;
    DWORD         dwUserResponse;
    LISTCK        lList                  = { LIST_FOURCC, 4, 0 };
    PCMWAVEFORMAT PcmWaveFormat =
    {
        { WAVE_FORMAT_PCM, CHANNELS, SAMPLESPERSEC, AVGBYTESPERSEC, BLOCKALIGN },
        BITSPERSAMPLE
    };

    LISTCK*    plList                   = &lList;
    TCHAR      pszDefaultFileName[]     = TEXT( "\\WaveInterOp.wav" );
    TCHAR*     pszFileName =
        g_bSave_WAV_file ? g_pszWAVFileName : pszDefaultFileName;

    WAVEFORMAT WaveFormat =
    {
        WAVE_FORMAT_PCM, CHANNELS, SAMPLESPERSEC, AVGBYTESPERSEC, BLOCKALIGN
        
    };
    WAVEFORMATEX  wfx =
    {
        WAVE_FORMAT_PCM,
        CHANNELS,
        SAMPLESPERSEC,
        AVGBYTESPERSEC,
        BLOCKALIGN,
        BITSPERSAMPLE,
        SIZE
    };
    WAVEHDR wh;

    // Set up an audio buffer for test.
    dwBufferLength = dwExpectedPlayTime * wfx.nAvgBytesPerSec / 1000;
    data = new char[ dwBufferLength ];
    if( !data )
    {
        LOG( TEXT( "ERROR:\tNew failed for data [%s:%u]" ), TEXT( __FILE__ ), __LINE__ );
        LOG( TEXT( "\tPossible Cause:  Out of Memory\n" ) );
        return TPR_ABORT;
    }

    ZeroMemory( data, dwBufferLength );
    ZeroMemory( &wh,sizeof( WAVEHDR ) );

    // Check for a buffer that is smaller than we expected. 
    if( dwExpectedPlayTime >= ( ULONG_MAX / wfx.nAvgBytesPerSec ) )
    {
        LOG( TEXT( "FAIL in %s @ line %u:" ), TEXT( __FILE__ ), __LINE__ );
        LOG( TEXT( "\tPotential overflow, dwExpectedPlayTime = %d ms."), dwExpectedPlayTime );
        delete[] data;
        data = NULL;
        return TPR_ABORT;
    } // if ExpectedPlayTime
    PREFAST_SUPPRESS(419, "The above line is checking for overflow. This seems to be prefast noise, since the path/trace Prefast lists is not possible. (Prefast team concurs so far.)");

    wh.lpData         = data;
    wh.dwBufferLength = dwBufferLength;
    wh.dwLoops        = 1;
    wh.dwFlags        = 0;
    if( !SineWave( wh.lpData, wh.dwBufferLength, &wfx ) )
    {
        LOG( TEXT(  "FAIL in %s @ line %u:\tSineWave returned a buffer of length zero." ), TEXT( __FILE__), __LINE__ );
        delete[] data;
        data = NULL;
        return TPR_ABORT;
    }
    
    while( !bLastTest )
    {
        bLastTest = TRUE;

        //  Generate a wave file.

        LogWaveFormat( PcmWaveFormat );

        CWaveFileEx cwfWaveInterOp(       pszFileName,
            GENERIC_READ | GENERIC_WRITE, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
            (LPVOID*)(&PcmWaveFormat),    (LPVOID*)(&plList)                 );

        if( cwfWaveInterOp.LastError() )
        {
            LOG( TEXT( "ERROR in %s @ line %u:" ), TEXT( __FILE__ ), __LINE__ );
            LOG( TEXT( "\tError %d detected after constructor." ),
            cwfWaveInterOp.LastError() );
            delete[] data;
            data = NULL;
            return TPR_ABORT;
        }

        // Add some optional chunks.
        cwfWaveInterOp.AddRandomChunk();
        cwfWaveInterOp.AddRandomChunk();

        if( !cwfWaveInterOp.WriteData( data, dwBufferLength, &dwNumberOfBytesWritten ) )
        {
            LOG(TEXT( "ERROR in %s @ line %u:" ), TEXT( __FILE__ ), __LINE__ );
            LOG( TEXT( "\tError %d detected after WriteData." ), cwfWaveInterOp.LastError() );
            delete[] data;
            data = NULL;
            return TPR_ABORT;
        }

        if( dwBufferLength != dwNumberOfBytesWritten )
        {
            LOG(TEXT( "ERROR in %s @ line %u:" ), TEXT( __FILE__ ), __LINE__ );
            LOG( TEXT( "\tUnexpected number of bytes written to WAV file." ) );
            delete[] data;
            data = NULL;
            return TPR_ABORT;
        }

        // Add more optional chunks.
        cwfWaveInterOp.AddRandomChunk();
        cwfWaveInterOp.AddRandomChunk();

        if( !cwfWaveInterOp.WriteData(data, dwBufferLength, &dwNumberOfBytesWritten ) )
        {
            LOG(TEXT( "ERROR in %s @ line %u:" ), TEXT( __FILE__ ), __LINE__ );
            LOG( TEXT( "\tError %d detected after second WriteData." ), cwfWaveInterOp.LastError() );
            delete[] data;
            data = NULL;
            return TPR_ABORT;
        }
          if( dwBufferLength != dwNumberOfBytesWritten )
        {
            LOG(TEXT( "ERROR in %s @ line %u:" ), TEXT( __FILE__ ), __LINE__ );
            LOG( TEXT( "\tUnexpected number of bytes written to WAV file." ) );
            delete[] data;
            data = NULL;
            return TPR_ABORT;
        }

        // Add some optional chunks at the end of the file.
        cwfWaveInterOp.AddRandomChunk();
        cwfWaveInterOp.AddRandomChunk();

        cwfWaveInterOp.Close();

        // Use PlaySound to test the audio file just created.
        bRunTest = FALSE;
        do
        {
            if( PlaySound(
                pszFileName, NULL, SND_FILENAME | SND_NODEFAULT | SND_SYNC ) )
            {
                LOG( TEXT( "PlaySound played." ) );
                if( g_interactive )
                {   // Let user, monitor sound quality.
                    dwUserResponse = GetUserEvaluation(TEXT (
                        "Did the audio file playback correctly, with acceptable quality and without audible glitches? Press YES or NO or press CANCEL if you wish to rerun this test."
                        ) );
                    if( TPR_RERUN_TEST == dwUserResponse ) 
                        bRunTest = TRUE;
                    else
                    {
                        dwReturn = GetReturnCode( dwReturn, dwUserResponse );
                        bRunTest = FALSE;
                    } // else !TPR_RERUN_TEST
                } // if g_interactive
            } // if PlaySound
            else // !PlaySound
            {
                LOG( TEXT( "ERROR:\tsndPlaySound failed.  Error %d returned." ),  cwfWaveInterOp.LastError() );
                dwReturn = TPR_FAIL;   
                bRunTest = FALSE;
            } // else !PlaySound
        } while( bRunTest );

        // Now use sndPlaySound to test the audio file.
        bRunTest = FALSE;
        do
        {
            if( sndPlaySound(
                pszFileName, SND_FILENAME | SND_NODEFAULT | SND_SYNC ) )        
            {
               LOG( TEXT( "sndPlaySound played." ) );
                if( g_interactive )
                {   // Let user, monitor sound quality.
                    dwUserResponse = GetUserEvaluation(TEXT (
                        "Did the audio file playback correctly, with acceptable quality and without audible glitches? Press YES or NO or press CANCEL if you wish to rerun this test."
                        ) );
                    if( TPR_RERUN_TEST == dwUserResponse ) 
                        bRunTest = TRUE;
                    else
                    {
                        dwReturn = GetReturnCode( dwReturn, dwUserResponse );
                        bRunTest = FALSE;
                    } // else !TPR_RERUN_TEST
                } // if g_interactive
            } // if sndPlaySound
            else // !sndPlaySound
            {
                LOG( TEXT( "ERROR:\tsndPlaySound failed.  Error %d returned." ), cwfWaveInterOp.LastError() );
                dwReturn = TPR_FAIL;   
                bRunTest = FALSE;
            } // else !sndPlaySound
        } while( bRunTest );

        if( FALSE == g_bSave_WAV_file )
        {
            if( DeleteFile( pszDefaultFileName ) )
            {
                LOG( TEXT( "Audio file deleted." ) );
                if( dwTestNum < dwMaxTestNum ) 
                {
                    bLastTest = FALSE;
                }
                dwTestNum++;
            }
            else // !DeleteFile
            {
                LOG( TEXT("ERROR in %s @ line %u:" ), TEXT( __FILE__ ), __LINE__ );
                LOG( TEXT( "\tUnable to delete audio file. Last error = %d." ),GetLastError() );
            } // !DeleteFile
        } // if !g_bSave_WAV_file

    } // while !bLastTest

    delete[] data;
    data = NULL;
    return dwReturn;
} // PlaybackInteroperability

