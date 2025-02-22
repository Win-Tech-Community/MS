// Tests for Instruction: rsq
#include "include.fx"

#define PS_SETUP \
	ps_2_0
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

#define TESTCASE \
Technique \
< \
	String Name =
#define PASSBEGIN \
	; \
	String Shape = "TinyQuad"; \
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


#define SET_PS_CONSTANTS \
	PixelShaderConstantF[4] = {-0.46875, -1.78125, 1.34375, 1.96875};

VertexShader NormalVS =
	asm
	{
		vs_2_0
		dcl_position	v0
		def c5, -0.46875, -1.78125, 1.34375, 1.96875
		def c6, 0.34375, 0.125, 0.5, 0.609375
		m4x4 oPos, v0, c0
		mov oT0, c5
		mov oD0, c6
	};


// Tests:

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// source registers * modifiers * swizzles
TESTCASE "rsq - Standard (0) rsq r0, r4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.46059348668, 1.46059348668, 1.46059348668, 1.46059348668
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0, r4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (1) rsq_pp r0, c4.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.749268649265, 0.749268649265, 0.749268649265
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, c4.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (2) rsq r0, -v0.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.41421356237, 1.41421356237, 1.41421356237, 1.41421356237
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0, -v0.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (3) rsq_pp r0, -t0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.7126966451, 0.7126966451
	dcl t0
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, -t0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (4) rsq_pp r0, -c4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.46059348668, 1.46059348668, 1.46059348668, 1.46059348668
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, -c4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (5) rsq_pp r0, -r4.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.749268649265, 0.749268649265, 0.749268649265
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, -r4.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (6) rsq r0, t0.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.862662185628, 0.862662185628
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0, t0.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (7) rsq r0, v0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.28102523044, 1.28102523044, 1.28102523044, 1.28102523044
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0, v0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (8) rsq r0, v0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 2.82842712475, 2.82842712475, 2.82842712475, 2.82842712475
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0, v0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (9) rsq r0, -c4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.862662185628, 0.862662185628
	mov r0, c0.y
	mov r2, c0.z
	rsq r0, -c4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (10) rsq_pp r0, v0.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.70560573084, 1.70560573084, 1.70560573084, 1.70560573084
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, v0.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (11) rsq_pp r0, r4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.862662185628, 0.862662185628
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, r4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (12) rsq_pp r0, -t0.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.46059348668, 1.46059348668, 1.46059348668, 1.46059348668
	dcl t0
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, -t0.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (13) rsq_pp r0, t0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.749268649265, 0.749268649265, 0.749268649265
	dcl t0
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, t0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (14) rsq_pp r0, -r4.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.7126966451, 0.7126966451
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	rsq_pp r0, -r4.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Standard (15) rsq r0, -c4.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.7126966451, 0.7126966451
	mov r0, c0.y
	mov r2, c0.z
	rsq r0, -c4.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// source registers * modifiers * swizzles
TESTCASE "rsq - sat (0) rsq_sat r0, r4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq_sat r0, r4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (1) rsq_sat r0, c4.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.749268649265, 0.749268649265, 0.749268649265
	mov r0, c0.y
	mov r2, c0.z
	rsq_sat r0, c4.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (2) rsq_sat r0, v0.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat r0, v0.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (3) rsq_sat r0, t0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.7126966451, 0.7126966451
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq_sat r0, t0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (4) rsq_sat_pp r0, c4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, c4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (5) rsq_sat_pp r0, r4.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.749268649265, 0.749268649265, 0.749268649265
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, r4.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (6) rsq_sat_pp r0, t0.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.862662185628, 0.862662185628
	dcl t0
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, t0.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (7) rsq_sat_pp r0, v0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, v0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (8) rsq_sat_pp r0, v0.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, v0.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (9) rsq_sat_pp r0, t0.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	dcl t0
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, t0.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (10) rsq_sat_pp r0, v0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, v0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (11) rsq_sat_pp r0, t0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.749268649265, 0.749268649265, 0.749268649265
	dcl t0
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, t0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (12) rsq_sat r0, r4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.862662185628, 0.862662185628
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq_sat r0, r4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (13) rsq_sat_pp r0, c4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.862662185628, 0.862662185628
	mov r0, c0.y
	mov r2, c0.w
	rsq_sat_pp r0, c4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (14) rsq_sat r0, r4.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.7126966451, 0.7126966451
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq_sat r0, r4.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - sat (15) rsq_sat r0, c4.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.7126966451, 0.7126966451
	mov r0, c0.y
	mov r2, c0.z
	rsq_sat r0, c4.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// masks & predication
TESTCASE "rsq - Pred/Mask (0) rsq r0, r4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.46059348668, 1.46059348668, 1.46059348668, 1.46059348668
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0, r4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (1) rsq r0.x, r4.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.0, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.x, r4.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (2) rsq r0.y, r4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.862662185628, 0.0, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.y, r4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (3) rsq r0.z, r4.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 0.7126966451, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.z, r4.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (4) rsq r0.w, c4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 1.46059348668
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.w, c4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (5) rsq r0.xz, c4.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.0, 0.749268649265, 0.0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xz, c4.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (6) rsq r0.yw, c4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.862662185628, 0.0, 0.862662185628
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.yw, c4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (7) rsq r0.xyw, c4.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.0, 0.7126966451
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xyw, c4.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (8) rsq r0.xyzw, v0.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.70560573084, 1.70560573084, 1.70560573084, 1.70560573084
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0.xyzw, v0.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (9) rsq r0, v0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 2.82842712475, 2.82842712475, 2.82842712475, 2.82842712475
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0, v0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (10) rsq r0.x, v0.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.41421356237, 0.0, 0.0, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0.x, v0.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (11) rsq r0.y, v0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 1.28102523044, 0.0, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0.y, v0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (12) rsq r0.z, t0.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 1.46059348668, 0.0
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.z, t0.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (13) rsq r0.w, t0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.749268649265
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.w, t0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (14) rsq r0.xz, t0.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.0, 0.862662185628, 0.0
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xz, t0.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (15) rsq r0.yw, t0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.7126966451, 0.0, 0.7126966451
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.yw, t0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (16) rsq r0.xyw, r4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.46059348668, 1.46059348668, 0.0, 1.46059348668
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xyw, r4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (17) rsq r0.xyzw, r4.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.749268649265, 0.749268649265, 0.749268649265, 0.749268649265
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xyzw, r4.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (18) rsq r0.x, c4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.46059348668, 0.0, 0.0, 0.0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.x, c4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (19) rsq r0.y, c4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 1.46059348668, 0.0, 0.0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.y, c4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (20) rsq r0.xz, r4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.46059348668, 0.0, 1.46059348668, 0.0
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xz, r4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (21) rsq r0.yw, r4.x"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 1.46059348668, 0.0, 1.46059348668
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.yw, r4.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (22) rsq r0.z, c4.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 0.749268649265, 0.0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.z, c4.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (23) rsq r0.xyw, v0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 2.82842712475, 2.82842712475, 0.0, 2.82842712475
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0.xyw, v0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (24) rsq r0, c4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.862662185628, 0.862662185628
	mov r0, c0.y
	mov r2, c0.z
	rsq r0, c4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (25) rsq r0.w, r4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.862662185628
	mov r4, c4
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.w, r4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (26) rsq r0.xyzw, c4.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.862662185628, 0.862662185628
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xyzw, c4.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (27) rsq r0.y, t0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.749268649265, 0.0, 0.0
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.y, t0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (28) rsq r0.yw, v0.y"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 2.82842712475, 0.0, 2.82842712475
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0.yw, v0.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (29) rsq r0.z, v0.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 1.41421356237, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0.z, v0.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (30) rsq r0.xyw, t0.z"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.862662185628, 0.862662185628, 0.0, 0.862662185628
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xyw, t0.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (31) rsq r0, t0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.7126966451, 0.7126966451
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0, t0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (32) rsq r0.x, t0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.0, 0.0, 0.0
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.x, t0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (33) rsq r0.w, v0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 1.28102523044
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0.w, v0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (34) rsq r0.xz, v0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 1.28102523044, 0.0, 1.28102523044, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	rsq r0.xz, v0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "rsq - Pred/Mask (35) rsq r0.xyzw, t0.w"
	PASSBEGIN
	TESTBEGIN
	def c1, 0.7126966451, 0.7126966451, 0.7126966451, 0.7126966451
	dcl t0
	mov r0, c0.y
	mov r2, c0.z
	rsq r0.xyzw, t0.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



// End of file.  68 tests generated.