#include "Test_Include.fx"

int Test_Count = 122;

string TestInfo
<
	string TestType = "PS";
>
= "ps_2_0_inst_crs";

PS_CRITERIA PS_001_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_001_Desc = "ps_2_0 : crs source reg combination t0, c0 is allowed";
string PS_001 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_002_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_002_Desc = "ps_2_0 : crs source reg combination v0, c0 is allowed";
string PS_002 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl v0 "
	"crs r0.r, v0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_003_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_003_Desc = "ps_2_0 : crs source reg combination c0, t0 is allowed";
string PS_003 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, c0, t0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_004_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_004_Desc = "ps_2_0 : crs source reg combination c0, v0 is allowed";
string PS_004 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl v0 "
	"crs r0.r, c0, v0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_005_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_005_Desc = "ps_2_0 : crs source reg combination -t0, -c0 is allowed";
string PS_005 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, -t0, -c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_006_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_006_Desc = "ps_2_0 : crs source reg combination -t0, c0 is allowed";
string PS_006 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, -t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_007_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_007_Desc = "ps_2_0 : crs source reg combination t0, -c0 is allowed";
string PS_007 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, -c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_008_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_008_Desc = "ps_2_0 : crs source reg combination t0, c0 is allowed";
string PS_008 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_009_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 9.109f };
string PS_009_Desc = "ps_2_0 : crs source reg combination t0, t0 is NOT allowed";
string PS_009 = 
	"ps_2_0 "
	"dcl t0 "
	"crs r0.r, t0, t0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_010_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_010_Desc = "ps_2_0 : crs source reg combination t0, t1 is NOT allowed";
string PS_010 = 
	"ps_2_0 "
	"dcl t0 "
	"dcl t1 "
	"crs r0.r, t0, t1 "
	"mov oC0, c0 ";

PS_CRITERIA PS_011_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_011_Desc = "ps_2_0 : crs source reg combination t0, v0 is NOT allowed";
string PS_011 = 
	"ps_2_0 "
	"dcl t0 "
	"dcl v0 "
	"crs r0.r, t0, v0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_012_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_012_Desc = "ps_2_0 : crs source reg combination v0, t0 is NOT allowed";
string PS_012 = 
	"ps_2_0 "
	"dcl v0 "
	"dcl t0 "
	"crs r0.r, v0, t0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_013_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_013_Desc = "ps_2_0 : crs source reg combination v0, v1 is NOT allowed";
string PS_013 = 
	"ps_2_0 "
	"dcl v0 "
	"dcl v1 "
	"crs r0.r, v0, v1 "
	"mov oC0, c0 ";

PS_CRITERIA PS_014_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_014_Desc = "ps_2_0 : crs source reg combination c0, c1 is NOT allowed";
string PS_014 = 
	"ps_2_0 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"crs r0.r, c0, c1 "
	"mov oC0, c0 ";

PS_CRITERIA PS_015_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_015_Desc = "ps_2_0 : crs source reg combination r0, r0 is NOT allowed";
string PS_015 = 
	"ps_2_0 "
	"mov r0, c0 "
	"crs r0.r, r0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_016_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_016_Desc = "ps_2_0 : crs source reg combination r0, b0 is NOT allowed";
string PS_016 = 
	"ps_2_0 "
	"defb b0, true "
	"mov r0, c0 "
	"crs r0.r, r0, b0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_017_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_017_Desc = "ps_2_0 : crs source reg combination r0, i0 is NOT allowed";
string PS_017 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"mov r0, c0 "
	"crs r0.r, r0, i0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_018_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_018_Desc = "ps_2_0 : crs source reg combination r0, p0 is NOT allowed";
string PS_018 = 
	"ps_2_0 "
	"mov r0, c0 "
	"crs r0.r, r0, p0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_019_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_019_Desc = "ps_2_0 : crs source reg combination r0, s0 is NOT allowed";
string PS_019 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"mov r0, c0 "
	"crs r0.r, r0, s0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_020_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_020_Desc = "ps_2_0 : crs source reg combination r0, oC0 is NOT allowed";
string PS_020 = 
	"ps_2_0 "
	"mov r0, c0 "
	"crs r0.r, r0, oC0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_021_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_021_Desc = "ps_2_0 : crs source reg combination r0, oDepth is NOT allowed";
string PS_021 = 
	"ps_2_0 "
	"mov r0, c0 "
	"crs r0.r, r0, oDepth "
	"mov oC0, c0 ";

PS_CRITERIA PS_022_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_022_Desc = "ps_2_0 : crs source reg combination b0, r0 is NOT allowed";
string PS_022 = 
	"ps_2_0 "
	"defb b0, true "
	"mov r0, c0 "
	"crs r0.r, b0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_023_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_023_Desc = "ps_2_0 : crs source reg combination b0, b0 is NOT allowed";
string PS_023 = 
	"ps_2_0 "
	"defb b0, true "
	"crs r0.r, b0, b0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_024_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_024_Desc = "ps_2_0 : crs source reg combination b0, i0 is NOT allowed";
string PS_024 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"crs r0.r, b0, i0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_025_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_025_Desc = "ps_2_0 : crs source reg combination b0, p0 is NOT allowed";
string PS_025 = 
	"ps_2_0 "
	"defb b0, true "
	"crs r0.r, b0, p0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_026_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_026_Desc = "ps_2_0 : crs source reg combination b0, s0 is NOT allowed";
string PS_026 = 
	"ps_2_0 "
	"defb b0, true "
	"dcl_2d s0 "
	"crs r0.r, b0, s0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_027_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_027_Desc = "ps_2_0 : crs source reg combination b0, oC0 is NOT allowed";
string PS_027 = 
	"ps_2_0 "
	"defb b0, true "
	"crs r0.r, b0, oC0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_028_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_028_Desc = "ps_2_0 : crs source reg combination b0, oDepth is NOT allowed";
string PS_028 = 
	"ps_2_0 "
	"defb b0, true "
	"crs r0.r, b0, oDepth "
	"mov oC0, c0 ";

PS_CRITERIA PS_029_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_029_Desc = "ps_2_0 : crs source reg combination i0, r0 is NOT allowed";
string PS_029 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"mov r0, c0 "
	"crs r0.r, i0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_030_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_030_Desc = "ps_2_0 : crs source reg combination i0, b0 is NOT allowed";
string PS_030 = 
	"ps_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"crs r0.r, i0, b0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_031_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_031_Desc = "ps_2_0 : crs source reg combination i0, i0 is NOT allowed";
string PS_031 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"crs r0.r, i0, i0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_032_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_032_Desc = "ps_2_0 : crs source reg combination i0, p0 is NOT allowed";
string PS_032 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"crs r0.r, i0, p0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_033_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_033_Desc = "ps_2_0 : crs source reg combination i0, s0 is NOT allowed";
string PS_033 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_2d s0 "
	"crs r0.r, i0, s0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_034_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_034_Desc = "ps_2_0 : crs source reg combination i0, oC0 is NOT allowed";
string PS_034 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"crs r0.r, i0, oC0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_035_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_035_Desc = "ps_2_0 : crs source reg combination i0, oDepth is NOT allowed";
string PS_035 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"crs r0.r, i0, oDepth "
	"mov oC0, c0 ";

PS_CRITERIA PS_036_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_036_Desc = "ps_2_0 : crs source reg combination p0, r0 is NOT allowed";
string PS_036 = 
	"ps_2_0 "
	"mov r0, c0 "
	"crs r0.r, p0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_037_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_037_Desc = "ps_2_0 : crs source reg combination p0, b0 is NOT allowed";
string PS_037 = 
	"ps_2_0 "
	"defb b0, true "
	"crs r0.r, p0, b0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_038_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_038_Desc = "ps_2_0 : crs source reg combination p0, i0 is NOT allowed";
string PS_038 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"crs r0.r, p0, i0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_039_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_039_Desc = "ps_2_0 : crs source reg combination p0, p0 is NOT allowed";
string PS_039 = 
	"ps_2_0 "
	"crs r0.r, p0, p0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_040_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_040_Desc = "ps_2_0 : crs source reg combination p0, s0 is NOT allowed";
string PS_040 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"crs r0.r, p0, s0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_041_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_041_Desc = "ps_2_0 : crs source reg combination p0, oC0 is NOT allowed";
string PS_041 = 
	"ps_2_0 "
	"crs r0.r, p0, oC0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_042_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_042_Desc = "ps_2_0 : crs source reg combination p0, oDepth is NOT allowed";
string PS_042 = 
	"ps_2_0 "
	"crs r0.r, p0, oDepth "
	"mov oC0, c0 ";

PS_CRITERIA PS_043_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_043_Desc = "ps_2_0 : crs source reg combination s0, r0 is NOT allowed";
string PS_043 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"mov r0, c0 "
	"crs r0.r, s0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_044_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_044_Desc = "ps_2_0 : crs source reg combination s0, b0 is NOT allowed";
string PS_044 = 
	"ps_2_0 "
	"defb b0, true "
	"dcl_2d s0 "
	"crs r0.r, s0, b0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_045_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_045_Desc = "ps_2_0 : crs source reg combination s0, i0 is NOT allowed";
string PS_045 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_2d s0 "
	"crs r0.r, s0, i0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_046_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_046_Desc = "ps_2_0 : crs source reg combination s0, p0 is NOT allowed";
string PS_046 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"crs r0.r, s0, p0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_047_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_047_Desc = "ps_2_0 : crs source reg combination s0, s0 is NOT allowed";
string PS_047 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"crs r0.r, s0, s0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_048_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_048_Desc = "ps_2_0 : crs source reg combination s0, oC0 is NOT allowed";
string PS_048 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"crs r0.r, s0, oC0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_049_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_049_Desc = "ps_2_0 : crs source reg combination s0, oDepth is NOT allowed";
string PS_049 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"crs r0.r, s0, oDepth "
	"mov oC0, c0 ";

PS_CRITERIA PS_050_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_050_Desc = "ps_2_0 : crs source reg combination oC0, r0 is NOT allowed";
string PS_050 = 
	"ps_2_0 "
	"mov r0, c0 "
	"crs r0.r, oC0, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_051_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_051_Desc = "ps_2_0 : crs source reg combination oC0, b0 is NOT allowed";
string PS_051 = 
	"ps_2_0 "
	"defb b0, true "
	"crs r0.r, oC0, b0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_052_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_052_Desc = "ps_2_0 : crs source reg combination oC0, i0 is NOT allowed";
string PS_052 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"crs r0.r, oC0, i0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_053_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_053_Desc = "ps_2_0 : crs source reg combination oC0, p0 is NOT allowed";
string PS_053 = 
	"ps_2_0 "
	"crs r0.r, oC0, p0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_054_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_054_Desc = "ps_2_0 : crs source reg combination oC0, s0 is NOT allowed";
string PS_054 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"crs r0.r, oC0, s0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_055_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_055_Desc = "ps_2_0 : crs source reg combination oC0, oC0 is NOT allowed";
string PS_055 = 
	"ps_2_0 "
	"crs r0.r, oC0, oC0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_056_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_056_Desc = "ps_2_0 : crs source reg combination oC0, oDepth is NOT allowed";
string PS_056 = 
	"ps_2_0 "
	"crs r0.r, oC0, oDepth "
	"mov oC0, c0 ";

PS_CRITERIA PS_057_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_057_Desc = "ps_2_0 : crs source reg combination oDepth, r0 is NOT allowed";
string PS_057 = 
	"ps_2_0 "
	"mov r0, c0 "
	"crs r0.r, oDepth, r0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_058_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_058_Desc = "ps_2_0 : crs source reg combination oDepth, b0 is NOT allowed";
string PS_058 = 
	"ps_2_0 "
	"defb b0, true "
	"crs r0.r, oDepth, b0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_059_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_059_Desc = "ps_2_0 : crs source reg combination oDepth, i0 is NOT allowed";
string PS_059 = 
	"ps_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"crs r0.r, oDepth, i0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_060_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_060_Desc = "ps_2_0 : crs source reg combination oDepth, p0 is NOT allowed";
string PS_060 = 
	"ps_2_0 "
	"crs r0.r, oDepth, p0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_061_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_061_Desc = "ps_2_0 : crs source reg combination oDepth, s0 is NOT allowed";
string PS_061 = 
	"ps_2_0 "
	"dcl_2d s0 "
	"crs r0.r, oDepth, s0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_062_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_062_Desc = "ps_2_0 : crs source reg combination oDepth, oC0 is NOT allowed";
string PS_062 = 
	"ps_2_0 "
	"crs r0.r, oDepth, oC0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_063_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_063_Desc = "ps_2_0 : crs source reg combination oDepth, oDepth is NOT allowed";
string PS_063 = 
	"ps_2_0 "
	"crs r0.r, oDepth, oDepth "
	"mov oC0, c0 ";

PS_CRITERIA PS_064_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_064_Desc = "ps_2_0 : crs source reg combination t0.r, c0 is NOT allowed";
string PS_064 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.r, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_065_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_065_Desc = "ps_2_0 : crs source reg combination t0.g, c0 is NOT allowed";
string PS_065 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.g, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_066_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_066_Desc = "ps_2_0 : crs source reg combination t0.b, c0 is NOT allowed";
string PS_066 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.b, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_067_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_067_Desc = "ps_2_0 : crs source reg combination t0.a, c0 is NOT allowed";
string PS_067 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.a, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_068_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_068_Desc = "ps_2_0 : crs source reg combination t0.gbra, c0 is NOT allowed";
string PS_068 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.gbra, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_069_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_069_Desc = "ps_2_0 : crs source reg combination t0.brga, c0 is NOT allowed";
string PS_069 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.brga, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_070_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_070_Desc = "ps_2_0 : crs source reg combination t0.abgr, c0 is NOT allowed";
string PS_070 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.abgr, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_071_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_071_Desc = "ps_2_0 : crs source reg combination t0.agrb, c0 is NOT allowed";
string PS_071 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.agrb, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_072_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_072_Desc = "ps_2_0 : crs source reg combination t0.rbga, c0 is NOT allowed";
string PS_072 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.rbga, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_073_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_073_Desc = "ps_2_0 : crs source reg combination t0.rgab, c0 is NOT allowed";
string PS_073 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.rgab, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_074_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_074_Desc = "ps_2_0 : crs source reg combination t0.bgr, c0 is NOT allowed";
string PS_074 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.bgr, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_075_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_075_Desc = "ps_2_0 : crs source reg combination t0.rbg, c0 is NOT allowed";
string PS_075 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.rbg, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_076_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_076_Desc = "ps_2_0 : crs source reg combination t0.gar, c0 is NOT allowed";
string PS_076 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.gar, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_077_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_077_Desc = "ps_2_0 : crs source reg combination t0.gr, c0 is NOT allowed";
string PS_077 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.gr, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_078_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_078_Desc = "ps_2_0 : crs source reg combination t0.ab, c0 is NOT allowed";
string PS_078 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.ab, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_079_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_079_Desc = "ps_2_0 : crs source reg combination t0.bg, c0 is NOT allowed";
string PS_079 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0.bg, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_080_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_080_Desc = "ps_2_0 : crs source reg combination t0, c0.r is NOT allowed";
string PS_080 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.r "
	"mov oC0, c0 ";

PS_CRITERIA PS_081_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_081_Desc = "ps_2_0 : crs source reg combination t0, c0.g is NOT allowed";
string PS_081 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.g "
	"mov oC0, c0 ";

PS_CRITERIA PS_082_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_082_Desc = "ps_2_0 : crs source reg combination t0, c0.b is NOT allowed";
string PS_082 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.b "
	"mov oC0, c0 ";

PS_CRITERIA PS_083_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_083_Desc = "ps_2_0 : crs source reg combination t0, c0.a is NOT allowed";
string PS_083 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.a "
	"mov oC0, c0 ";

PS_CRITERIA PS_084_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_084_Desc = "ps_2_0 : crs source reg combination t0, c0.gbra is NOT allowed";
string PS_084 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.gbra "
	"mov oC0, c0 ";

PS_CRITERIA PS_085_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_085_Desc = "ps_2_0 : crs source reg combination t0, c0.brga is NOT allowed";
string PS_085 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.brga "
	"mov oC0, c0 ";

PS_CRITERIA PS_086_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_086_Desc = "ps_2_0 : crs source reg combination t0, c0.abgr is NOT allowed";
string PS_086 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.abgr "
	"mov oC0, c0 ";

PS_CRITERIA PS_087_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_087_Desc = "ps_2_0 : crs source reg combination t0, c0.agrb is NOT allowed";
string PS_087 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.agrb "
	"mov oC0, c0 ";

PS_CRITERIA PS_088_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_088_Desc = "ps_2_0 : crs source reg combination t0, c0.rbga is NOT allowed";
string PS_088 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.rbga "
	"mov oC0, c0 ";

PS_CRITERIA PS_089_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_089_Desc = "ps_2_0 : crs source reg combination t0, c0.rgab is NOT allowed";
string PS_089 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.rgab "
	"mov oC0, c0 ";

PS_CRITERIA PS_090_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_090_Desc = "ps_2_0 : crs source reg combination t0, c0.bgr is NOT allowed";
string PS_090 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.bgr "
	"mov oC0, c0 ";

PS_CRITERIA PS_091_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_091_Desc = "ps_2_0 : crs source reg combination t0, c0.rbg is NOT allowed";
string PS_091 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.rbg "
	"mov oC0, c0 ";

PS_CRITERIA PS_092_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_092_Desc = "ps_2_0 : crs source reg combination t0, c0.gar is NOT allowed";
string PS_092 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.gar "
	"mov oC0, c0 ";

PS_CRITERIA PS_093_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_093_Desc = "ps_2_0 : crs source reg combination t0, c0.gr is NOT allowed";
string PS_093 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.gr "
	"mov oC0, c0 ";

PS_CRITERIA PS_094_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_094_Desc = "ps_2_0 : crs source reg combination t0, c0.ab is NOT allowed";
string PS_094 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.ab "
	"mov oC0, c0 ";

PS_CRITERIA PS_095_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_095_Desc = "ps_2_0 : crs source reg combination t0, c0.bg is NOT allowed";
string PS_095 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0.bg "
	"mov oC0, c0 ";

PS_CRITERIA PS_096_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_096_Desc = "ps_2_0 : crs write mask .r is allowed";
string PS_096 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.r, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_097_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_097_Desc = "ps_2_0 : crs write mask .g is allowed";
string PS_097 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.g, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_098_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_098_Desc = "ps_2_0 : crs write mask .b is allowed";
string PS_098 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.b, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_099_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_099_Desc = "ps_2_0 : crs write mask .rg is allowed";
string PS_099 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.rg, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_100_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_100_Desc = "ps_2_0 : crs write mask .gb is allowed";
string PS_100 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.gb, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_101_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_101_Desc = "ps_2_0 : crs write mask .rb is allowed";
string PS_101 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.rb, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_102_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_102_Desc = "ps_2_0 : crs write mask .rgb is allowed";
string PS_102 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.rgb, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_103_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_103_Desc = "ps_2_0 : crs write mask .a is NOT allowed";
string PS_103 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.a, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_104_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_104_Desc = "ps_2_0 : crs write mask .ba is NOT allowed";
string PS_104 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.ba, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_105_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_105_Desc = "ps_2_0 : crs write mask .ra is NOT allowed";
string PS_105 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.ra, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_106_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_106_Desc = "ps_2_0 : crs write mask .ga is NOT allowed";
string PS_106 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.ga, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_107_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_107_Desc = "ps_2_0 : crs write mask .gba is NOT allowed";
string PS_107 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.gba, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_108_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_108_Desc = "ps_2_0 : crs write mask .rba is NOT allowed";
string PS_108 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.rba, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_109_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_109_Desc = "ps_2_0 : crs write mask .rgba is NOT allowed";
string PS_109 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.rgba, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_110_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_110_Desc = "ps_2_0 : crs write mask .yx is NOT allowed";
string PS_110 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.yx, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_111_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_111_Desc = "ps_2_0 : crs write mask .zx is NOT allowed";
string PS_111 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.zx, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_112_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_112_Desc = "ps_2_0 : crs write mask .zy is NOT allowed";
string PS_112 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.zy, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_113_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_113_Desc = "ps_2_0 : crs write mask .wx is NOT allowed";
string PS_113 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.wx, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_114_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_114_Desc = "ps_2_0 : crs write mask .wz is NOT allowed";
string PS_114 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.wz, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_115_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_115_Desc = "ps_2_0 : crs write mask .wy is NOT allowed";
string PS_115 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.wy, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_116_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_116_Desc = "ps_2_0 : crs write mask .zyx is NOT allowed";
string PS_116 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.zyx, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_117_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_117_Desc = "ps_2_0 : crs write mask .wzy is NOT allowed";
string PS_117 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.wzy, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_118_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_118_Desc = "ps_2_0 : crs write mask .wzx is NOT allowed";
string PS_118 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.wzx, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_119_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_119_Desc = "ps_2_0 : crs write mask .wyx is NOT allowed";
string PS_119 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.wyx, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_120_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_120_Desc = "ps_2_0 : crs write mask .yxw is NOT allowed";
string PS_120 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.yxw, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_121_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_121_Desc = "ps_2_0 : crs write mask .wzyx is NOT allowed";
string PS_121 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.wzyx, t0, c0 "
	"mov oC0, c0 ";

PS_CRITERIA PS_122_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string PS_122_Desc = "ps_2_0 : crs write mask .zxwy is NOT allowed";
string PS_122 = 
	"ps_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl t0 "
	"crs r0.zxwy, t0, c0 "
	"mov oC0, c0 ";


