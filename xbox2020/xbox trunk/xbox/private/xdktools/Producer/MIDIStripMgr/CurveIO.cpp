#include "stdafx.h"
#include "CurveIO.h"
#include "SeqSegmentRiff.h"
#include "MIDIFileIO.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Curve defines
#define CT_MAX		192		// Curve table maximum
#define CT_FACTOR	100		// Curve table multiplication factor
#define CT_DIVFACTOR	( ( CT_MAX ) * CT_FACTOR ) // Curve division factor


// Curve Table: LINEAR
static short ganCT_Linear[CT_MAX + 1] =
{
	0,100,200,300,400,500,600,700,
	800,900,1000,1100,1200,1300,1400,1500,
	1600,1700,1800,1900,2000,2100,2200,2300,
	2400,2500,2600,2700,2800,2900,3000,3100,
	3200,3300,3400,3500,3600,3700,3800,3900,
	4000,4100,4200,4300,4400,4500,4600,4700,
	4800,4900,5000,5100,5200,5300,5400,5500,
	5600,5700,5800,5900,6000,6100,6200,6300,
	6400,6500,6600,6700,6800,6900,7000,7100,
	7200,7300,7400,7500,7600,7700,7800,7900,
	8000,8100,8200,8300,8400,8500,8600,8700,
	8800,8900,9000,9100,9200,9300,9400,9500,
	9600,9700,9800,9900,10000,10100,10200,10300,
	10400,10500,10600,10700,10800,10900,11000,11100,
	11200,11300,11400,11500,11600,11700,11800,11900,
	12000,12100,12200,12300,12400,12500,12600,12700,
	12800,12900,13000,13100,13200,13300,13400,13500,
	13600,13700,13800,13900,14000,14100,14200,14300,
	14400,14500,14600,14700,14800,14900,15000,15100,
	15200,15300,15400,15500,15600,15700,15800,15900,
	16000,16100,16200,16300,16400,16500,16600,16700,
	16800,16900,17000,17100,17200,17300,17400,17500,
	17600,17700,17800,17900,18000,18100,18200,18300,
	18400,18500,18600,18700,18800,18900,19000,19100,19200
};


// Curve Table: SINE
static short ganCT_Sine[CT_MAX + 1] =
{
	0,1,5,11,20,32,46,62,
	82,103,128,155,184,216,250,287,
	327,369,413,460,509,561,615,671,
	730,792,855,921,990,1060,1133,1208,
	1286,1365,1447,1531,1617,1706,1796,1889,
	1983,2080,2179,2279,2382,2486,2593,2701,
	2811,2923,3037,3153,3270,3389,3509,3632,
	3755,3881,4008,4136,4266,4397,4530,4664,
	4799,4936,5074,5213,5354,5495,5638,5781,
	5926,6071,6218,6365,6514,6663,6813,6963,
	7115,7267,7420,7573,7727,7881,8036,8191,
	8346,8502,8659,8815,8972,9128,9285,9442,
	9600,9757,9914,10071,10227,10384,10540,10697,
	10853,11008,11163,11318,11472,11626,11779,11932,
	12084,12236,12386,12536,12685,12834,12981,13128,
	13273,13418,13561,13704,13845,13986,14125,14263,
	14399,14535,14669,14802,14933,15063,15191,15318,
	15444,15567,15690,15810,15929,16046,16162,16276,
	16388,16498,16606,16713,16817,16920,17020,17119,
	17216,17310,17403,17493,17582,17668,17752,17834,
	17913,17991,18066,18139,18209,18278,18344,18407,
	18469,18528,18584,18638,18690,18739,18786,18830,
	18872,18912,18949,18983,19015,19044,19071,19096,
	19117,19137,19153,19167,19179,19188,19194,19198,19200
};


// Curve Table: LOG
static short ganCT_Log[CT_MAX + 1] =
{
	0,381,747,1097,1432,1755,2066,2366,
	2655,2934,3205,3467,3721,3967,4207,4439,
	4666,4886,5101,5310,5515,5714,5909,6099,
	6285,6467,6645,6819,6990,7157,7321,7482,
	7640,7795,7947,8096,8243,8387,8529,8668,
	8805,8940,9073,9204,9332,9459,9584,9707,
	9828,9947,10065,10181,10295,10408,10520,10630,
	10738,10845,10951,11056,11159,11261,11361,11461,
	11559,11656,11752,11847,11941,12034,12126,12216,
	12306,12395,12483,12570,12656,12741,12826,12909,
	12992,13074,13155,13235,13315,13394,13472,13549,
	13626,13702,13777,13851,13925,13998,14071,14143,
	14214,14285,14355,14425,14494,14562,14630,14698,
	14764,14831,14896,14962,15026,15091,15154,15218,
	15280,15343,15405,15466,15527,15587,15647,15707,
	15766,15825,15883,15941,15999,16056,16113,16169,
	16225,16281,16336,16391,16446,16500,16554,16607,
	16661,16713,16766,16818,16870,16921,16973,17024,
	17074,17124,17174,17224,17273,17323,17371,17420,
	17468,17516,17564,17611,17658,17705,17752,17798,
	17844,17890,17936,17981,18026,18071,18116,18160,
	18204,18248,18292,18335,18379,18422,18464,18507,
	18549,18592,18634,18675,18717,18758,18799,18840,
	18881,18921,18962,19002,19042,19081,19121,19160,19200
};


// Curve Table: EXPONENTIAL
static short ganCT_Exp[CT_MAX + 1] =
{
	0,40,79,119,158,198,238,279,
	319,360,401,442,483,525,566,608,
	651,693,736,778,821,865,908,952,
	996,1040,1084,1129,1174,1219,1264,1310,
	1356,1402,1448,1495,1542,1589,1636,1684,
	1732,1780,1829,1877,1927,1976,2026,2076,
	2126,2176,2227,2279,2330,2382,2434,2487,
	2539,2593,2646,2700,2754,2809,2864,2919,
	2975,3031,3087,3144,3201,3259,3317,3375,
	3434,3493,3553,3613,3673,3734,3795,3857,
	3920,3982,4046,4109,4174,4238,4304,4369,
	4436,4502,4570,4638,4706,4775,4845,4915,
	4986,5057,5129,5202,5275,5349,5423,5498,
	5574,5651,5728,5806,5885,5965,6045,6126,
	6208,6291,6374,6459,6544,6630,6717,6805,
	6894,6984,7074,7166,7259,7353,7448,7544,
	7641,7739,7839,7939,8041,8144,8249,8355,
	8462,8570,8680,8792,8905,9019,9135,9253,
	9372,9493,9616,9741,9868,9996,10127,10260,
	10395,10532,10671,10813,10957,11104,11253,11405,
	11560,11718,11879,12043,12210,12381,12555,12733,
	12915,13101,13291,13486,13685,13890,14099,14314,
	14534,14761,14993,15233,15479,15733,15995,16266,
	16545,16834,17134,17445,17768,18103,18453,18819,19200
};

CCurveItem::CCurveItem()
{
	Clear();
}


CCurveItem::CCurveItem(const FullSeqEvent* pEvent)
{
	CopyFrom(pEvent);
}


/*
CCurveItem::CCurveItem(const CCurveItem *pCurveItem)
{
	Copy( pCurveItem );
}


void CCurveItem::CopyFrom(const DMUS_IO_SEQ_ITEM& item)
{
	Clear();

	// BUGBUG: Need to add reset values
	// If it really is a control change, import as a curve event
	if( (Status(item.bStatus) == MIDI_PBEND)
	||  (Status(item.bStatus) == MIDI_PTOUCH)
	||  (Status(item.bStatus) == MIDI_MTOUCH)
	||  (Status(item.bStatus) == MIDI_CCHANGE) )
	{
		m_mtTime = item.mtTime;
		m_nOffset = item.nOffset;
		m_bFlags = 0;

		m_bCurveShape = DMUS_CURVES_INSTANT;
		m_mtDuration = 1;

		switch( Status(item.bStatus) )
		{
			case MIDI_PBEND:
				m_bType = DMUS_CURVET_PBCURVE;
				m_bCCData = 0;
				m_nStartValue = (short)(((item.bByte2 & 0x7F) << 7) + (item.bByte1 & 0x7F));
				m_nEndValue = (short)(((item.bByte2 & 0x7F) << 7) + (item.bByte1 & 0x7F));
				break;
			case MIDI_PTOUCH:
				m_bType = DMUS_CURVET_PATCURVE;
				m_bCCData = item.bByte1;
				m_nStartValue = item.bByte2;
				m_nEndValue = item.bByte2;
				break;
			case MIDI_MTOUCH:
				m_bType = DMUS_CURVET_MATCURVE;
				m_bCCData = 0;
				m_nStartValue = item.bByte1;
				m_nEndValue = item.bByte1;
				break;
			default:
				m_bType = DMUS_CURVET_CCCURVE;
				m_bCCData = item.bByte1;
				m_nStartValue = item.bByte2;
				m_nEndValue = item.bByte2;
				break;
		}

		m_mtResetDuration = 0;
		m_nResetValue = 0;
	}
	else
	{
		ASSERT(FALSE);
	}
}
*/

void CCurveItem::CopyFrom(const FullSeqEvent* pEvent)
{
	Clear();

	// BUGBUG: Need to add reset values
	// If it really is a control change, import as a curve event
	if( (Status(pEvent->bStatus) == MIDI_PBEND)
	||  (Status(pEvent->bStatus) == MIDI_PTOUCH)
	||  (Status(pEvent->bStatus) == MIDI_MTOUCH)
	||  (Status(pEvent->bStatus) == MIDI_CCHANGE) )
	{
		m_mtTime = pEvent->mtTime;
		m_nOffset = pEvent->nOffset;
		m_bFlags = 0;

		m_bCurveShape = DMUS_CURVES_INSTANT;
		m_mtDuration = 1;

		switch( Status(pEvent->bStatus) )
		{
			case MIDI_PBEND:
				m_bType = DMUS_CURVET_PBCURVE;
				m_bCCData = 0;
				m_nStartValue = (short)(((pEvent->bByte2 & 0x7F) << 7) + (pEvent->bByte1 & 0x7F));
				m_nEndValue = (short)(((pEvent->bByte2 & 0x7F) << 7) + (pEvent->bByte1 & 0x7F));
				break;
			case MIDI_PTOUCH:
				m_bType = DMUS_CURVET_PATCURVE;
				m_bCCData = pEvent->bByte1;
				m_nStartValue = pEvent->bByte2;
				m_nEndValue = pEvent->bByte2;
				break;
			case MIDI_MTOUCH:
				m_bType = DMUS_CURVET_MATCURVE;
				m_bCCData = 0;
				m_nStartValue = pEvent->bByte1;
				m_nEndValue = pEvent->bByte1;
				break;
			default:
				m_bType = DMUS_CURVET_CCCURVE;
				m_bCCData = pEvent->bByte1;
				m_nStartValue = pEvent->bByte2;
				m_nEndValue = pEvent->bByte2;
				break;
		}

		m_mtResetDuration = 0;
		m_nResetValue = 0;
	}
	else
	{
		ASSERT(FALSE);
	}
}

/*
void CCurveItem::CopyFrom(const DMUS_IO_CURVE_ITEM& item)
{
	Clear();

	m_mtTime = item.mtStart;
	m_mtDuration = item.mtDuration;
	m_nOffset = item.nOffset;

	m_bFlags = item.bFlags;

	// curve specific data
	m_mtResetDuration = item.mtResetDuration;
	m_nStartValue = item.nStartValue;
	m_nEndValue = item.nEndValue;
	m_nResetValue = item.nResetValue;
	m_bType = item.bType;
	m_bCurveShape = item.bCurveShape;
	m_bCCData = item.bCCData;
}


bool CCurveItem::CopyTo(DMUS_IO_CURVE_ITEM& item)
{
	item.mtStart = m_mtTime;
	item.mtDuration = m_mtDuration;
	item.nOffset = m_nOffset;

	item.mtResetDuration = m_mtResetDuration;
	item.nStartValue = m_nStartValue;
	item.nEndValue = m_nEndValue;
	item.nResetValue = m_nResetValue;
	item.bType = m_bType;
	item.bCurveShape = m_bCurveShape;
	item.bCCData = m_bCCData;
	item.bFlags = m_bFlags;
	return true;
}
*/

void CCurveItem::Clear()
{
	CEventItem::Clear();

	m_mtResetDuration = 0;
	m_nStartValue = 0;
	m_nEndValue = 0;
	m_nResetValue = 0;
	m_bCurveShape = 0;
	m_bCCData = 0;
	m_bFlags = 0;
	m_bType = 0;
	m_wParamType = 0;
	m_wMergeIndex = 0;
	ZeroMemory( &m_rectFrame, sizeof( RECT ) );
	ZeroMemory( &m_rectSelect, sizeof( RECT ) );
	m_mtCurrent = 0;
}

/*
void CCurveItem::Copy( const CCurveItem* pCurveItem )
{
	ASSERT( pCurveItem != NULL );
	if ( pCurveItem == NULL )
	{
		return;
	}

	if( pCurveItem == this )
	{
		return;
	}

	Clear();

	CEventItem::Copy( pCurveItem );

	m_nResetValue = pCurveItem->m_nResetValue;
	m_nStartValue = pCurveItem->m_nStartValue;
	m_nEndValue = pCurveItem->m_nEndValue;
	m_nResetValue = pCurveItem->m_nResetValue;
	m_mtResetDuration = pCurveItem->m_mtResetDuration;
	m_bCurveShape = pCurveItem->m_bCurveShape;
	m_bCCData = pCurveItem->m_bCCData;

	m_dwBits = pCurveItem->m_dwBits;
	m_bFlags = pCurveItem->m_bFlags;
	m_bType = pCurveItem->m_bType;
}


/////////////////////////////////////////////////////////////////////////////
// CCurveItem::ComputeCurve

DWORD CCurveItem::ComputeCurve( void )
{
	DWORD dwRet;
	short *panTable;

	switch( m_bCurveShape )
	{
		case DMUS_CURVES_LINEAR:
			panTable = &ganCT_Linear[ 0 ];
			break;

		case DMUS_CURVES_EXP:
			panTable = &ganCT_Exp[ 0 ];
			break;

		case DMUS_CURVES_LOG:
			panTable = &ganCT_Log[ 0 ];
			break;

		case DMUS_CURVES_SINE:
			panTable = &ganCT_Sine[ 0 ];
			break;

		case DMUS_CURVES_INSTANT:
		default:
			dwRet = (DWORD)m_nEndValue;
			return dwRet;

	}

	// Compute index into table
	// There are CT_MAX + 1 elements in the table.
	short nIndex;

	if( (m_mtDuration == 0)
	|| 	(m_mtCurrent >= m_mtDuration) )
	{
		nIndex = CT_MAX;
	}
	else
	{
		double dblRes = (double)m_mtDuration / ( CT_MAX + 1 );
		nIndex = (short)( (double)m_mtCurrent / dblRes );
	}

	double dbl = ((double)panTable[nIndex] / CT_DIVFACTOR ) * (double)(m_nEndValue - m_nStartValue);
	dwRet = (DWORD)dbl + m_nStartValue;

//	TRACE( "ComputeCurve=%ld   %ld\n", dwRet, m_mtCurrent );
	return dwRet;
}


/////////////////////////////////////////////////////////////////////////////
// CCurveItem::SetDefaultResetValues

void CCurveItem::SetDefaultResetValues( MUSIC_TIME mtLength  )
{
	m_bFlags &= ~DMUS_CURVE_RESET;	
	m_nResetValue = 0;	
	m_mtResetDuration = 0;
	
	switch( m_bType )
	{
		case DMUS_CURVET_PBCURVE:
			m_bFlags |= DMUS_CURVE_RESET;	
			m_nResetValue = PB_DISP_OFFSET;	
			m_mtResetDuration = mtLength - AbsTime();
			break;
		
		case DMUS_CURVET_CCCURVE:
			switch( m_bCCData )
			{
				case 1:		// Mod Wheel
				case 2:		// Breath Controller
				case 4:		// Foot Controller
				case 5:		// Portamento Time
				case 12:	// FX1
				case 13:	// FX2
				case 64:	// Sustain Pedal
				case 65:	// Portamento On/Off
				case 66:	// Sostenuto Pedal
				case 67:	// Soft Pedal
				case 68:	// Legato Footswitch
				case 69:	// Hold 2
					m_bFlags |= DMUS_CURVE_RESET;	
					m_nResetValue = 0;	
					m_mtResetDuration = mtLength - AbsTime();
					break;
			}
			break;

		case DMUS_CURVET_PATCURVE:
		case DMUS_CURVET_MATCURVE:
			m_bFlags |= DMUS_CURVE_RESET;	
			m_nResetValue = 0;	
			m_mtResetDuration = mtLength - AbsTime();
			break;
	}
}
*/