#include "Test_Include.fx"

int Test_Count = 199;

string TestInfo
<
	string TestType = "PS";
>
= "ps_1_4_inst_mad";

PS_CRITERIA PS_001_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_001_Desc = "ps_1_4 : mad source reg combination v0, v1, r0 is allowed";
string PS_001 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0, v0, v1, r0 ";

PS_CRITERIA PS_002_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_002_Desc = "ps_1_4 : mad source reg combination v0, v1, c0 is allowed";
string PS_002 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mad r0, v0, v1, c0 "
	"mov r0, c0 ";

PS_CRITERIA PS_003_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_003_Desc = "ps_1_4 : mad source reg combination v0, r0, v1 is allowed";
string PS_003 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0, v0, r0, v1 ";

PS_CRITERIA PS_004_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_004_Desc = "ps_1_4 : mad source reg combination v0, r0, r1 is allowed";
string PS_004 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, v0, r0, r1 ";

PS_CRITERIA PS_005_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_005_Desc = "ps_1_4 : mad source reg combination v0, r0, c0 is allowed";
string PS_005 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, v0, r0, c0 ";

PS_CRITERIA PS_006_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_006_Desc = "ps_1_4 : mad source reg combination v0, c0, v1 is allowed";
string PS_006 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mad r0, v0, c0, v1 "
	"mov r0, c0 ";

PS_CRITERIA PS_007_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_007_Desc = "ps_1_4 : mad source reg combination v0, c0, r0 is allowed";
string PS_007 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, v0, c0, r0 ";

PS_CRITERIA PS_008_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_008_Desc = "ps_1_4 : mad source reg combination v0, c0, c1 is allowed";
string PS_008 = 
	"ps_1_4 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"mad r0, v0, c0, c1 "
	"mov r0, c0 ";

PS_CRITERIA PS_009_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_009_Desc = "ps_1_4 : mad source reg combination r0, v0, v1 is allowed";
string PS_009 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0, r0, v0, v1 ";

PS_CRITERIA PS_010_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_010_Desc = "ps_1_4 : mad source reg combination r0, v0, r1 is allowed";
string PS_010 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, v0, r1 ";

PS_CRITERIA PS_011_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_011_Desc = "ps_1_4 : mad source reg combination r0, v0, c0 is allowed";
string PS_011 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, r0, v0, c0 ";

PS_CRITERIA PS_012_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_012_Desc = "ps_1_4 : mad source reg combination r0, r1, v0 is allowed";
string PS_012 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, r1, v0 ";

PS_CRITERIA PS_013_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_013_Desc = "ps_1_4 : mad source reg combination r0, r1, r2 is allowed";
string PS_013 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mov r2, c0 "
	"mad r0, r0, r1, r2 ";

PS_CRITERIA PS_014_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_014_Desc = "ps_1_4 : mad source reg combination r0, r1, c0 is allowed";
string PS_014 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, r1, c0 ";

PS_CRITERIA PS_015_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_015_Desc = "ps_1_4 : mad source reg combination r0, c0, v0 is allowed";
string PS_015 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, r0, c0, v0 ";

PS_CRITERIA PS_016_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_016_Desc = "ps_1_4 : mad source reg combination r0, c0, r1 is allowed";
string PS_016 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1 ";

PS_CRITERIA PS_017_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_017_Desc = "ps_1_4 : mad source reg combination r0, c0, c1 is allowed";
string PS_017 = 
	"ps_1_4 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, r0, c0, c1 ";

PS_CRITERIA PS_018_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_018_Desc = "ps_1_4 : mad source reg combination c0, v0, v1 is allowed";
string PS_018 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mad r0, c0, v0, v1 "
	"mov r0, c0 ";

PS_CRITERIA PS_019_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_019_Desc = "ps_1_4 : mad source reg combination c0, v0, r0 is allowed";
string PS_019 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, c0, v0, r0 ";

PS_CRITERIA PS_020_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_020_Desc = "ps_1_4 : mad source reg combination c0, v0, c1 is allowed";
string PS_020 = 
	"ps_1_4 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"mad r0, c0, v0, c1 "
	"mov r0, c0 ";

PS_CRITERIA PS_021_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_021_Desc = "ps_1_4 : mad source reg combination c0, r0, v0 is allowed";
string PS_021 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, c0, r0, v0 ";

PS_CRITERIA PS_022_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_022_Desc = "ps_1_4 : mad source reg combination c0, r0, r1 is allowed";
string PS_022 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, c0, r0, r1 ";

PS_CRITERIA PS_023_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_023_Desc = "ps_1_4 : mad source reg combination c0, r0, c1 is allowed";
string PS_023 = 
	"ps_1_4 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, c0, r0, c1 ";

PS_CRITERIA PS_024_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_024_Desc = "ps_1_4 : mad source reg combination c0, c1, v0 is allowed";
string PS_024 = 
	"ps_1_4 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"mad r0, c0, c1, v0 "
	"mov r0, c0 ";

PS_CRITERIA PS_025_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_025_Desc = "ps_1_4 : mad source reg combination c0, c1, r0 is allowed";
string PS_025 = 
	"ps_1_4 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mad r0, c0, c1, r0 ";

PS_CRITERIA PS_026_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_026_Desc = "ps_1_4 : mad source reg combination r0_bias, c0, r1_bias is allowed";
string PS_026 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bias, c0, r1_bias ";

PS_CRITERIA PS_027_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_027_Desc = "ps_1_4 : mad source reg combination r0_bias, c0, 1 - r1 is allowed";
string PS_027 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bias, c0, 1 - r1 ";

PS_CRITERIA PS_028_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_028_Desc = "ps_1_4 : mad source reg combination r0_bias, c0, -r1 is allowed";
string PS_028 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bias, c0, -r1 ";

PS_CRITERIA PS_029_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_029_Desc = "ps_1_4 : mad source reg combination r0_bias, c0, r1_x2 is allowed";
string PS_029 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bias, c0, r1_x2 ";

PS_CRITERIA PS_030_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_030_Desc = "ps_1_4 : mad source reg combination r0_bias, c0, r1_bx2 is allowed";
string PS_030 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bias, c0, r1_bx2 ";

PS_CRITERIA PS_031_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_031_Desc = "ps_1_4 : mad source reg combination r0_bias, c0, -r1_x2 is allowed";
string PS_031 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bias, c0, -r1_x2 ";

PS_CRITERIA PS_032_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_032_Desc = "ps_1_4 : mad source reg combination r0_bias, c0, -r1_bx2 is allowed";
string PS_032 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bias, c0, -r1_bx2 ";

PS_CRITERIA PS_033_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_033_Desc = "ps_1_4 : mad source reg combination r0_bias, c0, r1 is allowed";
string PS_033 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bias, c0, r1 ";

PS_CRITERIA PS_034_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_034_Desc = "ps_1_4 : mad source reg combination 1 - r0, c0, r1_bias is allowed";
string PS_034 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, 1 - r0, c0, r1_bias ";

PS_CRITERIA PS_035_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_035_Desc = "ps_1_4 : mad source reg combination 1 - r0, c0, 1 - r1 is allowed";
string PS_035 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, 1 - r0, c0, 1 - r1 ";

PS_CRITERIA PS_036_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_036_Desc = "ps_1_4 : mad source reg combination 1 - r0, c0, -r1 is allowed";
string PS_036 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, 1 - r0, c0, -r1 ";

PS_CRITERIA PS_037_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_037_Desc = "ps_1_4 : mad source reg combination 1 - r0, c0, r1_x2 is allowed";
string PS_037 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, 1 - r0, c0, r1_x2 ";

PS_CRITERIA PS_038_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_038_Desc = "ps_1_4 : mad source reg combination 1 - r0, c0, r1_bx2 is allowed";
string PS_038 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, 1 - r0, c0, r1_bx2 ";

PS_CRITERIA PS_039_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_039_Desc = "ps_1_4 : mad source reg combination 1 - r0, c0, -r1_x2 is allowed";
string PS_039 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, 1 - r0, c0, -r1_x2 ";

PS_CRITERIA PS_040_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_040_Desc = "ps_1_4 : mad source reg combination 1 - r0, c0, -r1_bx2 is allowed";
string PS_040 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, 1 - r0, c0, -r1_bx2 ";

PS_CRITERIA PS_041_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_041_Desc = "ps_1_4 : mad source reg combination 1 - r0, c0, r1 is allowed";
string PS_041 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, 1 - r0, c0, r1 ";

PS_CRITERIA PS_042_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_042_Desc = "ps_1_4 : mad source reg combination -r0, c0, r1_bias is allowed";
string PS_042 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0, c0, r1_bias ";

PS_CRITERIA PS_043_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_043_Desc = "ps_1_4 : mad source reg combination -r0, c0, 1 - r1 is allowed";
string PS_043 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0, c0, 1 - r1 ";

PS_CRITERIA PS_044_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_044_Desc = "ps_1_4 : mad source reg combination -r0, c0, -r1 is allowed";
string PS_044 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0, c0, -r1 ";

PS_CRITERIA PS_045_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_045_Desc = "ps_1_4 : mad source reg combination -r0, c0, r1_x2 is allowed";
string PS_045 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0, c0, r1_x2 ";

PS_CRITERIA PS_046_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_046_Desc = "ps_1_4 : mad source reg combination -r0, c0, r1_bx2 is allowed";
string PS_046 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0, c0, r1_bx2 ";

PS_CRITERIA PS_047_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_047_Desc = "ps_1_4 : mad source reg combination -r0, c0, -r1_x2 is allowed";
string PS_047 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0, c0, -r1_x2 ";

PS_CRITERIA PS_048_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_048_Desc = "ps_1_4 : mad source reg combination -r0, c0, -r1_bx2 is allowed";
string PS_048 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0, c0, -r1_bx2 ";

PS_CRITERIA PS_049_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_049_Desc = "ps_1_4 : mad source reg combination -r0, c0, r1 is allowed";
string PS_049 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0, c0, r1 ";

PS_CRITERIA PS_050_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_050_Desc = "ps_1_4 : mad source reg combination r0_x2, c0, r1_bias is allowed";
string PS_050 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_x2, c0, r1_bias ";

PS_CRITERIA PS_051_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_051_Desc = "ps_1_4 : mad source reg combination r0_x2, c0, 1 - r1 is allowed";
string PS_051 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_x2, c0, 1 - r1 ";

PS_CRITERIA PS_052_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_052_Desc = "ps_1_4 : mad source reg combination r0_x2, c0, -r1 is allowed";
string PS_052 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_x2, c0, -r1 ";

PS_CRITERIA PS_053_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_053_Desc = "ps_1_4 : mad source reg combination r0_x2, c0, r1_x2 is allowed";
string PS_053 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_x2, c0, r1_x2 ";

PS_CRITERIA PS_054_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_054_Desc = "ps_1_4 : mad source reg combination r0_x2, c0, r1_bx2 is allowed";
string PS_054 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_x2, c0, r1_bx2 ";

PS_CRITERIA PS_055_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_055_Desc = "ps_1_4 : mad source reg combination r0_x2, c0, -r1_x2 is allowed";
string PS_055 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_x2, c0, -r1_x2 ";

PS_CRITERIA PS_056_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_056_Desc = "ps_1_4 : mad source reg combination r0_x2, c0, -r1_bx2 is allowed";
string PS_056 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_x2, c0, -r1_bx2 ";

PS_CRITERIA PS_057_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_057_Desc = "ps_1_4 : mad source reg combination r0_x2, c0, r1 is allowed";
string PS_057 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_x2, c0, r1 ";

PS_CRITERIA PS_058_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_058_Desc = "ps_1_4 : mad source reg combination r0_bx2, c0, r1_bias is allowed";
string PS_058 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bx2, c0, r1_bias ";

PS_CRITERIA PS_059_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_059_Desc = "ps_1_4 : mad source reg combination r0_bx2, c0, 1 - r1 is allowed";
string PS_059 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bx2, c0, 1 - r1 ";

PS_CRITERIA PS_060_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_060_Desc = "ps_1_4 : mad source reg combination r0_bx2, c0, -r1 is allowed";
string PS_060 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bx2, c0, -r1 ";

PS_CRITERIA PS_061_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_061_Desc = "ps_1_4 : mad source reg combination r0_bx2, c0, r1_x2 is allowed";
string PS_061 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bx2, c0, r1_x2 ";

PS_CRITERIA PS_062_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_062_Desc = "ps_1_4 : mad source reg combination r0_bx2, c0, r1_bx2 is allowed";
string PS_062 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bx2, c0, r1_bx2 ";

PS_CRITERIA PS_063_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_063_Desc = "ps_1_4 : mad source reg combination r0_bx2, c0, -r1_x2 is allowed";
string PS_063 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bx2, c0, -r1_x2 ";

PS_CRITERIA PS_064_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_064_Desc = "ps_1_4 : mad source reg combination r0_bx2, c0, -r1_bx2 is allowed";
string PS_064 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bx2, c0, -r1_bx2 ";

PS_CRITERIA PS_065_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_065_Desc = "ps_1_4 : mad source reg combination r0_bx2, c0, r1 is allowed";
string PS_065 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0_bx2, c0, r1 ";

PS_CRITERIA PS_066_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_066_Desc = "ps_1_4 : mad source reg combination -r0_x2, c0, r1_bias is allowed";
string PS_066 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_x2, c0, r1_bias ";

PS_CRITERIA PS_067_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_067_Desc = "ps_1_4 : mad source reg combination -r0_x2, c0, 1 - r1 is allowed";
string PS_067 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_x2, c0, 1 - r1 ";

PS_CRITERIA PS_068_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_068_Desc = "ps_1_4 : mad source reg combination -r0_x2, c0, -r1 is allowed";
string PS_068 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_x2, c0, -r1 ";

PS_CRITERIA PS_069_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_069_Desc = "ps_1_4 : mad source reg combination -r0_x2, c0, r1_x2 is allowed";
string PS_069 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_x2, c0, r1_x2 ";

PS_CRITERIA PS_070_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_070_Desc = "ps_1_4 : mad source reg combination -r0_x2, c0, r1_bx2 is allowed";
string PS_070 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_x2, c0, r1_bx2 ";

PS_CRITERIA PS_071_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_071_Desc = "ps_1_4 : mad source reg combination -r0_x2, c0, -r1_x2 is allowed";
string PS_071 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_x2, c0, -r1_x2 ";

PS_CRITERIA PS_072_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_072_Desc = "ps_1_4 : mad source reg combination -r0_x2, c0, -r1_bx2 is allowed";
string PS_072 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_x2, c0, -r1_bx2 ";

PS_CRITERIA PS_073_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_073_Desc = "ps_1_4 : mad source reg combination -r0_x2, c0, r1 is allowed";
string PS_073 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_x2, c0, r1 ";

PS_CRITERIA PS_074_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_074_Desc = "ps_1_4 : mad source reg combination -r0_bx2, c0, r1_bias is allowed";
string PS_074 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_bx2, c0, r1_bias ";

PS_CRITERIA PS_075_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_075_Desc = "ps_1_4 : mad source reg combination -r0_bx2, c0, 1 - r1 is allowed";
string PS_075 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_bx2, c0, 1 - r1 ";

PS_CRITERIA PS_076_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_076_Desc = "ps_1_4 : mad source reg combination -r0_bx2, c0, -r1 is allowed";
string PS_076 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_bx2, c0, -r1 ";

PS_CRITERIA PS_077_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_077_Desc = "ps_1_4 : mad source reg combination -r0_bx2, c0, r1_x2 is allowed";
string PS_077 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_bx2, c0, r1_x2 ";

PS_CRITERIA PS_078_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_078_Desc = "ps_1_4 : mad source reg combination -r0_bx2, c0, r1_bx2 is allowed";
string PS_078 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_bx2, c0, r1_bx2 ";

PS_CRITERIA PS_079_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_079_Desc = "ps_1_4 : mad source reg combination -r0_bx2, c0, -r1_x2 is allowed";
string PS_079 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_bx2, c0, -r1_x2 ";

PS_CRITERIA PS_080_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_080_Desc = "ps_1_4 : mad source reg combination -r0_bx2, c0, -r1_bx2 is allowed";
string PS_080 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_bx2, c0, -r1_bx2 ";

PS_CRITERIA PS_081_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_081_Desc = "ps_1_4 : mad source reg combination -r0_bx2, c0, r1 is allowed";
string PS_081 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, -r0_bx2, c0, r1 ";

PS_CRITERIA PS_082_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_082_Desc = "ps_1_4 : mad source reg combination r0, c0, r1_bias is allowed";
string PS_082 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1_bias ";

PS_CRITERIA PS_083_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_083_Desc = "ps_1_4 : mad source reg combination r0, c0, 1 - r1 is allowed";
string PS_083 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, 1 - r1 ";

PS_CRITERIA PS_084_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_084_Desc = "ps_1_4 : mad source reg combination r0, c0, -r1 is allowed";
string PS_084 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, -r1 ";

PS_CRITERIA PS_085_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_085_Desc = "ps_1_4 : mad source reg combination r0, c0, r1_x2 is allowed";
string PS_085 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1_x2 ";

PS_CRITERIA PS_086_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_086_Desc = "ps_1_4 : mad source reg combination r0, c0, r1_bx2 is allowed";
string PS_086 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1_bx2 ";

PS_CRITERIA PS_087_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_087_Desc = "ps_1_4 : mad source reg combination r0, c0, -r1_x2 is allowed";
string PS_087 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, -r1_x2 ";

PS_CRITERIA PS_088_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_088_Desc = "ps_1_4 : mad source reg combination r0, c0, -r1_bx2 is allowed";
string PS_088 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, -r1_bx2 ";

PS_CRITERIA PS_089_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_089_Desc = "ps_1_4 : mad source reg combination r0, c0, r1 is allowed";
string PS_089 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1 ";

PS_CRITERIA PS_090_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_090_Desc = "ps_1_4 : mad source reg combination r0.r, c0, r1 is allowed";
string PS_090 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.r, c0, r1 ";

PS_CRITERIA PS_091_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_091_Desc = "ps_1_4 : mad source reg combination r0.g, c0, r1 is allowed";
string PS_091 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.g, c0, r1 ";

PS_CRITERIA PS_092_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_092_Desc = "ps_1_4 : mad source reg combination r0.b, c0, r1 is allowed";
string PS_092 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.b, c0, r1 ";

PS_CRITERIA PS_093_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_093_Desc = "ps_1_4 : mad source reg combination r0.a, c0, r1 is allowed";
string PS_093 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.a, c0, r1 ";

PS_CRITERIA PS_094_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_094_Desc = "ps_1_4 : mad source reg combination r0, c0.r, r1 is allowed";
string PS_094 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.r, r1 ";

PS_CRITERIA PS_095_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_095_Desc = "ps_1_4 : mad source reg combination r0, c0.g, r1 is allowed";
string PS_095 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.g, r1 ";

PS_CRITERIA PS_096_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_096_Desc = "ps_1_4 : mad source reg combination r0, c0.b, r1 is allowed";
string PS_096 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.b, r1 ";

PS_CRITERIA PS_097_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_097_Desc = "ps_1_4 : mad source reg combination r0, c0.a, r1 is allowed";
string PS_097 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.a, r1 ";

PS_CRITERIA PS_098_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_098_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.r is allowed";
string PS_098 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.r ";

PS_CRITERIA PS_099_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_099_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.g is allowed";
string PS_099 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.g ";

PS_CRITERIA PS_100_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_100_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.b is allowed";
string PS_100 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.b ";

PS_CRITERIA PS_101_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_101_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.a is allowed";
string PS_101 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.a ";

PS_CRITERIA PS_102_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_102_Desc = "ps_1_4 : mad source reg combination v0, v1, v2 is NOT allowed";
string PS_102 = 
	"ps_1_4 "
	"mad r0, v0, v1, v2 "
	"mov r0, c0 ";

PS_CRITERIA PS_103_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_103_Desc = "ps_1_4 : mad source reg combination c0, c1, c2 is NOT allowed";
string PS_103 = 
	"ps_1_4 "
	"def c2, 1, 1, 1, 1 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"mad r0, c0, c1, c2 "
	"mov r0, c0 ";

PS_CRITERIA PS_104_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_104_Desc = "ps_1_4 : mad source reg combination t0, t0, t0 is NOT allowed";
string PS_104 = 
	"ps_1_4 "
	"texcrd r0, t0 "
	"mad r0, t0, t0, t0 "
	"mov r0, c0 ";

PS_CRITERIA PS_105_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_105_Desc = "ps_1_4 : mad source reg combination r0.gbra, c0, r1 is NOT allowed";
string PS_105 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.gbra, c0, r1 ";

PS_CRITERIA PS_106_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_106_Desc = "ps_1_4 : mad source reg combination r0.brga, c0, r1 is NOT allowed";
string PS_106 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.brga, c0, r1 ";

PS_CRITERIA PS_107_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_107_Desc = "ps_1_4 : mad source reg combination r0.abgr, c0, r1 is NOT allowed";
string PS_107 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.abgr, c0, r1 ";

PS_CRITERIA PS_108_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_108_Desc = "ps_1_4 : mad source reg combination r0.agrb, c0, r1 is NOT allowed";
string PS_108 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.agrb, c0, r1 ";

PS_CRITERIA PS_109_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_109_Desc = "ps_1_4 : mad source reg combination r0.rbga, c0, r1 is NOT allowed";
string PS_109 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.rbga, c0, r1 ";

PS_CRITERIA PS_110_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_110_Desc = "ps_1_4 : mad source reg combination r0.rgab, c0, r1 is NOT allowed";
string PS_110 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.rgab, c0, r1 ";

PS_CRITERIA PS_111_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_111_Desc = "ps_1_4 : mad source reg combination r0.bgr, c0, r1 is NOT allowed";
string PS_111 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.bgr, c0, r1 ";

PS_CRITERIA PS_112_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_112_Desc = "ps_1_4 : mad source reg combination r0.rbg, c0, r1 is NOT allowed";
string PS_112 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.rbg, c0, r1 ";

PS_CRITERIA PS_113_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_113_Desc = "ps_1_4 : mad source reg combination r0.gar, c0, r1 is NOT allowed";
string PS_113 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.gar, c0, r1 ";

PS_CRITERIA PS_114_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_114_Desc = "ps_1_4 : mad source reg combination r0.gr, c0, r1 is NOT allowed";
string PS_114 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.gr, c0, r1 ";

PS_CRITERIA PS_115_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_115_Desc = "ps_1_4 : mad source reg combination r0.ab, c0, r1 is NOT allowed";
string PS_115 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.ab, c0, r1 ";

PS_CRITERIA PS_116_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_116_Desc = "ps_1_4 : mad source reg combination r0.bg, c0, r1 is NOT allowed";
string PS_116 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0.bg, c0, r1 ";

PS_CRITERIA PS_117_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_117_Desc = "ps_1_4 : mad source reg combination r0, c0.gbra, r1 is NOT allowed";
string PS_117 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.gbra, r1 ";

PS_CRITERIA PS_118_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_118_Desc = "ps_1_4 : mad source reg combination r0, c0.brga, r1 is NOT allowed";
string PS_118 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.brga, r1 ";

PS_CRITERIA PS_119_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_119_Desc = "ps_1_4 : mad source reg combination r0, c0.abgr, r1 is NOT allowed";
string PS_119 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.abgr, r1 ";

PS_CRITERIA PS_120_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_120_Desc = "ps_1_4 : mad source reg combination r0, c0.agrb, r1 is NOT allowed";
string PS_120 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.agrb, r1 ";

PS_CRITERIA PS_121_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_121_Desc = "ps_1_4 : mad source reg combination r0, c0.rbga, r1 is NOT allowed";
string PS_121 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.rbga, r1 ";

PS_CRITERIA PS_122_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_122_Desc = "ps_1_4 : mad source reg combination r0, c0.rgab, r1 is NOT allowed";
string PS_122 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.rgab, r1 ";

PS_CRITERIA PS_123_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_123_Desc = "ps_1_4 : mad source reg combination r0, c0.bgr, r1 is NOT allowed";
string PS_123 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.bgr, r1 ";

PS_CRITERIA PS_124_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_124_Desc = "ps_1_4 : mad source reg combination r0, c0.rbg, r1 is NOT allowed";
string PS_124 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.rbg, r1 ";

PS_CRITERIA PS_125_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_125_Desc = "ps_1_4 : mad source reg combination r0, c0.gar, r1 is NOT allowed";
string PS_125 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.gar, r1 ";

PS_CRITERIA PS_126_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_126_Desc = "ps_1_4 : mad source reg combination r0, c0.gr, r1 is NOT allowed";
string PS_126 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.gr, r1 ";

PS_CRITERIA PS_127_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_127_Desc = "ps_1_4 : mad source reg combination r0, c0.ab, r1 is NOT allowed";
string PS_127 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.ab, r1 ";

PS_CRITERIA PS_128_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_128_Desc = "ps_1_4 : mad source reg combination r0, c0.bg, r1 is NOT allowed";
string PS_128 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0.bg, r1 ";

PS_CRITERIA PS_129_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_129_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.gbra is NOT allowed";
string PS_129 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.gbra ";

PS_CRITERIA PS_130_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_130_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.brga is NOT allowed";
string PS_130 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.brga ";

PS_CRITERIA PS_131_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_131_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.abgr is NOT allowed";
string PS_131 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.abgr ";

PS_CRITERIA PS_132_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_132_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.agrb is NOT allowed";
string PS_132 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.agrb ";

PS_CRITERIA PS_133_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_133_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.rbga is NOT allowed";
string PS_133 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.rbga ";

PS_CRITERIA PS_134_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_134_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.rgab is NOT allowed";
string PS_134 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.rgab ";

PS_CRITERIA PS_135_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_135_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.bgr is NOT allowed";
string PS_135 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.bgr ";

PS_CRITERIA PS_136_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_136_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.rbg is NOT allowed";
string PS_136 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.rbg ";

PS_CRITERIA PS_137_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_137_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.gar is NOT allowed";
string PS_137 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.gar ";

PS_CRITERIA PS_138_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_138_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.gr is NOT allowed";
string PS_138 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.gr ";

PS_CRITERIA PS_139_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_139_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.ab is NOT allowed";
string PS_139 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.ab ";

PS_CRITERIA PS_140_Criteria = { false, false, 0x0104, -1, -1, -1, -1, CAPS_ARBITRARYSWIZZLE, -1, 0.f };
string PS_140_Desc = "ps_1_4 : mad source reg combination r0, c0, r1.bg is NOT allowed";
string PS_140 = 
	"ps_1_4 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"mov r1, c0 "
	"mad r0, r0, c0, r1.bg ";

PS_CRITERIA PS_141_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_141_Desc = "ps_1_4 : mad dest r# is allowed";
string PS_141 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_142_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_142_Desc = "ps_1_4 : mad _x2 dest r# is allowed";
string PS_142 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x2 r0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_143_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_143_Desc = "ps_1_4 : mad _x4 dest r# is allowed";
string PS_143 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x4 r0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_144_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_144_Desc = "ps_1_4 : mad _x8 dest r# is allowed";
string PS_144 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x8 r0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_145_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_145_Desc = "ps_1_4 : mad _d2 dest r# is allowed";
string PS_145 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d2 r0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_146_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_146_Desc = "ps_1_4 : mad _d4 dest r# is allowed";
string PS_146 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d4 r0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_147_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_147_Desc = "ps_1_4 : mad _d8 dest r# is allowed";
string PS_147 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d8 r0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_148_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_148_Desc = "ps_1_4 : mad _sat dest r# is allowed";
string PS_148 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_sat r0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_149_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_149_Desc = "ps_1_4 : mad dest v# is NOT allowed";
string PS_149 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad v0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_150_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_150_Desc = "ps_1_4 : mad _x2 dest v# is NOT allowed";
string PS_150 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x2 v0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_151_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_151_Desc = "ps_1_4 : mad _x4 dest v# is NOT allowed";
string PS_151 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x4 v0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_152_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_152_Desc = "ps_1_4 : mad _x8 dest v# is NOT allowed";
string PS_152 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x8 v0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_153_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_153_Desc = "ps_1_4 : mad _d2 dest v# is NOT allowed";
string PS_153 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d2 v0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_154_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_154_Desc = "ps_1_4 : mad _d4 dest v# is NOT allowed";
string PS_154 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d4 v0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_155_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_155_Desc = "ps_1_4 : mad _d8 dest v# is NOT allowed";
string PS_155 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d8 v0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_156_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_156_Desc = "ps_1_4 : mad _sat dest v# is NOT allowed";
string PS_156 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_sat v0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_157_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_157_Desc = "ps_1_4 : mad dest c# is NOT allowed";
string PS_157 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad c1, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_158_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_158_Desc = "ps_1_4 : mad _x2 dest c# is NOT allowed";
string PS_158 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x2 c1, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_159_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_159_Desc = "ps_1_4 : mad _x4 dest c# is NOT allowed";
string PS_159 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x4 c1, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_160_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_160_Desc = "ps_1_4 : mad _x8 dest c# is NOT allowed";
string PS_160 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x8 c1, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_161_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_161_Desc = "ps_1_4 : mad _d2 dest c# is NOT allowed";
string PS_161 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d2 c1, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_162_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_162_Desc = "ps_1_4 : mad _d4 dest c# is NOT allowed";
string PS_162 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d4 c1, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_163_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_163_Desc = "ps_1_4 : mad _d8 dest c# is NOT allowed";
string PS_163 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d8 c1, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_164_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_164_Desc = "ps_1_4 : mad _sat dest c# is NOT allowed";
string PS_164 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_sat c1, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_165_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_165_Desc = "ps_1_4 : mad dest t# is NOT allowed";
string PS_165 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad t0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_166_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_166_Desc = "ps_1_4 : mad _x2 dest t# is NOT allowed";
string PS_166 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x2 t0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_167_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_167_Desc = "ps_1_4 : mad _x4 dest t# is NOT allowed";
string PS_167 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x4 t0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_168_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_168_Desc = "ps_1_4 : mad _x8 dest t# is NOT allowed";
string PS_168 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_x8 t0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_169_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_169_Desc = "ps_1_4 : mad _d2 dest t# is NOT allowed";
string PS_169 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d2 t0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_170_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_170_Desc = "ps_1_4 : mad _d4 dest t# is NOT allowed";
string PS_170 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d4 t0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_171_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_171_Desc = "ps_1_4 : mad _d8 dest t# is NOT allowed";
string PS_171 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_d8 t0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_172_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_172_Desc = "ps_1_4 : mad _sat dest t# is NOT allowed";
string PS_172 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad_sat t0, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_173_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_173_Desc = "ps_1_4 : mad write mask .r is allowed";
string PS_173 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.r, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_174_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_174_Desc = "ps_1_4 : mad write mask .g is allowed";
string PS_174 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.g, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_175_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_175_Desc = "ps_1_4 : mad write mask .b is allowed";
string PS_175 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.b, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_176_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_176_Desc = "ps_1_4 : mad write mask .a is allowed";
string PS_176 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.a, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_177_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_177_Desc = "ps_1_4 : mad write mask .rg is allowed";
string PS_177 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.rg, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_178_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_178_Desc = "ps_1_4 : mad write mask .gb is allowed";
string PS_178 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.gb, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_179_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_179_Desc = "ps_1_4 : mad write mask .ba is allowed";
string PS_179 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.ba, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_180_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_180_Desc = "ps_1_4 : mad write mask .rb is allowed";
string PS_180 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.rb, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_181_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_181_Desc = "ps_1_4 : mad write mask .ra is allowed";
string PS_181 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.ra, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_182_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_182_Desc = "ps_1_4 : mad write mask .ga is allowed";
string PS_182 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.ga, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_183_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_183_Desc = "ps_1_4 : mad write mask .rgb is allowed";
string PS_183 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.rgb, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_184_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_184_Desc = "ps_1_4 : mad write mask .gba is allowed";
string PS_184 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.gba, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_185_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_185_Desc = "ps_1_4 : mad write mask .rba is allowed";
string PS_185 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.rba, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_186_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_186_Desc = "ps_1_4 : mad write mask .rgba is allowed";
string PS_186 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.rgba, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_187_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_187_Desc = "ps_1_4 : mad write mask .yx is NOT allowed";
string PS_187 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.yx, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_188_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_188_Desc = "ps_1_4 : mad write mask .zx is NOT allowed";
string PS_188 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.zx, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_189_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_189_Desc = "ps_1_4 : mad write mask .zy is NOT allowed";
string PS_189 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.zy, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_190_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_190_Desc = "ps_1_4 : mad write mask .wx is NOT allowed";
string PS_190 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.wx, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_191_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_191_Desc = "ps_1_4 : mad write mask .wz is NOT allowed";
string PS_191 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.wz, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_192_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_192_Desc = "ps_1_4 : mad write mask .wy is NOT allowed";
string PS_192 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.wy, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_193_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_193_Desc = "ps_1_4 : mad write mask .zyx is NOT allowed";
string PS_193 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.zyx, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_194_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_194_Desc = "ps_1_4 : mad write mask .wzy is NOT allowed";
string PS_194 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.wzy, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_195_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_195_Desc = "ps_1_4 : mad write mask .wzx is NOT allowed";
string PS_195 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.wzx, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_196_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_196_Desc = "ps_1_4 : mad write mask .wyx is NOT allowed";
string PS_196 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.wyx, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_197_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_197_Desc = "ps_1_4 : mad write mask .yxw is NOT allowed";
string PS_197 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.yxw, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_198_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_198_Desc = "ps_1_4 : mad write mask .wzyx is NOT allowed";
string PS_198 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.wzyx, v0, v1, r0 "
	"mov r0, c0 ";

PS_CRITERIA PS_199_Criteria = { false, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
string PS_199_Desc = "ps_1_4 : mad write mask .zxwy is NOT allowed";
string PS_199 = 
	"ps_1_4 "
	"mov r0, c0 "
	"mad r0.zxwy, v0, v1, r0 "
	"mov r0, c0 ";


