#include "Test_Include.fx"

int Test_Count = 199;

string TestInfo
<
	string TestType = "VS";
>
= "vs_2_0_inst_slt";

VS_CRITERIA VS_001_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_001_Desc = "vs_2_0 : slt source reg combination v0, r0 is allowed";
string VS_001 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"mov r0, c0 "
	"slt r0, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_002_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_002_Desc = "vs_2_0 : slt source reg combination v0, c0 is allowed";
string VS_002 = 
	"vs_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"slt r0, v0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_003_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_003_Desc = "vs_2_0 : slt source reg combination r0, v0 is allowed";
string VS_003 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"mov r0, c0 "
	"slt r0, r0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_004_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_004_Desc = "vs_2_0 : slt source reg combination r0, r1 is allowed";
string VS_004 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_005_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_005_Desc = "vs_2_0 : slt source reg combination r0, c0 is allowed";
string VS_005 = 
	"vs_2_0 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"slt r0, r0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_006_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_006_Desc = "vs_2_0 : slt source reg combination c0, v0 is allowed";
string VS_006 = 
	"vs_2_0 "
	"def c0, 1, 1, 1, 1 "
	"dcl_fog v0 "
	"slt r0, c0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_007_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_007_Desc = "vs_2_0 : slt source reg combination c0, r0 is allowed";
string VS_007 = 
	"vs_2_0 "
	"def c0, 1, 1, 1, 1 "
	"mov r0, c0 "
	"slt r0, c0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_008_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_008_Desc = "vs_2_0 : slt source reg combination -r0, -r1 is allowed";
string VS_008 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, -r0, -r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_009_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_009_Desc = "vs_2_0 : slt source reg combination -r0, r1 is allowed";
string VS_009 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, -r0, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_010_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_010_Desc = "vs_2_0 : slt source reg combination r0, -r1 is allowed";
string VS_010 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, -r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_011_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_011_Desc = "vs_2_0 : slt source reg combination r0, r1 is allowed";
string VS_011 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_012_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_012_Desc = "vs_2_0 : slt source reg combination r0.x, r1 is allowed";
string VS_012 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.x, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_013_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_013_Desc = "vs_2_0 : slt source reg combination r0.y, r1 is allowed";
string VS_013 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.y, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_014_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_014_Desc = "vs_2_0 : slt source reg combination r0.z, r1 is allowed";
string VS_014 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.z, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_015_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_015_Desc = "vs_2_0 : slt source reg combination r0.w, r1 is allowed";
string VS_015 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.w, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_016_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_016_Desc = "vs_2_0 : slt source reg combination r0.yzxw, r1 is allowed";
string VS_016 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.yzxw, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_017_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_017_Desc = "vs_2_0 : slt source reg combination r0.zxyw, r1 is allowed";
string VS_017 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.zxyw, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_018_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_018_Desc = "vs_2_0 : slt source reg combination r0.wzyx, r1 is allowed";
string VS_018 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.wzyx, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_019_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_019_Desc = "vs_2_0 : slt source reg combination r0.wyxz, r1 is allowed";
string VS_019 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.wyxz, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_020_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_020_Desc = "vs_2_0 : slt source reg combination r0.xzyw, r1 is allowed";
string VS_020 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.xzyw, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_021_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_021_Desc = "vs_2_0 : slt source reg combination r0.xywz, r1 is allowed";
string VS_021 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.xywz, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_022_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_022_Desc = "vs_2_0 : slt source reg combination r0.zyx, r1 is allowed";
string VS_022 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.zyx, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_023_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_023_Desc = "vs_2_0 : slt source reg combination r0.xzy, r1 is allowed";
string VS_023 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.xzy, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_024_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_024_Desc = "vs_2_0 : slt source reg combination r0.ywx, r1 is allowed";
string VS_024 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.ywx, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_025_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_025_Desc = "vs_2_0 : slt source reg combination r0.yx, r1 is allowed";
string VS_025 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.yx, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_026_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_026_Desc = "vs_2_0 : slt source reg combination r0.wz, r1 is allowed";
string VS_026 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.wz, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_027_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_027_Desc = "vs_2_0 : slt source reg combination r0.zy, r1 is allowed";
string VS_027 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0.zy, r1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_028_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_028_Desc = "vs_2_0 : slt source reg combination r0, r1.x is allowed";
string VS_028 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.x "
	"mov oPos, c0 ";

VS_CRITERIA VS_029_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_029_Desc = "vs_2_0 : slt source reg combination r0, r1.y is allowed";
string VS_029 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.y "
	"mov oPos, c0 ";

VS_CRITERIA VS_030_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_030_Desc = "vs_2_0 : slt source reg combination r0, r1.z is allowed";
string VS_030 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.z "
	"mov oPos, c0 ";

VS_CRITERIA VS_031_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_031_Desc = "vs_2_0 : slt source reg combination r0, r1.w is allowed";
string VS_031 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.w "
	"mov oPos, c0 ";

VS_CRITERIA VS_032_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_032_Desc = "vs_2_0 : slt source reg combination r0, r1.yzxw is allowed";
string VS_032 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.yzxw "
	"mov oPos, c0 ";

VS_CRITERIA VS_033_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_033_Desc = "vs_2_0 : slt source reg combination r0, r1.zxyw is allowed";
string VS_033 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.zxyw "
	"mov oPos, c0 ";

VS_CRITERIA VS_034_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_034_Desc = "vs_2_0 : slt source reg combination r0, r1.wzyx is allowed";
string VS_034 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.wzyx "
	"mov oPos, c0 ";

VS_CRITERIA VS_035_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_035_Desc = "vs_2_0 : slt source reg combination r0, r1.wyxz is allowed";
string VS_035 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.wyxz "
	"mov oPos, c0 ";

VS_CRITERIA VS_036_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_036_Desc = "vs_2_0 : slt source reg combination r0, r1.xzyw is allowed";
string VS_036 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.xzyw "
	"mov oPos, c0 ";

VS_CRITERIA VS_037_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_037_Desc = "vs_2_0 : slt source reg combination r0, r1.xywz is allowed";
string VS_037 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.xywz "
	"mov oPos, c0 ";

VS_CRITERIA VS_038_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_038_Desc = "vs_2_0 : slt source reg combination r0, r1.zyx is allowed";
string VS_038 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.zyx "
	"mov oPos, c0 ";

VS_CRITERIA VS_039_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_039_Desc = "vs_2_0 : slt source reg combination r0, r1.xzy is allowed";
string VS_039 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.xzy "
	"mov oPos, c0 ";

VS_CRITERIA VS_040_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_040_Desc = "vs_2_0 : slt source reg combination r0, r1.ywx is allowed";
string VS_040 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.ywx "
	"mov oPos, c0 ";

VS_CRITERIA VS_041_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_041_Desc = "vs_2_0 : slt source reg combination r0, r1.yx is allowed";
string VS_041 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.yx "
	"mov oPos, c0 ";

VS_CRITERIA VS_042_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_042_Desc = "vs_2_0 : slt source reg combination r0, r1.wz is allowed";
string VS_042 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.wz "
	"mov oPos, c0 ";

VS_CRITERIA VS_043_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_043_Desc = "vs_2_0 : slt source reg combination r0, r1.zy is allowed";
string VS_043 = 
	"vs_2_0 "
	"mov r0, c0 "
	"mov r1, c0 "
	"slt r0, r0, r1.zy "
	"mov oPos, c0 ";

VS_CRITERIA VS_044_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_044_Desc = "vs_2_0 : slt source reg combination v0, v1 is NOT allowed";
string VS_044 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"dcl_texcoord v1 "
	"slt r0, v0, v1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_045_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_045_Desc = "vs_2_0 : slt source reg combination c0, c1 is NOT allowed";
string VS_045 = 
	"vs_2_0 "
	"def c1, 1, 1, 1, 1 "
	"def c0, 1, 1, 1, 1 "
	"slt r0, c0, c1 "
	"mov oPos, c0 ";

VS_CRITERIA VS_046_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_046_Desc = "vs_2_0 : slt source reg combination a0, a0 is NOT allowed";
string VS_046 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, a0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_047_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_047_Desc = "vs_2_0 : slt source reg combination a0, b0 is NOT allowed";
string VS_047 = 
	"vs_2_0 "
	"defb b0, true "
	"mova a0.x, c0.x "
	"slt r0, a0, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_048_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_048_Desc = "vs_2_0 : slt source reg combination a0, i0 is NOT allowed";
string VS_048 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"mova a0.x, c0.x "
	"slt r0, a0, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_049_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_049_Desc = "vs_2_0 : slt source reg combination a0, aL is NOT allowed";
string VS_049 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"mova aL.x, c0.x "
	"slt r0, a0, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_050_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_050_Desc = "vs_2_0 : slt source reg combination a0, oPos is NOT allowed";
string VS_050 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, a0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_051_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_051_Desc = "vs_2_0 : slt source reg combination a0, oFog is NOT allowed";
string VS_051 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, a0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_052_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_052_Desc = "vs_2_0 : slt source reg combination a0, oPts is NOT allowed";
string VS_052 = 
	"vs_2_0 "
	"dcl ts "
	"mova a0.x, c0.x "
	"slt r0, a0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_053_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_053_Desc = "vs_2_0 : slt source reg combination a0, oD0 is NOT allowed";
string VS_053 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, a0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_054_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_054_Desc = "vs_2_0 : slt source reg combination a0, oT0 is NOT allowed";
string VS_054 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, a0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_055_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_055_Desc = "vs_2_0 : slt source reg combination b0, a0 is NOT allowed";
string VS_055 = 
	"vs_2_0 "
	"defb b0, true "
	"mova a0.x, c0.x "
	"slt r0, b0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_056_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_056_Desc = "vs_2_0 : slt source reg combination b0, b0 is NOT allowed";
string VS_056 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, b0, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_057_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_057_Desc = "vs_2_0 : slt source reg combination b0, i0 is NOT allowed";
string VS_057 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"slt r0, b0, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_058_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_058_Desc = "vs_2_0 : slt source reg combination b0, aL is NOT allowed";
string VS_058 = 
	"vs_2_0 "
	"defb b0, true "
	"mova aL.x, c0.x "
	"slt r0, b0, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_059_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_059_Desc = "vs_2_0 : slt source reg combination b0, oPos is NOT allowed";
string VS_059 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, b0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_060_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_060_Desc = "vs_2_0 : slt source reg combination b0, oFog is NOT allowed";
string VS_060 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, b0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_061_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_061_Desc = "vs_2_0 : slt source reg combination b0, oPts is NOT allowed";
string VS_061 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl ts "
	"slt r0, b0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_062_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_062_Desc = "vs_2_0 : slt source reg combination b0, oD0 is NOT allowed";
string VS_062 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, b0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_063_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_063_Desc = "vs_2_0 : slt source reg combination b0, oT0 is NOT allowed";
string VS_063 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, b0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_064_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_064_Desc = "vs_2_0 : slt source reg combination i0, a0 is NOT allowed";
string VS_064 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"mova a0.x, c0.x "
	"slt r0, i0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_065_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_065_Desc = "vs_2_0 : slt source reg combination i0, b0 is NOT allowed";
string VS_065 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, i0, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_066_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_066_Desc = "vs_2_0 : slt source reg combination i0, i0 is NOT allowed";
string VS_066 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, i0, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_067_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_067_Desc = "vs_2_0 : slt source reg combination i0, aL is NOT allowed";
string VS_067 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"mova aL.x, c0.x "
	"slt r0, i0, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_068_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_068_Desc = "vs_2_0 : slt source reg combination i0, oPos is NOT allowed";
string VS_068 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, i0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_069_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_069_Desc = "vs_2_0 : slt source reg combination i0, oFog is NOT allowed";
string VS_069 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, i0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_070_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_070_Desc = "vs_2_0 : slt source reg combination i0, oPts is NOT allowed";
string VS_070 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl ts "
	"slt r0, i0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_071_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_071_Desc = "vs_2_0 : slt source reg combination i0, oD0 is NOT allowed";
string VS_071 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, i0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_072_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_072_Desc = "vs_2_0 : slt source reg combination i0, oT0 is NOT allowed";
string VS_072 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, i0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_073_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_073_Desc = "vs_2_0 : slt source reg combination aL, a0 is NOT allowed";
string VS_073 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"mova a0.x, c0.x "
	"slt r0, aL, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_074_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_074_Desc = "vs_2_0 : slt source reg combination aL, b0 is NOT allowed";
string VS_074 = 
	"vs_2_0 "
	"defb b0, true "
	"mova aL.x, c0.x "
	"slt r0, aL, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_075_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_075_Desc = "vs_2_0 : slt source reg combination aL, i0 is NOT allowed";
string VS_075 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"mova aL.x, c0.x "
	"slt r0, aL, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_076_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_076_Desc = "vs_2_0 : slt source reg combination aL, aL is NOT allowed";
string VS_076 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, aL, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_077_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_077_Desc = "vs_2_0 : slt source reg combination aL, oPos is NOT allowed";
string VS_077 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, aL, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_078_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_078_Desc = "vs_2_0 : slt source reg combination aL, oFog is NOT allowed";
string VS_078 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, aL, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_079_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_079_Desc = "vs_2_0 : slt source reg combination aL, oPts is NOT allowed";
string VS_079 = 
	"vs_2_0 "
	"dcl ts "
	"mova aL.x, c0.x "
	"slt r0, aL, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_080_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_080_Desc = "vs_2_0 : slt source reg combination aL, oD0 is NOT allowed";
string VS_080 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, aL, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_081_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_081_Desc = "vs_2_0 : slt source reg combination aL, oT0 is NOT allowed";
string VS_081 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, aL, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_082_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_082_Desc = "vs_2_0 : slt source reg combination oPos, a0 is NOT allowed";
string VS_082 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, oPos, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_083_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_083_Desc = "vs_2_0 : slt source reg combination oPos, b0 is NOT allowed";
string VS_083 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, oPos, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_084_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_084_Desc = "vs_2_0 : slt source reg combination oPos, i0 is NOT allowed";
string VS_084 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, oPos, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_085_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_085_Desc = "vs_2_0 : slt source reg combination oPos, aL is NOT allowed";
string VS_085 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, oPos, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_086_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_086_Desc = "vs_2_0 : slt source reg combination oPos, oPos is NOT allowed";
string VS_086 = 
	"vs_2_0 "
	"slt r0, oPos, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_087_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_087_Desc = "vs_2_0 : slt source reg combination oPos, oFog is NOT allowed";
string VS_087 = 
	"vs_2_0 "
	"slt r0, oPos, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_088_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_088_Desc = "vs_2_0 : slt source reg combination oPos, oPts is NOT allowed";
string VS_088 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oPos, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_089_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_089_Desc = "vs_2_0 : slt source reg combination oPos, oD0 is NOT allowed";
string VS_089 = 
	"vs_2_0 "
	"slt r0, oPos, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_090_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_090_Desc = "vs_2_0 : slt source reg combination oPos, oT0 is NOT allowed";
string VS_090 = 
	"vs_2_0 "
	"slt r0, oPos, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_091_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_091_Desc = "vs_2_0 : slt source reg combination oFog, a0 is NOT allowed";
string VS_091 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, oFog, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_092_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_092_Desc = "vs_2_0 : slt source reg combination oFog, b0 is NOT allowed";
string VS_092 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, oFog, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_093_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_093_Desc = "vs_2_0 : slt source reg combination oFog, i0 is NOT allowed";
string VS_093 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, oFog, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_094_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_094_Desc = "vs_2_0 : slt source reg combination oFog, aL is NOT allowed";
string VS_094 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, oFog, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_095_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_095_Desc = "vs_2_0 : slt source reg combination oFog, oPos is NOT allowed";
string VS_095 = 
	"vs_2_0 "
	"slt r0, oFog, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_096_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_096_Desc = "vs_2_0 : slt source reg combination oFog, oFog is NOT allowed";
string VS_096 = 
	"vs_2_0 "
	"slt r0, oFog, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_097_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_097_Desc = "vs_2_0 : slt source reg combination oFog, oPts is NOT allowed";
string VS_097 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oFog, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_098_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_098_Desc = "vs_2_0 : slt source reg combination oFog, oD0 is NOT allowed";
string VS_098 = 
	"vs_2_0 "
	"slt r0, oFog, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_099_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_099_Desc = "vs_2_0 : slt source reg combination oFog, oT0 is NOT allowed";
string VS_099 = 
	"vs_2_0 "
	"slt r0, oFog, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_100_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_100_Desc = "vs_2_0 : slt source reg combination oPts, a0 is NOT allowed";
string VS_100 = 
	"vs_2_0 "
	"dcl ts "
	"mova a0.x, c0.x "
	"slt r0, oPts, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_101_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_101_Desc = "vs_2_0 : slt source reg combination oPts, b0 is NOT allowed";
string VS_101 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl ts "
	"slt r0, oPts, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_102_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_102_Desc = "vs_2_0 : slt source reg combination oPts, i0 is NOT allowed";
string VS_102 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl ts "
	"slt r0, oPts, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_103_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_103_Desc = "vs_2_0 : slt source reg combination oPts, aL is NOT allowed";
string VS_103 = 
	"vs_2_0 "
	"dcl ts "
	"mova aL.x, c0.x "
	"slt r0, oPts, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_104_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_104_Desc = "vs_2_0 : slt source reg combination oPts, oPos is NOT allowed";
string VS_104 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oPts, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_105_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_105_Desc = "vs_2_0 : slt source reg combination oPts, oFog is NOT allowed";
string VS_105 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oPts, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_106_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_106_Desc = "vs_2_0 : slt source reg combination oPts, oPts is NOT allowed";
string VS_106 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oPts, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_107_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_107_Desc = "vs_2_0 : slt source reg combination oPts, oD0 is NOT allowed";
string VS_107 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oPts, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_108_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_108_Desc = "vs_2_0 : slt source reg combination oPts, oT0 is NOT allowed";
string VS_108 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oPts, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_109_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_109_Desc = "vs_2_0 : slt source reg combination oD0, a0 is NOT allowed";
string VS_109 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, oD0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_110_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_110_Desc = "vs_2_0 : slt source reg combination oD0, b0 is NOT allowed";
string VS_110 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, oD0, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_111_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_111_Desc = "vs_2_0 : slt source reg combination oD0, i0 is NOT allowed";
string VS_111 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, oD0, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_112_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_112_Desc = "vs_2_0 : slt source reg combination oD0, aL is NOT allowed";
string VS_112 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, oD0, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_113_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_113_Desc = "vs_2_0 : slt source reg combination oD0, oPos is NOT allowed";
string VS_113 = 
	"vs_2_0 "
	"slt r0, oD0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_114_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_114_Desc = "vs_2_0 : slt source reg combination oD0, oFog is NOT allowed";
string VS_114 = 
	"vs_2_0 "
	"slt r0, oD0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_115_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_115_Desc = "vs_2_0 : slt source reg combination oD0, oPts is NOT allowed";
string VS_115 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oD0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_116_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_116_Desc = "vs_2_0 : slt source reg combination oD0, oD0 is NOT allowed";
string VS_116 = 
	"vs_2_0 "
	"slt r0, oD0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_117_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_117_Desc = "vs_2_0 : slt source reg combination oD0, oT0 is NOT allowed";
string VS_117 = 
	"vs_2_0 "
	"slt r0, oD0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_118_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_118_Desc = "vs_2_0 : slt source reg combination oT0, a0 is NOT allowed";
string VS_118 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"slt r0, oT0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_119_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_119_Desc = "vs_2_0 : slt source reg combination oT0, b0 is NOT allowed";
string VS_119 = 
	"vs_2_0 "
	"defb b0, true "
	"slt r0, oT0, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_120_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_120_Desc = "vs_2_0 : slt source reg combination oT0, i0 is NOT allowed";
string VS_120 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"slt r0, oT0, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_121_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_121_Desc = "vs_2_0 : slt source reg combination oT0, aL is NOT allowed";
string VS_121 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"slt r0, oT0, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_122_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_122_Desc = "vs_2_0 : slt source reg combination oT0, oPos is NOT allowed";
string VS_122 = 
	"vs_2_0 "
	"slt r0, oT0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_123_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_123_Desc = "vs_2_0 : slt source reg combination oT0, oFog is NOT allowed";
string VS_123 = 
	"vs_2_0 "
	"slt r0, oT0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_124_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_124_Desc = "vs_2_0 : slt source reg combination oT0, oPts is NOT allowed";
string VS_124 = 
	"vs_2_0 "
	"dcl ts "
	"slt r0, oT0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_125_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_125_Desc = "vs_2_0 : slt source reg combination oT0, oD0 is NOT allowed";
string VS_125 = 
	"vs_2_0 "
	"slt r0, oT0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_126_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_126_Desc = "vs_2_0 : slt source reg combination oT0, oT0 is NOT allowed";
string VS_126 = 
	"vs_2_0 "
	"slt r0, oT0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_127_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_127_Desc = "vs_2_0 : slt dest r# is allowed";
string VS_127 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_128_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_128_Desc = "vs_2_0 : slt dest oPos is allowed";
string VS_128 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt oPos, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_129_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_129_Desc = "vs_2_0 : slt dest oD# is allowed";
string VS_129 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt oD0, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_130_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_130_Desc = "vs_2_0 : slt dest oT# is allowed";
string VS_130 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt oT0, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_131_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_131_Desc = "vs_2_0 : slt dest v# is NOT allowed";
string VS_131 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt v0, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_132_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_132_Desc = "vs_2_0 : slt dest c# is NOT allowed";
string VS_132 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt c1, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_133_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_133_Desc = "vs_2_0 : slt dest a0 is NOT allowed";
string VS_133 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt a0, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_134_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_134_Desc = "vs_2_0 : slt dest b# is NOT allowed";
string VS_134 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt b0, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_135_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_135_Desc = "vs_2_0 : slt dest i# is NOT allowed";
string VS_135 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt i0, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_136_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_136_Desc = "vs_2_0 : slt dest aL is NOT allowed";
string VS_136 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt aL, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_137_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_137_Desc = "vs_2_0 : slt write mask .x is allowed";
string VS_137 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.x, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_138_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_138_Desc = "vs_2_0 : slt write mask .y is allowed";
string VS_138 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.y, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_139_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_139_Desc = "vs_2_0 : slt write mask .z is allowed";
string VS_139 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.z, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_140_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_140_Desc = "vs_2_0 : slt write mask .w is allowed";
string VS_140 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.w, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_141_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_141_Desc = "vs_2_0 : slt write mask .xy is allowed";
string VS_141 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.xy, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_142_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_142_Desc = "vs_2_0 : slt write mask .yz is allowed";
string VS_142 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.yz, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_143_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_143_Desc = "vs_2_0 : slt write mask .zw is allowed";
string VS_143 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.zw, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_144_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_144_Desc = "vs_2_0 : slt write mask .xz is allowed";
string VS_144 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.xz, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_145_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_145_Desc = "vs_2_0 : slt write mask .xw is allowed";
string VS_145 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.xw, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_146_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_146_Desc = "vs_2_0 : slt write mask .yw is allowed";
string VS_146 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.yw, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_147_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_147_Desc = "vs_2_0 : slt write mask .xyz is allowed";
string VS_147 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.xyz, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_148_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_148_Desc = "vs_2_0 : slt write mask .yzw is allowed";
string VS_148 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.yzw, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_149_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_149_Desc = "vs_2_0 : slt write mask .xzw is allowed";
string VS_149 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.xzw, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_150_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_150_Desc = "vs_2_0 : slt write mask .xyzw is allowed";
string VS_150 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.xyzw, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_151_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_151_Desc = "vs_2_0 : slt write mask .yx is NOT allowed";
string VS_151 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.yx, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_152_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_152_Desc = "vs_2_0 : slt write mask .zx is NOT allowed";
string VS_152 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.zx, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_153_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_153_Desc = "vs_2_0 : slt write mask .zy is NOT allowed";
string VS_153 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.zy, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_154_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_154_Desc = "vs_2_0 : slt write mask .wx is NOT allowed";
string VS_154 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.wx, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_155_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_155_Desc = "vs_2_0 : slt write mask .wz is NOT allowed";
string VS_155 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.wz, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_156_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_156_Desc = "vs_2_0 : slt write mask .wy is NOT allowed";
string VS_156 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.wy, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_157_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_157_Desc = "vs_2_0 : slt write mask .zyx is NOT allowed";
string VS_157 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.zyx, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_158_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_158_Desc = "vs_2_0 : slt write mask .wzy is NOT allowed";
string VS_158 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.wzy, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_159_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_159_Desc = "vs_2_0 : slt write mask .wzx is NOT allowed";
string VS_159 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.wzx, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_160_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_160_Desc = "vs_2_0 : slt write mask .wyx is NOT allowed";
string VS_160 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.wyx, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_161_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_161_Desc = "vs_2_0 : slt write mask .yxw is NOT allowed";
string VS_161 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.yxw, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_162_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_162_Desc = "vs_2_0 : slt write mask .wzyx is NOT allowed";
string VS_162 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.wzyx, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_163_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_163_Desc = "vs_2_0 : slt write mask .zxwy is NOT allowed";
string VS_163 = 
	"vs_2_0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"slt r0.zxwy, v0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_164_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_164_Desc = "vs_2_0 : slt is allowed in a 1 level if b0 block";
string VS_164 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	slt r0, v0, r0 "
	"endif ";

VS_CRITERIA VS_165_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_165_Desc = "vs_2_0 : slt is allowed in a 8 level if b0 block";
string VS_165 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	if b0 "
	"		if b0 "
	"			if b0 "
	"				if b0 "
	"					if b0 "
	"						if b0 "
	"							if b0 "
	"								slt r0, v0, r0 "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_166_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_166_Desc = "vs_2_0 : slt is allowed in a 16 level if b0 block";
string VS_166 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	if b0 "
	"		if b0 "
	"			if b0 "
	"				if b0 "
	"					if b0 "
	"						if b0 "
	"							if b0 "
	"								if b0 "
	"									if b0 "
	"										if b0 "
	"											if b0 "
	"												if b0 "
	"													if b0 "
	"														if b0 "
	"															if b0 "
	"																slt r0, v0, r0 "
	"															endif "
	"														endif "
	"													endif "
	"												endif "
	"											endif "
	"										endif "
	"									endif "
	"								endif "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_167_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_167_Desc = "vs_2_0 : slt is NOT allowed in a 24 level if b0 block";
string VS_167 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	if b0 "
	"		if b0 "
	"			if b0 "
	"				if b0 "
	"					if b0 "
	"						if b0 "
	"							if b0 "
	"								if b0 "
	"									if b0 "
	"										if b0 "
	"											if b0 "
	"												if b0 "
	"													if b0 "
	"														if b0 "
	"															if b0 "
	"																if b0 "
	"																	if b0 "
	"																		if b0 "
	"																			if b0 "
	"																				if b0 "
	"																					if b0 "
	"																						if b0 "
	"																							if b0 "
	"																								slt r0, v0, r0 "
	"																							endif "
	"																						endif "
	"																					endif "
	"																				endif "
	"																			endif "
	"																		endif "
	"																	endif "
	"																endif "
	"															endif "
	"														endif "
	"													endif "
	"												endif "
	"											endif "
	"										endif "
	"									endif "
	"								endif "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_168_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_168_Desc = "vs_2_0 : slt is NOT allowed in a 25 level if b0 block";
string VS_168 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	if b0 "
	"		if b0 "
	"			if b0 "
	"				if b0 "
	"					if b0 "
	"						if b0 "
	"							if b0 "
	"								if b0 "
	"									if b0 "
	"										if b0 "
	"											if b0 "
	"												if b0 "
	"													if b0 "
	"														if b0 "
	"															if b0 "
	"																if b0 "
	"																	if b0 "
	"																		if b0 "
	"																			if b0 "
	"																				if b0 "
	"																					if b0 "
	"																						if b0 "
	"																							if b0 "
	"																								if b0 "
	"																									slt r0, v0, r0 "
	"																								endif "
	"																							endif "
	"																						endif "
	"																					endif "
	"																				endif "
	"																			endif "
	"																		endif "
	"																	endif "
	"																endif "
	"															endif "
	"														endif "
	"													endif "
	"												endif "
	"											endif "
	"										endif "
	"									endif "
	"								endif "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_169_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_169_Desc = "vs_2_0 : slt is allowed in a 1 level if b0 nop else block";
string VS_169 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	slt r0, v0, r0 "
	"endif ";

VS_CRITERIA VS_170_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_170_Desc = "vs_2_0 : slt is allowed in a 8 level if b0 nop else block";
string VS_170 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	if b0 nop else "
	"		if b0 nop else "
	"			if b0 nop else "
	"				if b0 nop else "
	"					if b0 nop else "
	"						if b0 nop else "
	"							if b0 nop else "
	"								slt r0, v0, r0 "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_171_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_171_Desc = "vs_2_0 : slt is NOT allowed in a 16 level if b0 nop else block";
string VS_171 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	if b0 nop else "
	"		if b0 nop else "
	"			if b0 nop else "
	"				if b0 nop else "
	"					if b0 nop else "
	"						if b0 nop else "
	"							if b0 nop else "
	"								if b0 nop else "
	"									if b0 nop else "
	"										if b0 nop else "
	"											if b0 nop else "
	"												if b0 nop else "
	"													if b0 nop else "
	"														if b0 nop else "
	"															if b0 nop else "
	"																slt r0, v0, r0 "
	"															endif "
	"														endif "
	"													endif "
	"												endif "
	"											endif "
	"										endif "
	"									endif "
	"								endif "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_172_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_172_Desc = "vs_2_0 : slt is NOT allowed in a 24 level if b0 nop else block";
string VS_172 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	if b0 nop else "
	"		if b0 nop else "
	"			if b0 nop else "
	"				if b0 nop else "
	"					if b0 nop else "
	"						if b0 nop else "
	"							if b0 nop else "
	"								if b0 nop else "
	"									if b0 nop else "
	"										if b0 nop else "
	"											if b0 nop else "
	"												if b0 nop else "
	"													if b0 nop else "
	"														if b0 nop else "
	"															if b0 nop else "
	"																if b0 nop else "
	"																	if b0 nop else "
	"																		if b0 nop else "
	"																			if b0 nop else "
	"																				if b0 nop else "
	"																					if b0 nop else "
	"																						if b0 nop else "
	"																							if b0 nop else "
	"																								slt r0, v0, r0 "
	"																							endif "
	"																						endif "
	"																					endif "
	"																				endif "
	"																			endif "
	"																		endif "
	"																	endif "
	"																endif "
	"															endif "
	"														endif "
	"													endif "
	"												endif "
	"											endif "
	"										endif "
	"									endif "
	"								endif "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_173_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_173_Desc = "vs_2_0 : slt is NOT allowed in a 25 level if b0 nop else block";
string VS_173 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	if b0 nop else "
	"		if b0 nop else "
	"			if b0 nop else "
	"				if b0 nop else "
	"					if b0 nop else "
	"						if b0 nop else "
	"							if b0 nop else "
	"								if b0 nop else "
	"									if b0 nop else "
	"										if b0 nop else "
	"											if b0 nop else "
	"												if b0 nop else "
	"													if b0 nop else "
	"														if b0 nop else "
	"															if b0 nop else "
	"																if b0 nop else "
	"																	if b0 nop else "
	"																		if b0 nop else "
	"																			if b0 nop else "
	"																				if b0 nop else "
	"																					if b0 nop else "
	"																						if b0 nop else "
	"																							if b0 nop else "
	"																								if b0 nop else "
	"																									slt r0, v0, r0 "
	"																								endif "
	"																							endif "
	"																						endif "
	"																					endif "
	"																				endif "
	"																			endif "
	"																		endif "
	"																	endif "
	"																endif "
	"															endif "
	"														endif "
	"													endif "
	"												endif "
	"											endif "
	"										endif "
	"									endif "
	"								endif "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_174_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_174_Desc = "vs_2_0 : slt is allowed in a 1 level loop aL, i0 block";
string VS_174 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	slt r0, v0, r0 "
	"endloop ";

VS_CRITERIA VS_175_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_175_Desc = "vs_2_0 : slt is NOT allowed in a 2 level loop aL, i0 block";
string VS_175 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		slt r0, v0, r0 "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_176_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_176_Desc = "vs_2_0 : slt is NOT allowed in a 3 level loop aL, i0 block";
string VS_176 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		loop aL, i0 "
	"			slt r0, v0, r0 "
	"		endloop "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_177_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_177_Desc = "vs_2_0 : slt is NOT allowed in a 4 level loop aL, i0 block";
string VS_177 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		loop aL, i0 "
	"			loop aL, i0 "
	"				slt r0, v0, r0 "
	"			endloop "
	"		endloop "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_178_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_178_Desc = "vs_2_0 : slt is NOT allowed in a 5 level loop aL, i0 block";
string VS_178 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		loop aL, i0 "
	"			loop aL, i0 "
	"				loop aL, i0 "
	"					slt r0, v0, r0 "
	"				endloop "
	"			endloop "
	"		endloop "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_179_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_179_Desc = "vs_2_0 : slt is allowed in a 1 level rep i0 block";
string VS_179 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	slt r0, v0, r0 "
	"endrep ";

VS_CRITERIA VS_180_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_180_Desc = "vs_2_0 : slt is NOT allowed in a 2 level rep i0 block";
string VS_180 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	rep i0 "
	"		slt r0, v0, r0 "
	"	endrep "
	"endrep ";

VS_CRITERIA VS_181_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_181_Desc = "vs_2_0 : slt is NOT allowed in a 3 level rep i0 block";
string VS_181 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	rep i0 "
	"		rep i0 "
	"			slt r0, v0, r0 "
	"		endrep "
	"	endrep "
	"endrep ";

VS_CRITERIA VS_182_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_182_Desc = "vs_2_0 : slt is NOT allowed in a 4 level rep i0 block";
string VS_182 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	rep i0 "
	"		rep i0 "
	"			rep i0 "
	"				slt r0, v0, r0 "
	"			endrep "
	"		endrep "
	"	endrep "
	"endrep ";

VS_CRITERIA VS_183_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_183_Desc = "vs_2_0 : slt is NOT allowed in a 5 level rep i0 block";
string VS_183 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	rep i0 "
	"		rep i0 "
	"			rep i0 "
	"				rep i0 "
	"					slt r0, v0, r0 "
	"				endrep "
	"			endrep "
	"		endrep "
	"	endrep "
	"endrep ";

VS_CRITERIA VS_184_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_184_Desc = "vs_2_0 : slt is allowed in a if b0 and if b0 block";
string VS_184 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	if b0 "
	"		slt r0, v0, r0 "
	"	endif "
	"endif ";

VS_CRITERIA VS_185_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_185_Desc = "vs_2_0 : slt is allowed in a if b0 and if b0 nop else block";
string VS_185 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	if b0 nop else "
	"		slt r0, v0, r0 "
	"	endif "
	"endif ";

VS_CRITERIA VS_186_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_186_Desc = "vs_2_0 : slt is allowed in a if b0 and loop aL, i0 block";
string VS_186 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	loop aL, i0 "
	"		slt r0, v0, r0 "
	"	endloop "
	"endif ";

VS_CRITERIA VS_187_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_187_Desc = "vs_2_0 : slt is allowed in a if b0 and rep i0 block";
string VS_187 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 "
	"	rep i0 "
	"		slt r0, v0, r0 "
	"	endrep "
	"endif ";

VS_CRITERIA VS_188_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_188_Desc = "vs_2_0 : slt is allowed in a if b0 nop else and if b0 block";
string VS_188 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	if b0 "
	"		slt r0, v0, r0 "
	"	endif "
	"endif ";

VS_CRITERIA VS_189_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_189_Desc = "vs_2_0 : slt is allowed in a if b0 nop else and if b0 nop else block";
string VS_189 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	if b0 nop else "
	"		slt r0, v0, r0 "
	"	endif "
	"endif ";

VS_CRITERIA VS_190_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_190_Desc = "vs_2_0 : slt is allowed in a if b0 nop else and loop aL, i0 block";
string VS_190 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	loop aL, i0 "
	"		slt r0, v0, r0 "
	"	endloop "
	"endif ";

VS_CRITERIA VS_191_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_191_Desc = "vs_2_0 : slt is allowed in a if b0 nop else and rep i0 block";
string VS_191 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"dcl_depth v0 "
	"mov r0, c0 "
	"if b0 nop else "
	"	rep i0 "
	"		slt r0, v0, r0 "
	"	endrep "
	"endif ";

VS_CRITERIA VS_192_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_192_Desc = "vs_2_0 : slt is allowed in a loop aL, i0 and if b0 block";
string VS_192 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	if b0 "
	"		slt r0, v0, r0 "
	"	endif "
	"endloop ";

VS_CRITERIA VS_193_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_193_Desc = "vs_2_0 : slt is allowed in a loop aL, i0 and if b0 nop else block";
string VS_193 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	if b0 nop else "
	"		slt r0, v0, r0 "
	"	endif "
	"endloop ";

VS_CRITERIA VS_194_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_194_Desc = "vs_2_0 : slt is NOT allowed in a loop aL, i0 and loop aL, i0 block";
string VS_194 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		slt r0, v0, r0 "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_195_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_195_Desc = "vs_2_0 : slt is NOT allowed in a loop aL, i0 and rep i0 block";
string VS_195 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"loop aL, i0 "
	"	rep i0 "
	"		slt r0, v0, r0 "
	"	endrep "
	"endloop ";

VS_CRITERIA VS_196_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_196_Desc = "vs_2_0 : slt is allowed in a rep i0 and if b0 block";
string VS_196 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	if b0 "
	"		slt r0, v0, r0 "
	"	endif "
	"endrep ";

VS_CRITERIA VS_197_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_197_Desc = "vs_2_0 : slt is allowed in a rep i0 and if b0 nop else block";
string VS_197 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	if b0 nop else "
	"		slt r0, v0, r0 "
	"	endif "
	"endrep ";

VS_CRITERIA VS_198_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_198_Desc = "vs_2_0 : slt is NOT allowed in a rep i0 and loop aL, i0 block";
string VS_198 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	loop aL, i0 "
	"		slt r0, v0, r0 "
	"	endloop "
	"endrep ";

VS_CRITERIA VS_199_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_199_Desc = "vs_2_0 : slt is NOT allowed in a rep i0 and rep i0 block";
string VS_199 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_depth v0 "
	"mov r0, c0 "
	"rep i0 "
	"	rep i0 "
	"		slt r0, v0, r0 "
	"	endrep "
	"endrep ";


