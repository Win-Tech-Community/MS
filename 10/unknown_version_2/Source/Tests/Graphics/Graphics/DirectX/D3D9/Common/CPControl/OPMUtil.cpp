CRITERIA PS_079_Criteria = { true, false, 0x0104, -1, -1, -1, -1, 0, -1, 0.f };
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

PS_CRITERIA 