#include "Test_Include.fx"

int Test_Count = 103;

string TestInfo
<
	string TestType = "VS";
>
= "vs_2_0_inst_lit";

VS_CRITERIA VS_001_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_001_Desc = "vs_2_0 : lit source reg combination v0 is allowed";
string VS_001 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_002_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_002_Desc = "vs_2_0 : lit source reg combination r0 is allowed";
string VS_002 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_003_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_003_Desc = "vs_2_0 : lit source reg combination c0 is allowed";
string VS_003 = 
	"vs_2_0 "
	"def c0, 1, 1, 1, 1 "
	"lit r0, c0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_004_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_004_Desc = "vs_2_0 : lit source reg combination -r0 is allowed";
string VS_004 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, -r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_005_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_005_Desc = "vs_2_0 : lit source reg combination r0 is allowed";
string VS_005 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_006_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_006_Desc = "vs_2_0 : lit source reg combination r0.x is allowed";
string VS_006 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.x "
	"mov oPos, c0 ";

VS_CRITERIA VS_007_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_007_Desc = "vs_2_0 : lit source reg combination r0.y is allowed";
string VS_007 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.y "
	"mov oPos, c0 ";

VS_CRITERIA VS_008_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_008_Desc = "vs_2_0 : lit source reg combination r0.z is allowed";
string VS_008 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.z "
	"mov oPos, c0 ";

VS_CRITERIA VS_009_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_009_Desc = "vs_2_0 : lit source reg combination r0.w is allowed";
string VS_009 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.w "
	"mov oPos, c0 ";

VS_CRITERIA VS_010_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_010_Desc = "vs_2_0 : lit source reg combination r0.yzxw is allowed";
string VS_010 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.yzxw "
	"mov oPos, c0 ";

VS_CRITERIA VS_011_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_011_Desc = "vs_2_0 : lit source reg combination r0.zxyw is allowed";
string VS_011 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.zxyw "
	"mov oPos, c0 ";

VS_CRITERIA VS_012_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_012_Desc = "vs_2_0 : lit source reg combination r0.wzyx is allowed";
string VS_012 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.wzyx "
	"mov oPos, c0 ";

VS_CRITERIA VS_013_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_013_Desc = "vs_2_0 : lit source reg combination r0.wyxz is allowed";
string VS_013 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.wyxz "
	"mov oPos, c0 ";

VS_CRITERIA VS_014_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_014_Desc = "vs_2_0 : lit source reg combination r0.xzyw is allowed";
string VS_014 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.xzyw "
	"mov oPos, c0 ";

VS_CRITERIA VS_015_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_015_Desc = "vs_2_0 : lit source reg combination r0.xywz is allowed";
string VS_015 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.xywz "
	"mov oPos, c0 ";

VS_CRITERIA VS_016_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_016_Desc = "vs_2_0 : lit source reg combination r0.zyx is allowed";
string VS_016 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.zyx "
	"mov oPos, c0 ";

VS_CRITERIA VS_017_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_017_Desc = "vs_2_0 : lit source reg combination r0.xzy is allowed";
string VS_017 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.xzy "
	"mov oPos, c0 ";

VS_CRITERIA VS_018_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_018_Desc = "vs_2_0 : lit source reg combination r0.ywx is allowed";
string VS_018 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.ywx "
	"mov oPos, c0 ";

VS_CRITERIA VS_019_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_019_Desc = "vs_2_0 : lit source reg combination r0.yx is allowed";
string VS_019 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.yx "
	"mov oPos, c0 ";

VS_CRITERIA VS_020_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_020_Desc = "vs_2_0 : lit source reg combination r0.wz is allowed";
string VS_020 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.wz "
	"mov oPos, c0 ";

VS_CRITERIA VS_021_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_021_Desc = "vs_2_0 : lit source reg combination r0.zy is allowed";
string VS_021 = 
	"vs_2_0 "
	"mov r0, c0 "
	"lit r0, r0.zy "
	"mov oPos, c0 ";

VS_CRITERIA VS_022_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_022_Desc = "vs_2_0 : lit source reg combination a0 is NOT allowed";
string VS_022 = 
	"vs_2_0 "
	"mova a0.x, c0.x "
	"lit r0, a0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_023_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_023_Desc = "vs_2_0 : lit source reg combination b0 is NOT allowed";
string VS_023 = 
	"vs_2_0 "
	"defb b0, true "
	"lit r0, b0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_024_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_024_Desc = "vs_2_0 : lit source reg combination i0 is NOT allowed";
string VS_024 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"lit r0, i0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_025_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_025_Desc = "vs_2_0 : lit source reg combination aL is NOT allowed";
string VS_025 = 
	"vs_2_0 "
	"mova aL.x, c0.x "
	"lit r0, aL "
	"mov oPos, c0 ";

VS_CRITERIA VS_026_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_026_Desc = "vs_2_0 : lit source reg combination oPos is NOT allowed";
string VS_026 = 
	"vs_2_0 "
	"lit r0, oPos "
	"mov oPos, c0 ";

VS_CRITERIA VS_027_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_027_Desc = "vs_2_0 : lit source reg combination oFog is NOT allowed";
string VS_027 = 
	"vs_2_0 "
	"lit r0, oFog "
	"mov oPos, c0 ";

VS_CRITERIA VS_028_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_028_Desc = "vs_2_0 : lit source reg combination oPts is NOT allowed";
string VS_028 = 
	"vs_2_0 "
	"dcl ts "
	"lit r0, oPts "
	"mov oPos, c0 ";

VS_CRITERIA VS_029_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_029_Desc = "vs_2_0 : lit source reg combination oD0 is NOT allowed";
string VS_029 = 
	"vs_2_0 "
	"lit r0, oD0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_030_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_030_Desc = "vs_2_0 : lit source reg combination oT0 is NOT allowed";
string VS_030 = 
	"vs_2_0 "
	"lit r0, oT0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_031_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_031_Desc = "vs_2_0 : lit dest r# is allowed";
string VS_031 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_032_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_032_Desc = "vs_2_0 : lit dest oPos is allowed";
string VS_032 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit oPos, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_033_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_033_Desc = "vs_2_0 : lit dest oD# is allowed";
string VS_033 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit oD0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_034_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_034_Desc = "vs_2_0 : lit dest oT# is allowed";
string VS_034 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit oT0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_035_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_035_Desc = "vs_2_0 : lit dest v# is NOT allowed";
string VS_035 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit v0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_036_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_036_Desc = "vs_2_0 : lit dest c# is NOT allowed";
string VS_036 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit c1, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_037_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_037_Desc = "vs_2_0 : lit dest a0 is NOT allowed";
string VS_037 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit a0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_038_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_038_Desc = "vs_2_0 : lit dest b# is NOT allowed";
string VS_038 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit b0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_039_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_039_Desc = "vs_2_0 : lit dest i# is NOT allowed";
string VS_039 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit i0, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_040_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_040_Desc = "vs_2_0 : lit dest aL is NOT allowed";
string VS_040 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit aL, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_041_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_041_Desc = "vs_2_0 : lit write mask .x is allowed";
string VS_041 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.x, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_042_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_042_Desc = "vs_2_0 : lit write mask .y is allowed";
string VS_042 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.y, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_043_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_043_Desc = "vs_2_0 : lit write mask .z is allowed";
string VS_043 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.z, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_044_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_044_Desc = "vs_2_0 : lit write mask .w is allowed";
string VS_044 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.w, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_045_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_045_Desc = "vs_2_0 : lit write mask .xy is allowed";
string VS_045 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.xy, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_046_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_046_Desc = "vs_2_0 : lit write mask .yz is allowed";
string VS_046 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.yz, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_047_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_047_Desc = "vs_2_0 : lit write mask .zw is allowed";
string VS_047 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.zw, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_048_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_048_Desc = "vs_2_0 : lit write mask .xz is allowed";
string VS_048 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.xz, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_049_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_049_Desc = "vs_2_0 : lit write mask .xw is allowed";
string VS_049 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.xw, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_050_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_050_Desc = "vs_2_0 : lit write mask .yw is allowed";
string VS_050 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.yw, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_051_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_051_Desc = "vs_2_0 : lit write mask .xyz is allowed";
string VS_051 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.xyz, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_052_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_052_Desc = "vs_2_0 : lit write mask .yzw is allowed";
string VS_052 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.yzw, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_053_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_053_Desc = "vs_2_0 : lit write mask .xzw is allowed";
string VS_053 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.xzw, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_054_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_054_Desc = "vs_2_0 : lit write mask .xyzw is allowed";
string VS_054 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.xyzw, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_055_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_055_Desc = "vs_2_0 : lit write mask .yx is NOT allowed";
string VS_055 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.yx, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_056_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_056_Desc = "vs_2_0 : lit write mask .zx is NOT allowed";
string VS_056 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.zx, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_057_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_057_Desc = "vs_2_0 : lit write mask .zy is NOT allowed";
string VS_057 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.zy, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_058_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_058_Desc = "vs_2_0 : lit write mask .wx is NOT allowed";
string VS_058 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.wx, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_059_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_059_Desc = "vs_2_0 : lit write mask .wz is NOT allowed";
string VS_059 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.wz, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_060_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_060_Desc = "vs_2_0 : lit write mask .wy is NOT allowed";
string VS_060 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.wy, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_061_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_061_Desc = "vs_2_0 : lit write mask .zyx is NOT allowed";
string VS_061 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.zyx, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_062_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_062_Desc = "vs_2_0 : lit write mask .wzy is NOT allowed";
string VS_062 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.wzy, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_063_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_063_Desc = "vs_2_0 : lit write mask .wzx is NOT allowed";
string VS_063 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.wzx, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_064_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_064_Desc = "vs_2_0 : lit write mask .wyx is NOT allowed";
string VS_064 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.wyx, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_065_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_065_Desc = "vs_2_0 : lit write mask .yxw is NOT allowed";
string VS_065 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.yxw, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_066_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_066_Desc = "vs_2_0 : lit write mask .wzyx is NOT allowed";
string VS_066 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.wzyx, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_067_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_067_Desc = "vs_2_0 : lit write mask .zxwy is NOT allowed";
string VS_067 = 
	"vs_2_0 "
	"dcl_fog v0 "
	"lit r0.zxwy, v0 "
	"mov oPos, c0 ";

VS_CRITERIA VS_068_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_068_Desc = "vs_2_0 : lit is allowed in a 1 level if b0 block";
string VS_068 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 "
	"	lit r0, v0 "
	"endif ";

VS_CRITERIA VS_069_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_069_Desc = "vs_2_0 : lit is allowed in a 8 level if b0 block";
string VS_069 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 "
	"	if b0 "
	"		if b0 "
	"			if b0 "
	"				if b0 "
	"					if b0 "
	"						if b0 "
	"							if b0 "
	"								lit r0, v0 "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_070_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_070_Desc = "vs_2_0 : lit is allowed in a 16 level if b0 block";
string VS_070 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
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
	"																lit r0, v0 "
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

VS_CRITERIA VS_071_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_071_Desc = "vs_2_0 : lit is NOT allowed in a 24 level if b0 block";
string VS_071 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
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
	"																								lit r0, v0 "
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

VS_CRITERIA VS_072_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_072_Desc = "vs_2_0 : lit is NOT allowed in a 25 level if b0 block";
string VS_072 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
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
	"																									lit r0, v0 "
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

VS_CRITERIA VS_073_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_073_Desc = "vs_2_0 : lit is allowed in a 1 level if b0 nop else block";
string VS_073 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 nop else "
	"	lit r0, v0 "
	"endif ";

VS_CRITERIA VS_074_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_074_Desc = "vs_2_0 : lit is allowed in a 8 level if b0 nop else block";
string VS_074 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 nop else "
	"	if b0 nop else "
	"		if b0 nop else "
	"			if b0 nop else "
	"				if b0 nop else "
	"					if b0 nop else "
	"						if b0 nop else "
	"							if b0 nop else "
	"								lit r0, v0 "
	"							endif "
	"						endif "
	"					endif "
	"				endif "
	"			endif "
	"		endif "
	"	endif "
	"endif ";

VS_CRITERIA VS_075_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_075_Desc = "vs_2_0 : lit is NOT allowed in a 16 level if b0 nop else block";
string VS_075 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
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
	"																lit r0, v0 "
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

VS_CRITERIA VS_076_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_076_Desc = "vs_2_0 : lit is NOT allowed in a 24 level if b0 nop else block";
string VS_076 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
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
	"																								lit r0, v0 "
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

VS_CRITERIA VS_077_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_077_Desc = "vs_2_0 : lit is NOT allowed in a 25 level if b0 nop else block";
string VS_077 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
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
	"																									lit r0, v0 "
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

VS_CRITERIA VS_078_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_078_Desc = "vs_2_0 : lit is allowed in a 1 level loop aL, i0 block";
string VS_078 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	lit r0, v0 "
	"endloop ";

VS_CRITERIA VS_079_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_079_Desc = "vs_2_0 : lit is NOT allowed in a 2 level loop aL, i0 block";
string VS_079 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		lit r0, v0 "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_080_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_080_Desc = "vs_2_0 : lit is NOT allowed in a 3 level loop aL, i0 block";
string VS_080 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		loop aL, i0 "
	"			lit r0, v0 "
	"		endloop "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_081_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_081_Desc = "vs_2_0 : lit is NOT allowed in a 4 level loop aL, i0 block";
string VS_081 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		loop aL, i0 "
	"			loop aL, i0 "
	"				lit r0, v0 "
	"			endloop "
	"		endloop "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_082_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_082_Desc = "vs_2_0 : lit is NOT allowed in a 5 level loop aL, i0 block";
string VS_082 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		loop aL, i0 "
	"			loop aL, i0 "
	"				loop aL, i0 "
	"					lit r0, v0 "
	"				endloop "
	"			endloop "
	"		endloop "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_083_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_083_Desc = "vs_2_0 : lit is allowed in a 1 level rep i0 block";
string VS_083 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	lit r0, v0 "
	"endrep ";

VS_CRITERIA VS_084_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_084_Desc = "vs_2_0 : lit is NOT allowed in a 2 level rep i0 block";
string VS_084 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	rep i0 "
	"		lit r0, v0 "
	"	endrep "
	"endrep ";

VS_CRITERIA VS_085_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_085_Desc = "vs_2_0 : lit is NOT allowed in a 3 level rep i0 block";
string VS_085 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	rep i0 "
	"		rep i0 "
	"			lit r0, v0 "
	"		endrep "
	"	endrep "
	"endrep ";

VS_CRITERIA VS_086_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_086_Desc = "vs_2_0 : lit is NOT allowed in a 4 level rep i0 block";
string VS_086 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	rep i0 "
	"		rep i0 "
	"			rep i0 "
	"				lit r0, v0 "
	"			endrep "
	"		endrep "
	"	endrep "
	"endrep ";

VS_CRITERIA VS_087_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_087_Desc = "vs_2_0 : lit is NOT allowed in a 5 level rep i0 block";
string VS_087 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	rep i0 "
	"		rep i0 "
	"			rep i0 "
	"				rep i0 "
	"					lit r0, v0 "
	"				endrep "
	"			endrep "
	"		endrep "
	"	endrep "
	"endrep ";

VS_CRITERIA VS_088_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_088_Desc = "vs_2_0 : lit is allowed in a if b0 and if b0 block";
string VS_088 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 "
	"	if b0 "
	"		lit r0, v0 "
	"	endif "
	"endif ";

VS_CRITERIA VS_089_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_089_Desc = "vs_2_0 : lit is allowed in a if b0 and if b0 nop else block";
string VS_089 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 "
	"	if b0 nop else "
	"		lit r0, v0 "
	"	endif "
	"endif ";

VS_CRITERIA VS_090_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_090_Desc = "vs_2_0 : lit is allowed in a if b0 and loop aL, i0 block";
string VS_090 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 "
	"	loop aL, i0 "
	"		lit r0, v0 "
	"	endloop "
	"endif ";

VS_CRITERIA VS_091_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_091_Desc = "vs_2_0 : lit is allowed in a if b0 and rep i0 block";
string VS_091 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 "
	"	rep i0 "
	"		lit r0, v0 "
	"	endrep "
	"endif ";

VS_CRITERIA VS_092_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_092_Desc = "vs_2_0 : lit is allowed in a if b0 nop else and if b0 block";
string VS_092 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 nop else "
	"	if b0 "
	"		lit r0, v0 "
	"	endif "
	"endif ";

VS_CRITERIA VS_093_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_093_Desc = "vs_2_0 : lit is allowed in a if b0 nop else and if b0 nop else block";
string VS_093 = 
	"vs_2_0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 nop else "
	"	if b0 nop else "
	"		lit r0, v0 "
	"	endif "
	"endif ";

VS_CRITERIA VS_094_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_094_Desc = "vs_2_0 : lit is allowed in a if b0 nop else and loop aL, i0 block";
string VS_094 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 nop else "
	"	loop aL, i0 "
	"		lit r0, v0 "
	"	endloop "
	"endif ";

VS_CRITERIA VS_095_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_095_Desc = "vs_2_0 : lit is allowed in a if b0 nop else and rep i0 block";
string VS_095 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"defb b0, true "
	"dcl_fog v0 "
	"if b0 nop else "
	"	rep i0 "
	"		lit r0, v0 "
	"	endrep "
	"endif ";

VS_CRITERIA VS_096_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_096_Desc = "vs_2_0 : lit is allowed in a loop aL, i0 and if b0 block";
string VS_096 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	if b0 "
	"		lit r0, v0 "
	"	endif "
	"endloop ";

VS_CRITERIA VS_097_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_097_Desc = "vs_2_0 : lit is allowed in a loop aL, i0 and if b0 nop else block";
string VS_097 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	if b0 nop else "
	"		lit r0, v0 "
	"	endif "
	"endloop ";

VS_CRITERIA VS_098_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_098_Desc = "vs_2_0 : lit is NOT allowed in a loop aL, i0 and loop aL, i0 block";
string VS_098 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	loop aL, i0 "
	"		lit r0, v0 "
	"	endloop "
	"endloop ";

VS_CRITERIA VS_099_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_099_Desc = "vs_2_0 : lit is NOT allowed in a loop aL, i0 and rep i0 block";
string VS_099 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"loop aL, i0 "
	"	rep i0 "
	"		lit r0, v0 "
	"	endrep "
	"endloop ";

VS_CRITERIA VS_100_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_100_Desc = "vs_2_0 : lit is allowed in a rep i0 and if b0 block";
string VS_100 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	if b0 "
	"		lit r0, v0 "
	"	endif "
	"endrep ";

VS_CRITERIA VS_101_Criteria = { true, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_101_Desc = "vs_2_0 : lit is allowed in a rep i0 and if b0 nop else block";
string VS_101 = 
	"vs_2_0 "
	"defb b0, true "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	if b0 nop else "
	"		lit r0, v0 "
	"	endif "
	"endrep ";

VS_CRITERIA VS_102_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_102_Desc = "vs_2_0 : lit is NOT allowed in a rep i0 and loop aL, i0 block";
string VS_102 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	loop aL, i0 "
	"		lit r0, v0 "
	"	endloop "
	"endrep ";

VS_CRITERIA VS_103_Criteria = { false, false, 0x0200, -1, -1, -1, -1, 0, -1, 0.f };
string VS_103_Desc = "vs_2_0 : lit is NOT allowed in a rep i0 and rep i0 block";
string VS_103 = 
	"vs_2_0 "
	"defi i0, 0, 0, 0, 0 "
	"dcl_fog v0 "
	"rep i0 "
	"	rep i0 "
	"		lit r0, v0 "
	"	endrep "
	"endrep ";


