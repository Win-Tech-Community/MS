// Tests for Instruction: mNxN
#include "include.fx"

#define PS_SETUP \
	ps_2_x
#define SET_PRED \
	mov r0, c2 \
	setp_gt p0, r0, c0.y

// sets green, then removes green if either red or blue channels are set:
#define PS_END \
	mov r2.ga, c0.x \
	add_sat r2.g, r2.g, -r2.r \
	add_sat r2.g, r2.g, -r2.b \
	mov oC0, r2

#define SET_VS \
	VertexShaderConstant[0] = <mFinal>; \
	VertexShader = <NormalVS>;

#define SET_MAIN_PS_CONST \
	PixelShaderConstant[0] = {1.0, 0.0, 0.0009765625, 0.03125};

// Standard verify result macro, outputs to r1 0-right and 1-wrong, per component:
#define VERIFY_RESULT \
	add r1, r0, -c1 \
	cmp r1, r1, r1, -r1 \
	mov r3, c1 \
	cmp r3, r3, r3, -r3 \
	max r3, r3, c0.x \
	mul r3, r2, r3 \
	add r1, r3, -r1 \
	cmp r1, r1, c0.y, c0.x    \
	mov r2, c0.y

// The following can be used to verify each component individually, since some
// instructions or macros may write to extra components and you do not want to verify those.
#define V_X add_sat r2.r, r2.r, r1.x
#define V_Y add_sat r2.r, r2.r, r1.y
#define V_Z add_sat r2.r, r2.r, r1.z
#define V_W add_sat r2.r, r2.r, r1.w

#define USEPREDICATE bool UsePredicate = true;
#define USEARBSWZ bool UseArbSwizzle = true;
#define TESTCASE \
Technique \
< \
	String Shape = "TinyQuad"; \
	String Name = 
#define PASSBEGIN \
> \
{ \
	Pass P0 \
	{
#define TESTBEGIN \
		PixelShader = asm { \
			PS_SETUP
#define TESTEND \
			PS_END \
		}; \
		SET_VS \
		SET_MAIN_PS_CONST \
		SET_PS_CONSTANTS \
	} \
}


#define SET_PS_CONSTANTS
VertexShader NormalVS =
	asm
	{
		vs_2_0
		dcl_position	v0
		def c5, -1.8125, -1.625, 0.71875, 0.3125
		def c6, -1.15625, 1.34375, 1.71875, -1.96875
		def c7, 1.9375, 1.84375, 0.75, -1.78125
		def c8, -1.4375, 1.5625, -0.53125, 1.90625
		def c9, -1.28125, -1.46875, 1.0625, -1.90625
		def c10, 0.90625, 0.8125, 0.359375, 0.15625
		def c11, 0.578125, 0.671875, 0.859375, 0.984375
		m4x4 oPos, v0, c0
		mov oT0, c5
		mov oT1, c6
		mov oT2, c7
		mov oT3, c8
		mov oT4, c9
		mov oD0, c10
		mov oD1, c11
	};


// Tests:

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// dimensions * source registers * modifiers * swizzles
TESTCASE "mNxN - Standard (0) m4x4 r0, r4, r5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, 0.5322265625, -6.525390625, 0.2802734375, 4.876953125
	mov r4, c4
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r8, c8
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, r4, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (1) m3x4_pp r0, c4.x, t1";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -3.455078125, -8.212890625, 0.736328125, 3.05859375
	dcl t1
	dcl t2
	dcl t3
	dcl t4
	mov r0, c0.y
	mov r2, c0.w
	m3x4_pp r0, c4.x, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (2) m4x3 r0.xyz, -v0.y, c5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, 0.05078125, -2.234375, -1.21875, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	m4x3 r0.xyz, -v0.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (3) m3x3_pp r0.xyz, -t0.zxyw, r5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, 6.0595703125, 3.16796875, 3.001953125, 0.0
	dcl t0
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r0, c0.y
	mov r2, c0.w
	m3x3_pp r0.xyz, -t0.zxyw, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (4) m3x2 r0.xy, r4.xw, t1";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, 3.052734375, -2.701171875, 0.0, 0.0
	dcl t1
	dcl t2
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, r4.xw, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (5) m3x4 r0, -r4.wzx, r5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, 2.5107421875, -0.5712890625, -1.63671875, 3.3818359375
	mov r4, c4
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r8, c8
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, -r4.wzx, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (6) m4x4 r0, -c4.yzwy, t1";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -6.5810546875, -1.3056640625, -0.1953125, -4.4560546875
	dcl t1
	dcl t2
	dcl t3
	dcl t4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, -c4.yzwy, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (7) m3x3_pp r0.xyz, -v0, c5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, -0.66162109375, -3.5234375, 0.22412109375, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	m3x3_pp r0.xyz, -v0, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (8) m4x3 r0.xyz, -t0.x, r5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, -0.11328125, 4.984375, 2.71875, 0.0
	dcl t0
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, -t0.x, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (9) m3x3_pp r0.xyz, r4.y, t1";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -3.09765625, -7.36328125, 0.66015625, 0.0
	dcl t1
	dcl t2
	dcl t3
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	m3x3_pp r0.xyz, r4.y, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (10) m4x3 r0.xyz, r4.zxyw, r5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, -6.6748046875, -3.724609375, -2.40625, 0.0
	mov r4, c4
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, r4.zxyw, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (11) m4x4_pp r0, -v0.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, 0.876953125, -1.8828125, 0.84375, 1.5224609375
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	m4x4_pp r0, -v0.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (12) m3x2_pp r0.xy, t0.wzx, r5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, -2.5107421875, 0.5712890625, 0.0, 0.0
	dcl t0
	mov r5, c5
	mov r6, c6
	mov r0, c0.y
	mov r2, c0.w
	m3x2_pp r0.xy, t0.wzx, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (13) m4x3_pp r0.xyz, -r4.yzwy, t1";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -6.5810546875, -1.3056640625, -0.1953125, 0.0
	dcl t1
	dcl t2
	dcl t3
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	m4x3_pp r0.xyz, -r4.yzwy, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (14) m3x3 r0.xyz, r4.yzwy, r5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, 3.3818359375, -1.5888671875, 3.29296875, 0.0
	mov r4, c4
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, r4.yzwy, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (15) m3x2_pp r0.xy, -c4, v0";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, 2.70458984375, 1.52197265625, 0.0, 0.0
	dcl v0
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	m3x2_pp r0.xy, -c4, v0
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (16) m3x2_pp r0.xy, v0.x, c5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, 1.7275390625, 4.1064453125, 0.0, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	m3x2_pp r0.xy, v0.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (17) m3x2_pp r0.xy, r4.y, r5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, -3.09765625, -7.36328125, 0.0, 0.0
	mov r4, c4
	mov r5, c5
	mov r6, c6
	mov r0, c0.y
	mov r2, c0.w
	m3x2_pp r0.xy, r4.y, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (18) m4x4 r0, c4.zxyw, t1";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -6.6748046875, -3.724609375, -2.40625, -0.5810546875
	dcl t1
	dcl t2
	dcl t3
	dcl t4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, c4.zxyw, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (19) m4x3_pp r0.xyz, -c4.xw, t1";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -2.4375, 3.2578125, -3.5234375, 0.0
	dcl t1
	dcl t2
	dcl t3
	mov r0, c0.y
	mov r2, c0.w
	m4x3_pp r0.xyz, -c4.xw, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (20) m4x4_pp r0, -r4.wzx, t1";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -1.0576171875, -3.7998046875, 1.818359375, -0.0732421875
	dcl t1
	dcl t2
	dcl t3
	dcl t4
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	m4x4_pp r0, -r4.wzx, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (21) m3x4_pp r0, -t0, r5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, -1.1474609375, 5.96875, 0.3154296875, -5.47265625
	dcl t0
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r8, c8
	mov r0, c0.y
	mov r2, c0.w
	m3x4_pp r0, -t0, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (22) m4x4_pp r0, r4.x, t1";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, 0.11328125, -4.984375, -2.71875, 6.513671875
	dcl t1
	dcl t2
	dcl t3
	dcl t4
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	m4x4_pp r0, r4.x, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (23) m4x4_pp r0, -c4.y, t1";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -0.1015625, 4.46875, 2.4375, -5.83984375
	dcl t1
	dcl t2
	dcl t3
	dcl t4
	mov r0, c0.y
	mov r2, c0.w
	m4x4_pp r0, -c4.y, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (24) m3x4_pp r0, v0.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, 2.19873046875, 2.9765625, 0.4677734375, -0.92822265625
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	m3x4_pp r0, v0.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (25) m3x4_pp r0, -t0.xw, r5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, -3.052734375, 2.701171875, -2.927734375, -2.1953125
	dcl t0
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r8, c8
	mov r0, c0.y
	mov r2, c0.w
	m3x4_pp r0, -t0.xw, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (26) m3x3 r0.xyz, c4.wzx, t1";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -2.5107421875, 0.5712890625, 1.63671875, 0.0
	dcl t1
	dcl t2
	dcl t3
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, c4.wzx, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (27) m3x4_pp r0, -t0.yzwy, r5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, -3.3818359375, 1.5888671875, -3.29296875, -1.3583984375
	dcl t0
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r8, c8
	mov r0, c0.y
	mov r2, c0.w
	m3x4_pp r0, -t0.yzwy, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (28) m4x3 r0.xyz, -r4, t1";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -0.5322265625, 6.525390625, -0.2802734375, 0.0
	dcl t1
	dcl t2
	dcl t3
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, -r4, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (29) m3x4_pp r0, t0.y, r5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, -3.09765625, -7.36328125, 0.66015625, 2.7421875
	dcl t0
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r8, c8
	mov r0, c0.y
	mov r2, c0.w
	m3x4_pp r0, t0.y, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (30) m3x2_pp r0.xy, r4.zxyw, t1";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -6.0595703125, -3.16796875, 0.0, 0.0
	dcl t1
	dcl t2
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	m3x2_pp r0.xy, r4.zxyw, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (31) m3x3 r0.xyz, -r4.x, r5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, 3.455078125, 8.212890625, -0.736328125, 0.0
	mov r4, c4
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, -r4.x, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (32) m3x3_pp r0.xyz, -r4.xw, r5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, -3.052734375, 2.701171875, -2.927734375, 0.0
	mov r4, c4
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r0, c0.y
	mov r2, c0.w
	m3x3_pp r0.xyz, -r4.xw, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (33) m4x3_pp r0.xyz, -v0.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, -0.07568359375, -0.03076171875, -1.5830078125, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	m4x3_pp r0.xyz, -v0.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (34) m4x4 r0, -t0.x, r5";
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, -0.11328125, 4.984375, 2.71875, -6.513671875
	dcl t0
	mov r5, c5
	mov r6, c6
	mov r7, c7
	mov r8, c8
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, -t0.x, r5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (35) m3x4 r0, r4.wzx, t1";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	TESTBEGIN
	def c1, -2.5107421875, 0.5712890625, 1.63671875, -3.3818359375
	dcl t1
	dcl t2
	dcl t3
	dcl t4
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, r4.wzx, t1
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Standard (36) m3x2_pp r0.xy, -v0.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, 0.18798828125, -2.35400390625, 0.0, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	m3x2_pp r0.xy, -v0.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// dimensions * values
TESTCASE "mNxN - Values (0) m4x4 r0, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, -0.125};
	TESTBEGIN
	def c1, -3.2919921875, -7.7861328125, 22.4609375, 7.833984375
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (1) m3x4 r0, r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 0};
	TESTBEGIN
	def c1, -11.2734375, 10.40625, -19.294921875, -11.70703125
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (2) m4x3 r0.xyz, -r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, 5.365234375, -6.646484375, 7.607421875, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, -r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (3) m3x3 r0.xyz, -r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	TESTBEGIN
	def c1, -10.6083984375, -9.060546875, 3.2177734375, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, -r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (4) m3x2 r0.xy, r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, -3.1748046875, -15.1494140625, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (5) m4x4 r0, -r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 2.4375};
	TESTBEGIN
	def c1, 9.333984375, -16.646484375, 1.5205078125, -14.0087890625
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, -r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (6) m3x4 r0, -r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, 0};
	TESTBEGIN
	def c1, -7.5009765625, 5.78125, -0.9716796875, 21.7197265625
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, -r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (7) m4x3 r0.xyz, -r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, 4.9423828125, -1.6259765625, 16.01953125, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, -r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (8) m3x3 r0.xyz, -r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	TESTBEGIN
	def c1, 2.2099609375, 9.7666015625, -8.412109375, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, -r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (9) m3x2 r0.xy, r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 0.6357421875, 2.8095703125, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (10) m4x3 r0.xyz, r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, -4.1875, 5.587890625, -8.7880859375, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (11) m3x3 r0.xyz, -r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	TESTBEGIN
	def c1, -15.291015625, 19.5283203125, -11.234375, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, -r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (12) m3x2 r0.xy, r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 0.5556640625, -9.5595703125, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (13) m3x2 r0.xy, -r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	TESTBEGIN
	def c1, -0.47265625, 4.4677734375, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, -r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (14) m4x3 r0.xyz, r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	TESTBEGIN
	def c1, 17.2421875, 1.05859375, 3.9638671875, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (15) m3x3 r0.xyz, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	TESTBEGIN
	def c1, -6.5029296875, 6.04296875, -2.212890625, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (16) m3x4 r0, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, 0};
	TESTBEGIN
	def c1, 11.3564453125, 0.392578125, 10.25390625, 7.345703125
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (17) m3x2 r0.xy, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 11.3564453125, 0.392578125, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (18) m4x4 r0, r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, -0.125};
	TESTBEGIN
	def c1, 16.3681640625, 22.11328125, -23.630859375, 17.8857421875
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (19) m4x3 r0.xyz, -r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	TESTBEGIN
	def c1, 10.7646484375, 14.54296875, -15.541015625, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, -r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (20) m3x2 r0.xy, -r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 2.2099609375, 9.7666015625, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, -r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (21) m4x4 r0, -r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 2.4375};
	TESTBEGIN
	def c1, 5.365234375, -6.646484375, 7.607421875, 2.40234375
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, -r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (22) m3x4 r0, -r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 0};
	TESTBEGIN
	def c1, 8.328125, -7.6875, 14.25390625, 8.6484375
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, -r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (23) m3x3 r0.xyz, r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	TESTBEGIN
	def c1, 0.6357421875, 2.8095703125, -2.419921875, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (24) m4x4 r0, r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 2.4375};
	TESTBEGIN
	def c1, -11.375, 6.9111328125, -19.451171875, -21.1572265625
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (25) m3x4 r0, r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, 0};
	TESTBEGIN
	def c1, -15.306640625, -1.380859375, -4.1357421875, 3.4052734375
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (26) m3x2 r0.xy, r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	TESTBEGIN
	def c1, 0.3291015625, 4.0009765625, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (27) m4x4 r0, -r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, -0.125};
	TESTBEGIN
	def c1, 17.8232421875, 23.328125, -22.701171875, 22.5791015625
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, -r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (28) m3x4 r0, r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 0};
	TESTBEGIN
	def c1, 15.291015625, -19.5283203125, 11.234375, -2.3896484375
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (29) m4x3 r0.xyz, -r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, -11.966796875, 18.3603515625, -3.77734375, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, -r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (30) m3x4 r0, -r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, 0};
	TESTBEGIN
	def c1, 4.1865234375, -5.9775390625, -1.2294921875, -22.810546875
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, -r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (31) m4x3 r0.xyz, -r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	TESTBEGIN
	def c1, 7.9990234375, 14.3359375, -20.263671875, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, -r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (32) m3x3 r0.xyz, -r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	TESTBEGIN
	def c1, 4.1865234375, -5.9775390625, -1.2294921875, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, -r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (33) m4x4 r0, -r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 2.4375};
	TESTBEGIN
	def c1, -15.078125, 18.2998046875, -16.6328125, 1.7607421875
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, -r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Values (34) m3x3 r0.xyz, -r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	TESTBEGIN
	def c1, -12.115234375, 17.2587890625, -9.986328125, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, -r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// dimensions * values
TESTCASE "mNxN - sat (0) m4x4_sat r0, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, -0.125};
	TESTBEGIN
	def c1, 0.0, 0.0, 1.0, 1.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4_sat r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (1) m3x4_sat r0, r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 0};
	TESTBEGIN
	def c1, 0.0, 1.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4_sat r0, r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (2) m4x3_sat r0.xyz, -r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3_sat r0.xyz, -r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (3) m3x3_sat r0.xyz, -r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3_sat r0.xyz, -r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (4) m3x2_sat r0.xy, r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2_sat r0.xy, r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (5) m4x4_sat r0, -r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 2.4375};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4_sat r0, -r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (6) m3x4_sat r0, -r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, 0};
	TESTBEGIN
	def c1, 0.0, 1.0, 0.0, 1.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4_sat r0, -r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (7) m4x3_sat r0.xyz, -r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3_sat r0.xyz, -r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (8) m3x3_sat r0.xyz, -r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	TESTBEGIN
	def c1, 1.0, 1.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3_sat r0.xyz, -r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (9) m3x2_sat r0.xy, r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 0.6357421875, 1.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2_sat r0.xy, r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (10) m4x3_sat r0.xyz, r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, 0.0, 1.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3_sat r0.xyz, r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (11) m3x3_sat r0.xyz, -r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	TESTBEGIN
	def c1, 0.0, 1.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3_sat r0.xyz, -r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (12) m3x2_sat r0.xy, r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 0.5556640625, 0.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2_sat r0.xy, r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (13) m3x2_sat r0.xy, -r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	TESTBEGIN
	def c1, 0.0, 1.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2_sat r0.xy, -r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (14) m4x3_sat r0.xyz, r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	TESTBEGIN
	def c1, 1.0, 0.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3_sat r0.xyz, r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (15) m3x3_sat r0.xyz, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	TESTBEGIN
	def c1, 0.0, 0.4580078125, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3_sat r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (16) m3x4_sat r0, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, 0};
	TESTBEGIN
	def c1, 1.0, 0.392578125, 1.0, 1.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4_sat r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (17) m3x2_sat r0.xy, -r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2_sat r0.xy, -r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (18) m4x4_sat r0, -r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 2.4375};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 1.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4_sat r0, -r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (19) m4x3_sat r0.xyz, r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, 0.0, 1.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3_sat r0.xyz, r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (20) m3x2_sat r0.xy, r4.x, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2_sat r0.xy, r4.x, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (21) m4x4_sat r0, -r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, -0.125};
	TESTBEGIN
	def c1, 0.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4_sat r0, -r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (22) m3x4_sat r0, r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 0};
	TESTBEGIN
	def c1, 0.0, 1.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4_sat r0, r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (23) m3x3_sat r0.xyz, -r4.y, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3_sat r0.xyz, -r4.y, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (24) m4x4_sat r0, -r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 2.4375};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4_sat r0, -r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (25) m3x4_sat r0, -r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 0};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 1.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4_sat r0, -r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (26) m3x2_sat r0.xy, -r4.zxyw, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2_sat r0.xy, -r4.zxyw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (27) m4x4_sat r0, -r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, -0.125};
	TESTBEGIN
	def c1, 1.0, 1.0, 0.0, 1.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4_sat r0, -r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (28) m3x4_sat r0, -r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 0};
	TESTBEGIN
	def c1, 0.0, 1.0, 0.0, 1.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4_sat r0, -r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (29) m4x3_sat r0.xyz, r4.xw, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	TESTBEGIN
	def c1, 0.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3_sat r0.xyz, r4.xw, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (30) m3x4_sat r0, -r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	PixelShaderConstantF[8] = {-1.90625, -3.375, 1.90625, 0};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4_sat r0, -r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (31) m4x3_sat r0.xyz, -r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 1.15625};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, -0.40625};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 2.59375};
	TESTBEGIN
	def c1, 0.0, 0.9990234375, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3_sat r0.xyz, -r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (32) m3x3_sat r0.xyz, -r4.wzx, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {3.46875, 0.65625, 1.9375, -2.875};
	PixelShaderConstantF[5] = {0.9375, -2.53125, -1.65625, 0};
	PixelShaderConstantF[6] = {-1.71875, 2.125, 2.59375, 0};
	PixelShaderConstantF[7] = {-0.75, -2.625, -2.1875, 0};
	TESTBEGIN
	def c1, 1.0, 0.0, 1.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3_sat r0.xyz, -r4.wzx, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (33) m4x4_sat r0, r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 3.75};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 2.09375};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, -3.125};
	PixelShaderConstantF[8] = {-1.5, 3.28125, 3.5, -0.125};
	TESTBEGIN
	def c1, 1.0, 0.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4_sat r0, r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - sat (34) m3x3_sat r0.xyz, r4.yzwy, c5";
	USEARBSWZ
	PASSBEGIN
	PixelShaderConstantF[4] = {-2.28125, 2.5625, -1.28125, -3.90625};
	PixelShaderConstantF[5] = {0.375, 3.375, -2.78125, 0};
	PixelShaderConstantF[6] = {0.96875, 1.78125, 1.53125, 0};
	PixelShaderConstantF[7] = {-2.40625, 0.8125, -2.09375, 0};
	TESTBEGIN
	def c1, 1.0, 0.0, 0.9716796875, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3_sat r0.xyz, r4.yzwy, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// dimensions * predication
TESTCASE "mNxN - Pred (0) m4x4 r0, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, 0.5322265625, -6.525390625, 0.2802734375, 4.876953125
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (1) (p0.x) m3x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, -0.3154296875, 5.47265625
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.x) m3x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (2) (p0.y) m4x3 r0.xyz, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, 0.5322265625, -6.525390625, 0.2802734375, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.y) m4x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (3) (p0.z) m3x3 r0.xyz, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, -0.3154296875, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.z) m3x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (4) (p0.w) m3x2 r0.xy, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.w) m3x2 r0.xy, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (5) m4x3 r0.xyz, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, 0.5322265625, -6.525390625, 0.2802734375, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m4x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (6) (!p0) m3x3 r0.xyz, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, 0.0, -5.96875, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0) m3x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (7) (!p0.z) m4x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, 0.5322265625, -6.525390625, 0.2802734375, 4.876953125
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0.z) m4x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (8) (!p0.y) m3x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0.y) m3x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (9) m3x4 r0, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, -0.3154296875, 5.47265625
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (10) (!p0) m3x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, -0.3154296875, 5.47265625
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0) m3x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (11) (!p0.y) m3x2 r0.xy, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0.y) m3x2 r0.xy, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (12) (p0.x) m3x3 r0.xyz, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.x) m3x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (13) (!p0.w) m4x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0.w) m4x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (14) (p0.z) m4x3 r0.xyz, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.z) m4x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (15) m3x3 r0.xyz, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, -0.3154296875, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (16) (!p0.z) m4x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0.z) m4x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (17) (!p0) m3x2 r0.xy, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, 1.1474609375, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0) m3x2 r0.xy, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (18) (p0.x) m3x2 r0.xy, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.x) m3x2 r0.xy, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (19) (p0.w) m4x3 r0.xyz, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.w) m4x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (20) (!p0) m4x3 r0.xyz, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0) m4x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (21) (!p0.x) m4x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, 0.5322265625, -6.525390625, 0.2802734375, 4.876953125
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0.x) m4x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (22) m3x4 r0, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, -0.3154296875, 5.47265625
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (23) (p0.w) m3x3 r0.xyz, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.w) m3x3 r0.xyz, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (24) (p0.y) m4x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, -1.96875};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, -1.78125};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 1.90625};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, -1.90625};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(p0.y) m4x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (25) m3x2 r0.xy, r4, c5";
	PASSBEGIN
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	TESTBEGIN
	def c1, 1.1474609375, -5.96875, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	m3x2 r0.xy, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "mNxN - Pred (26) (!p0.w) m3x4 r0, r4, c5";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	PixelShaderConstantF[4] = {-1.8125, -1.625, 0.71875, 0.3125};
	PixelShaderConstantF[5] = {-1.15625, 1.34375, 1.71875, 0};
	PixelShaderConstantF[6] = {1.9375, 1.84375, 0.75, 0};
	PixelShaderConstantF[7] = {-1.4375, 1.5625, -0.53125, 0};
	PixelShaderConstantF[8] = {-1.28125, -1.46875, 1.0625, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	(!p0.w) m3x4 r0, r4, c5
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



// End of file.  134 tests generated.