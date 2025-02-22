#include "Test_Include.fx"

int Test_Count = 127;

string TestInfo
<
	string TestType = "VS";
>
= "vs_1_1_inst_m4x4";

VS_CRITERIA VS_001_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_001_Desc = "vs_1_1 : m4x4 source reg combination v0, c0 is allowed";
string VS_001 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_002_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_002_Desc = "vs_1_1 : m4x4 source reg combination -v0, c0 is allowed";
string VS_002 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, -v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_003_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_003_Desc = "vs_1_1 : m4x4 source reg combination v0, c0 is allowed";
string VS_003 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_004_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_004_Desc = "vs_1_1 : m4x4 source reg combination v0.x, c0 is allowed";
string VS_004 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.x, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_005_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_005_Desc = "vs_1_1 : m4x4 source reg combination v0.y, c0 is allowed";
string VS_005 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.y, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_006_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_006_Desc = "vs_1_1 : m4x4 source reg combination v0.z, c0 is allowed";
string VS_006 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.z, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_007_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_007_Desc = "vs_1_1 : m4x4 source reg combination v0.w, c0 is allowed";
string VS_007 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.w, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_008_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_008_Desc = "vs_1_1 : m4x4 source reg combination v0.yzxw, c0 is allowed";
string VS_008 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.yzxw, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_009_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_009_Desc = "vs_1_1 : m4x4 source reg combination v0.zxyw, c0 is allowed";
string VS_009 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.zxyw, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_010_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_010_Desc = "vs_1_1 : m4x4 source reg combination v0.wzyx, c0 is allowed";
string VS_010 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.wzyx, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_011_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_011_Desc = "vs_1_1 : m4x4 source reg combination v0.wyxz, c0 is allowed";
string VS_011 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.wyxz, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_012_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_012_Desc = "vs_1_1 : m4x4 source reg combination v0.xzyw, c0 is allowed";
string VS_012 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.xzyw, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_013_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_013_Desc = "vs_1_1 : m4x4 source reg combination v0.xywz, c0 is allowed";
string VS_013 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.xywz, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_014_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_014_Desc = "vs_1_1 : m4x4 source reg combination v0.zyx, c0 is allowed";
string VS_014 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.zyx, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_015_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_015_Desc = "vs_1_1 : m4x4 source reg combination v0.xzy, c0 is allowed";
string VS_015 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.xzy, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_016_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_016_Desc = "vs_1_1 : m4x4 source reg combination v0.ywx, c0 is allowed";
string VS_016 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.ywx, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_017_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_017_Desc = "vs_1_1 : m4x4 source reg combination v0.yx, c0 is allowed";
string VS_017 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.yx, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_018_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_018_Desc = "vs_1_1 : m4x4 source reg combination v0.wz, c0 is allowed";
string VS_018 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.wz, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_019_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_019_Desc = "vs_1_1 : m4x4 source reg combination v0.zy, c0 is allowed";
string VS_019 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0.zy, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_020_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_020_Desc = "vs_1_1 : m4x4 source reg combination c0, c1 is NOT allowed";
string VS_020 = 
	"vs_1_1 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"m4x4 r0, c0, c1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_021_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_021_Desc = "vs_1_1 : m4x4 source reg combination r0, v0 is NOT allowed";
string VS_021 = 
	"vs_1_1 "
	"dcl_fog v0 "
	"mov r0, c0 "
	"m4x4 r0, r0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_022_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_022_Desc = "vs_1_1 : m4x4 source reg combination r0, r0 is NOT allowed";
string VS_022 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, r0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_023_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_023_Desc = "vs_1_1 : m4x4 source reg combination r0, a0 is NOT allowed";
string VS_023 = 
	"vs_1_1 "
	"mov r0, c0 "
	"mov a0.x, c0.x "
	"m4x4 r0, r0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_024_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_024_Desc = "vs_1_1 : m4x4 source reg combination r0, oPos is NOT allowed";
string VS_024 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, r0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_025_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_025_Desc = "vs_1_1 : m4x4 source reg combination r0, oFog is NOT allowed";
string VS_025 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, r0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_026_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_026_Desc = "vs_1_1 : m4x4 source reg combination r0, oPts is NOT allowed";
string VS_026 = 
	"vs_1_1 "
	"texcoord ts "
	"mov r0, c0 "
	"m4x4 r0, r0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_027_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_027_Desc = "vs_1_1 : m4x4 source reg combination r0, oD0 is NOT allowed";
string VS_027 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, r0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_028_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_028_Desc = "vs_1_1 : m4x4 source reg combination r0, oT0 is NOT allowed";
string VS_028 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, r0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_029_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_029_Desc = "vs_1_1 : m4x4 source reg combination a0, v0 is NOT allowed";
string VS_029 = 
	"vs_1_1 "
	"dcl_fog v0 "
	"mov a0.x, c0.x "
	"m4x4 r0, a0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_030_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_030_Desc = "vs_1_1 : m4x4 source reg combination a0, r0 is NOT allowed";
string VS_030 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"mov r0, c0 "
	"m4x4 r0, a0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_031_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_031_Desc = "vs_1_1 : m4x4 source reg combination a0, a0 is NOT allowed";
string VS_031 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, a0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_032_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_032_Desc = "vs_1_1 : m4x4 source reg combination a0, oPos is NOT allowed";
string VS_032 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, a0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_033_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_033_Desc = "vs_1_1 : m4x4 source reg combination a0, oFog is NOT allowed";
string VS_033 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, a0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_034_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_034_Desc = "vs_1_1 : m4x4 source reg combination a0, oPts is NOT allowed";
string VS_034 = 
	"vs_1_1 "
	"texcoord ts "
	"mov a0.x, c0.x "
	"m4x4 r0, a0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_035_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_035_Desc = "vs_1_1 : m4x4 source reg combination a0, oD0 is NOT allowed";
string VS_035 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, a0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_036_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_036_Desc = "vs_1_1 : m4x4 source reg combination a0, oT0 is NOT allowed";
string VS_036 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, a0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_037_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_037_Desc = "vs_1_1 : m4x4 source reg combination oPos, v0 is NOT allowed";
string VS_037 = 
	"vs_1_1 "
	"dcl_fog v0 "
	"m4x4 r0, oPos, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_038_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_038_Desc = "vs_1_1 : m4x4 source reg combination oPos, r0 is NOT allowed";
string VS_038 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, oPos, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_039_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_039_Desc = "vs_1_1 : m4x4 source reg combination oPos, a0 is NOT allowed";
string VS_039 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, oPos, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_040_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_040_Desc = "vs_1_1 : m4x4 source reg combination oPos, oPos is NOT allowed";
string VS_040 = 
	"vs_1_1 "
	"m4x4 r0, oPos, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_041_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_041_Desc = "vs_1_1 : m4x4 source reg combination oPos, oFog is NOT allowed";
string VS_041 = 
	"vs_1_1 "
	"m4x4 r0, oPos, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_042_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_042_Desc = "vs_1_1 : m4x4 source reg combination oPos, oPts is NOT allowed";
string VS_042 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oPos, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_043_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_043_Desc = "vs_1_1 : m4x4 source reg combination oPos, oD0 is NOT allowed";
string VS_043 = 
	"vs_1_1 "
	"m4x4 r0, oPos, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_044_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_044_Desc = "vs_1_1 : m4x4 source reg combination oPos, oT0 is NOT allowed";
string VS_044 = 
	"vs_1_1 "
	"m4x4 r0, oPos, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_045_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_045_Desc = "vs_1_1 : m4x4 source reg combination oFog, v0 is NOT allowed";
string VS_045 = 
	"vs_1_1 "
	"dcl_fog v0 "
	"m4x4 r0, oFog, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_046_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_046_Desc = "vs_1_1 : m4x4 source reg combination oFog, r0 is NOT allowed";
string VS_046 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, oFog, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_047_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_047_Desc = "vs_1_1 : m4x4 source reg combination oFog, a0 is NOT allowed";
string VS_047 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, oFog, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_048_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_048_Desc = "vs_1_1 : m4x4 source reg combination oFog, oPos is NOT allowed";
string VS_048 = 
	"vs_1_1 "
	"m4x4 r0, oFog, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_049_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_049_Desc = "vs_1_1 : m4x4 source reg combination oFog, oFog is NOT allowed";
string VS_049 = 
	"vs_1_1 "
	"m4x4 r0, oFog, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_050_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_050_Desc = "vs_1_1 : m4x4 source reg combination oFog, oPts is NOT allowed";
string VS_050 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oFog, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_051_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_051_Desc = "vs_1_1 : m4x4 source reg combination oFog, oD0 is NOT allowed";
string VS_051 = 
	"vs_1_1 "
	"m4x4 r0, oFog, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_052_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_052_Desc = "vs_1_1 : m4x4 source reg combination oFog, oT0 is NOT allowed";
string VS_052 = 
	"vs_1_1 "
	"m4x4 r0, oFog, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_053_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_053_Desc = "vs_1_1 : m4x4 source reg combination oPts, v0 is NOT allowed";
string VS_053 = 
	"vs_1_1 "
	"texcoord ts "
	"dcl_fog v0 "
	"m4x4 r0, oPts, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_054_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_054_Desc = "vs_1_1 : m4x4 source reg combination oPts, r0 is NOT allowed";
string VS_054 = 
	"vs_1_1 "
	"texcoord ts "
	"mov r0, c0 "
	"m4x4 r0, oPts, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_055_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_055_Desc = "vs_1_1 : m4x4 source reg combination oPts, a0 is NOT allowed";
string VS_055 = 
	"vs_1_1 "
	"texcoord ts "
	"mov a0.x, c0.x "
	"m4x4 r0, oPts, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_056_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_056_Desc = "vs_1_1 : m4x4 source reg combination oPts, oPos is NOT allowed";
string VS_056 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oPts, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_057_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_057_Desc = "vs_1_1 : m4x4 source reg combination oPts, oFog is NOT allowed";
string VS_057 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oPts, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_058_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_058_Desc = "vs_1_1 : m4x4 source reg combination oPts, oPts is NOT allowed";
string VS_058 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oPts, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_059_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_059_Desc = "vs_1_1 : m4x4 source reg combination oPts, oD0 is NOT allowed";
string VS_059 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oPts, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_060_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_060_Desc = "vs_1_1 : m4x4 source reg combination oPts, oT0 is NOT allowed";
string VS_060 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oPts, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_061_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_061_Desc = "vs_1_1 : m4x4 source reg combination oD0, v0 is NOT allowed";
string VS_061 = 
	"vs_1_1 "
	"dcl_fog v0 "
	"m4x4 r0, oD0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_062_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_062_Desc = "vs_1_1 : m4x4 source reg combination oD0, r0 is NOT allowed";
string VS_062 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, oD0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_063_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_063_Desc = "vs_1_1 : m4x4 source reg combination oD0, a0 is NOT allowed";
string VS_063 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, oD0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_064_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_064_Desc = "vs_1_1 : m4x4 source reg combination oD0, oPos is NOT allowed";
string VS_064 = 
	"vs_1_1 "
	"m4x4 r0, oD0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_065_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_065_Desc = "vs_1_1 : m4x4 source reg combination oD0, oFog is NOT allowed";
string VS_065 = 
	"vs_1_1 "
	"m4x4 r0, oD0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_066_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_066_Desc = "vs_1_1 : m4x4 source reg combination oD0, oPts is NOT allowed";
string VS_066 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oD0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_067_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_067_Desc = "vs_1_1 : m4x4 source reg combination oD0, oD0 is NOT allowed";
string VS_067 = 
	"vs_1_1 "
	"m4x4 r0, oD0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_068_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_068_Desc = "vs_1_1 : m4x4 source reg combination oD0, oT0 is NOT allowed";
string VS_068 = 
	"vs_1_1 "
	"m4x4 r0, oD0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_069_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_069_Desc = "vs_1_1 : m4x4 source reg combination oT0, v0 is NOT allowed";
string VS_069 = 
	"vs_1_1 "
	"dcl_fog v0 "
	"m4x4 r0, oT0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_070_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_070_Desc = "vs_1_1 : m4x4 source reg combination oT0, r0 is NOT allowed";
string VS_070 = 
	"vs_1_1 "
	"mov r0, c0 "
	"m4x4 r0, oT0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_071_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_071_Desc = "vs_1_1 : m4x4 source reg combination oT0, a0 is NOT allowed";
string VS_071 = 
	"vs_1_1 "
	"mov a0.x, c0.x "
	"m4x4 r0, oT0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_072_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_072_Desc = "vs_1_1 : m4x4 source reg combination oT0, oPos is NOT allowed";
string VS_072 = 
	"vs_1_1 "
	"m4x4 r0, oT0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_073_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_073_Desc = "vs_1_1 : m4x4 source reg combination oT0, oFog is NOT allowed";
string VS_073 = 
	"vs_1_1 "
	"m4x4 r0, oT0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_074_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_074_Desc = "vs_1_1 : m4x4 source reg combination oT0, oPts is NOT allowed";
string VS_074 = 
	"vs_1_1 "
	"texcoord ts "
	"m4x4 r0, oT0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_075_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_075_Desc = "vs_1_1 : m4x4 source reg combination oT0, oD0 is NOT allowed";
string VS_075 = 
	"vs_1_1 "
	"m4x4 r0, oT0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_076_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_076_Desc = "vs_1_1 : m4x4 source reg combination oT0, oT0 is NOT allowed";
string VS_076 = 
	"vs_1_1 "
	"m4x4 r0, oT0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_077_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_077_Desc = "vs_1_1 : m4x4 source reg combination v0, -c0 is NOT allowed";
string VS_077 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, -c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_078_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_078_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.x is NOT allowed";
string VS_078 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.x "
	"mov oPos, c0 ";

VS_CRITERIA VS_079_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_079_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.y is NOT allowed";
string VS_079 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.y "
	"mov oPos, c0 ";

VS_CRITERIA VS_080_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_080_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.z is NOT allowed";
string VS_080 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.z "
	"mov oPos, c0 ";

VS_CRITERIA VS_081_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_081_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.w is NOT allowed";
string VS_081 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.w "
	"mov oPos, c0 ";

VS_CRITERIA VS_082_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_082_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.yzxw is NOT allowed";
string VS_082 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.yzxw "
	"mov oPos, c0 ";

VS_CRITERIA VS_083_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_083_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.zxyw is NOT allowed";
string VS_083 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.zxyw "
	"mov oPos, c0 ";

VS_CRITERIA VS_084_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_084_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.wzyx is NOT allowed";
string VS_084 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.wzyx "
	"mov oPos, c0 ";

VS_CRITERIA VS_085_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_085_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.wyxz is NOT allowed";
string VS_085 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.wyxz "
	"mov oPos, c0 ";

VS_CRITERIA VS_086_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_086_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.xzyw is NOT allowed";
string VS_086 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.xzyw "
	"mov oPos, c0 ";

VS_CRITERIA VS_087_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_087_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.xywz is NOT allowed";
string VS_087 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.xywz "
	"mov oPos, c0 ";

VS_CRITERIA VS_088_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_088_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.zyx is NOT allowed";
string VS_088 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.zyx "
	"mov oPos, c0 ";

VS_CRITERIA VS_089_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_089_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.xzy is NOT allowed";
string VS_089 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.xzy "
	"mov oPos, c0 ";

VS_CRITERIA VS_090_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_090_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.ywx is NOT allowed";
string VS_090 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.ywx "
	"mov oPos, c0 ";

VS_CRITERIA VS_091_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_091_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.yx is NOT allowed";
string VS_091 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.yx "
	"mov oPos, c0 ";

VS_CRITERIA VS_092_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_092_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.wz is NOT allowed";
string VS_092 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.wz "
	"mov oPos, c0 ";

VS_CRITERIA VS_093_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_093_Desc = "vs_1_1 : m4x4 source reg combination v0, c0.zy is NOT allowed";
string VS_093 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0.zy "
	"mov oPos, c0 ";

VS_CRITERIA VS_094_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_094_Desc = "vs_1_1 : m4x4 dest r# is allowed";
string VS_094 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_095_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_095_Desc = "vs_1_1 : m4x4 dest oPos is allowed";
string VS_095 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 oPos, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_096_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_096_Desc = "vs_1_1 : m4x4 dest oD# is allowed";
string VS_096 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 oD0, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_097_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_097_Desc = "vs_1_1 : m4x4 dest oT# is allowed";
string VS_097 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 oT0, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_098_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_098_Desc = "vs_1_1 : m4x4 dest v# is NOT allowed";
string VS_098 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 v0, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_099_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_099_Desc = "vs_1_1 : m4x4 dest c# is NOT allowed";
string VS_099 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 c1, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_100_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_100_Desc = "vs_1_1 : m4x4 dest a0 is NOT allowed";
string VS_100 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 a0, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_101_Criteria = { true, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_101_Desc = "vs_1_1 : m4x4 write mask .xyzw is allowed";
string VS_101 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.xyzw, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_102_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_102_Desc = "vs_1_1 : m4x4 write mask .x is NOT allowed";
string VS_102 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.x, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_103_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_103_Desc = "vs_1_1 : m4x4 write mask .y is NOT allowed";
string VS_103 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.y, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_104_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_104_Desc = "vs_1_1 : m4x4 write mask .z is NOT allowed";
string VS_104 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.z, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_105_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_105_Desc = "vs_1_1 : m4x4 write mask .w is NOT allowed";
string VS_105 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.w, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_106_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_106_Desc = "vs_1_1 : m4x4 write mask .xy is NOT allowed";
string VS_106 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.xy, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_107_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_107_Desc = "vs_1_1 : m4x4 write mask .yz is NOT allowed";
string VS_107 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.yz, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_108_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_108_Desc = "vs_1_1 : m4x4 write mask .zw is NOT allowed";
string VS_108 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.zw, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_109_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_109_Desc = "vs_1_1 : m4x4 write mask .xz is NOT allowed";
string VS_109 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.xz, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_110_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_110_Desc = "vs_1_1 : m4x4 write mask .xw is NOT allowed";
string VS_110 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.xw, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_111_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_111_Desc = "vs_1_1 : m4x4 write mask .yw is NOT allowed";
string VS_111 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.yw, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_112_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_112_Desc = "vs_1_1 : m4x4 write mask .xyz is NOT allowed";
string VS_112 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.xyz, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_113_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_113_Desc = "vs_1_1 : m4x4 write mask .yzw is NOT allowed";
string VS_113 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.yzw, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_114_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_114_Desc = "vs_1_1 : m4x4 write mask .xzw is NOT allowed";
string VS_114 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.xzw, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_115_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_115_Desc = "vs_1_1 : m4x4 write mask .yx is NOT allowed";
string VS_115 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.yx, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_116_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_116_Desc = "vs_1_1 : m4x4 write mask .zx is NOT allowed";
string VS_116 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.zx, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_117_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_117_Desc = "vs_1_1 : m4x4 write mask .zy is NOT allowed";
string VS_117 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.zy, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_118_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_118_Desc = "vs_1_1 : m4x4 write mask .wx is NOT allowed";
string VS_118 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.wx, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_119_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_119_Desc = "vs_1_1 : m4x4 write mask .wz is NOT allowed";
string VS_119 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.wz, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_120_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_120_Desc = "vs_1_1 : m4x4 write mask .wy is NOT allowed";
string VS_120 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.wy, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_121_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_121_Desc = "vs_1_1 : m4x4 write mask .zyx is NOT allowed";
string VS_121 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.zyx, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_122_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_122_Desc = "vs_1_1 : m4x4 write mask .wzy is NOT allowed";
string VS_122 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.wzy, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_123_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_123_Desc = "vs_1_1 : m4x4 write mask .wzx is NOT allowed";
string VS_123 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.wzx, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_124_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_124_Desc = "vs_1_1 : m4x4 write mask .wyx is NOT allowed";
string VS_124 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.wyx, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_125_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_125_Desc = "vs_1_1 : m4x4 write mask .yxw is NOT allowed";
string VS_125 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.yxw, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_126_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_126_Desc = "vs_1_1 : m4x4 write mask .wzyx is NOT allowed";
string VS_126 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.wzyx, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_127_Criteria = { false, false, 0x0101, -1, -1, -1, -1, 0, -1, 0.f };
string VS_127_Desc = "vs_1_1 : m4x4 write mask .zxwy is NOT allowed";
string VS_127 = 
	"vs_1_1 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"m4x4 r0.zxwy, v0, c0 "
	"mov oPos, c0 ";


