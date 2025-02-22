// Tests for Instruction: pow
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


#define SET_PS_CONSTANTS \
	PixelShaderConstantF[4] = {-0.46875, -1.78125, 1.34375, 1.96875}; \
	PixelShaderConstantF[5] = {0.6875, -0.25, -1.0, 1.21875};

VertexShader NormalVS =
	asm
	{
		vs_2_0
		dcl_position	v0
		def c5, -0.46875, -1.78125, 1.34375, 1.96875
		def c6, 0.6875, -0.25, -1.0, 1.21875
		def c7, 0.234375, 0.890625, 0.671875, 0.984375
		def c8, 0.34375, 0.125, 0.5, 0.609375
		m4x4 oPos, v0, c0
		mov oT0, c5
		mov oT1, c6
		mov oD0, c7
		mov oD1, c8
	};


// Tests:

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// source registers * modifiers * swizzles
TESTCASE "pow - Standard (0) pow r0, r4.x, r5.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.593980421906, 0.593980421906, 0.593980421906, 0.593980421906
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow r0, r4.x, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (1) pow_pp r0, -c4.y, v1.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0748320541, 1.0748320541, 1.0748320541, 1.0748320541
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, -c4.y, v1.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (2) pow r0, -v0.z, -c5.z";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.671875, 0.671875, 0.671875, 0.671875
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow r0, -v0.z, -c5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (3) pow_pp r0, t0.w, -r5.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.437980970344, 0.437980970344, 0.437980970344, 0.437980970344
	dcl t0
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, t0.w, -r5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (4) pow_pp r0, -v0.x, -c5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.695789420928, 0.695789420928, 0.695789420928, 0.695789420928
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, -v0.x, -c5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (5) pow_pp r0, -t0.y, r5.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.48721361692, 1.48721361692, 1.48721361692, 1.48721361692
	dcl t0
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, -t0.y, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (6) pow r0, -r4.z, -r5.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.697608648147, 0.697608648147, 0.697608648147, 0.697608648147
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow r0, -r4.z, -r5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (7) pow r0, -c4.w, v1.z";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.40312152004, 1.40312152004, 1.40312152004, 1.40312152004
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow r0, -c4.w, v1.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (8) pow r0, r4.y, -r5.z";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.78125, 1.78125, 1.78125, 1.78125
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow r0, r4.y, -r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (9) pow r0, c4.z, -v1.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.963740678166, 0.963740678166, 0.963740678166, 0.963740678166
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow r0, c4.z, -v1.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (10) pow_pp r0, v0.z, -c5.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.314435164, 1.314435164, 1.314435164, 1.314435164
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, v0.z, -c5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (11) pow r0, -v0.y, c5.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.868341659206, 0.868341659206, 0.868341659206, 0.868341659206
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow r0, -v0.y, c5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (12) pow r0, t0.x, r5.z";
	PASSBEGIN
	TESTBEGIN
	def c1, 2.13333333333, 2.13333333333, 2.13333333333, 2.13333333333
	dcl t0
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow r0, t0.x, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (13) pow_pp r0, -r4.w, -r5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.18453430513, 1.18453430513, 1.18453430513, 1.18453430513
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, -r4.w, -r5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (14) pow_pp r0, c4.x, -v1.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.29751962341, 1.29751962341, 1.29751962341, 1.29751962341
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, c4.x, -v1.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (15) pow_pp r0, t0.z, r5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.928796094753, 0.928796094753, 0.928796094753, 0.928796094753
	dcl t0
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, t0.z, r5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (16) pow_pp r0, -c4.x, -v1.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.58679256556, 1.58679256556, 1.58679256556, 1.58679256556
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, -c4.x, -v1.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (17) pow_pp r0, -v0.w, c5.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.98923140554, 0.98923140554, 0.98923140554, 0.98923140554
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, -v0.w, c5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Standard (18) pow_pp r0, c4.z, v1.z";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.15920231194, 1.15920231194, 1.15920231194, 1.15920231194
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow_pp r0, c4.z, v1.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// source registers * modifiers * swizzles
TESTCASE "pow - sat (0) pow_sat r0, r4.w, r5.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow_sat r0, r4.w, r5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - sat (1) pow_sat r0, c4.y, v1.z";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow_sat r0, c4.y, v1.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - sat (2) pow_sat r0, v0.x, c5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow_sat r0, v0.x, c5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - sat (3) pow_sat r0, t0.z, r5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.928796094753, 0.928796094753, 0.928796094753, 0.928796094753
	dcl t0
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow_sat r0, t0.z, r5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - sat (4) pow_sat_pp r0, r4.w, r5.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.w
	pow_sat_pp r0, r4.w, r5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - sat (5) pow_sat_pp r0, c4.y, v1.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.0, 1.0, 1.0, 1.0
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow_sat_pp r0, c4.y, v1.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - sat (6) pow_sat_pp r0, v0.x, c5.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.368819613581, 0.368819613581, 0.368819613581, 0.368819613581
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow_sat_pp r0, v0.x, c5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - sat (7) pow_sat_pp r0, t0.w, r5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.844213625275, 0.844213625275, 0.844213625275, 0.844213625275
	dcl t0
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.w
	pow_sat_pp r0, t0.w, r5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// masks & predication
TESTCASE "pow - Pred/Mask (0) pow r0, r4.w, r5.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 2.28320422053, 2.28320422053, 2.28320422053, 2.28320422053
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow r0, r4.w, r5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (1) (p0.x) pow r0.x, c4.x, v1.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.909636042553, 0.0, 0.0, 0.0
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(p0.x) pow r0.x, c4.x, v1.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (2) (p0.y) pow r0.y, v0.w, c5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 0.0, 0.98923140554, 0.0, 0.0
	dcl v0
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(p0.y) pow r0.y, v0.w, c5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (3) (p0.z) pow r0.z, t0.w, r5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 1.59314761468, 0.0
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(p0.z) pow r0.z, t0.w, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (4) (!p0.w) pow r0.w, r4.w, r5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.507936507937
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.w) pow r0.w, r4.w, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (5) pow r0.xz, v0.w, c5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.00394484976, 0.0, 1.00394484976, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow r0.xz, v0.w, c5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (6) (!p0) pow r0.yw, t0.w, r5.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.0, 0.844213625275, 0.0, 0.844213625275
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0) pow r0.yw, t0.w, r5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (7) (!p0.z) pow r0.xyw, c4.x, v1.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 0.909636042553, 0.909636042553, 0.0, 0.909636042553
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(!p0.z) pow r0.xyw, c4.x, v1.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (8) (!p0.y) pow r0.xyzw, r4.y, r5.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.y) pow r0.xyzw, r4.y, r5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (9) (!p0.w) pow r0, c4.x, v1.w";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 0.630202095536, 0.630202095536, 0.630202095536, 0.630202095536
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(!p0.w) pow r0, c4.x, v1.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (10) (!p0) pow r0.x, v0.x, c5.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 1.43721644785, 0.0, 0.0, 0.0
	dcl v0
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(!p0) pow r0.x, v0.x, c5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (11) pow r0.y, t0.y, r5.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 1.48721361692, 0.0, 0.0
	dcl t0
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow r0.y, t0.y, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (12) (!p0.y) pow r0.z, r4.z, r5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 1.2252337552, 0.0
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.y) pow r0.z, r4.z, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (13) (p0.x) pow r0.w, t0.y, r5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(p0.x) pow r0.w, t0.y, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (14) (p0.w) pow r0.xz, c4.y, v1.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 1.3346347815, 0.0, 1.3346347815, 0.0
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(p0.w) pow r0.xz, c4.y, v1.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (15) (p0.y) pow r0.yw, c4.w, v1.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(p0.y) pow r0.yw, c4.w, v1.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (16) pow r0.xyw, t0.w, r5.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 2.28320422053, 2.28320422053, 0.0, 2.28320422053
	dcl t0
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	pow r0.xyw, t0.w, r5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (17) (p0.z) pow r0.xyzw, v0.z, c5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.760783055256, 0.760783055256, 0.760783055256, 0.760783055256
	dcl v0
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(p0.z) pow r0.xyzw, v0.z, c5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (18) (p0.x) pow r0, v0.y, c5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl v0
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(p0.x) pow r0, v0.y, c5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (19) (!p0.w) pow r0.x, r4.z, r5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.w) pow r0.x, r4.z, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (20) (!p0) pow r0.y, c4.y, v1.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(!p0) pow r0.y, c4.y, v1.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (21) (!p0.x) pow r0.z, c4.x, v1.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.909636042553, 0.0
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(!p0.x) pow r0.z, c4.x, v1.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (22) pow r0.w, c4.w, v1.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 1.26219951461
	dcl v1
	mov r0, c0.y
	mov r2, c0.w
	pow r0.w, c4.w, v1.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (23) (p0.x) pow r0.yw, r4.y, r5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 0.0, 1.48721361692, 0.0, 1.48721361692
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(p0.x) pow r0.yw, r4.y, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (24) (p0.z) pow r0.xz, r4.z, r5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(p0.z) pow r0.xz, r4.z, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (25) (p0.w) pow r0.xyw, v0.z, c5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl v0
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(p0.w) pow r0.xyw, v0.z, c5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (26) (!p0) pow r0.xyzw, c4.z, v1.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 1.15920231194, 0.0, 1.15920231194, 0.0
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(!p0) pow r0.xyzw, c4.z, v1.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (27) (!p0.y) pow r0, t0.w, r5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.y) pow r0, t0.w, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (28) (!p0.y) pow r0.x, t0.x, r5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.y) pow r0.x, t0.x, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (29) (!p0) pow r0.w, v0.y, c5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl v0
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(!p0) pow r0.w, v0.y, c5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (30) (!p0.x) pow r0.y, r4.w, r5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 0.0, 0.507936507937, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.x) pow r0.y, r4.w, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (31) (!p0) pow r0.xyw, r4.y, r5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 0.561403508772, 0.561403508772, 0.0, 0.561403508772
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0) pow r0.xyw, r4.y, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (32) (!p0.x) pow r0.xyzw, t0.y, r5.w";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 0, 0, 0};
	TESTBEGIN
	def c1, 2.02102154946, 2.02102154946, 2.02102154946, 2.02102154946
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.x) pow r0.xyzw, t0.y, r5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (33) pow r0.z, v0.w, c5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.0, 1.00394484976, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow r0.z, v0.w, c5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (34) pow r0.yw, v0.z, c5.w";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.0, 0.615896643013, 0.0, 0.615896643013
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow r0.yw, v0.z, c5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (35) (!p0) pow r0.xz, t0.y, r5.w";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0) pow r0.xz, t0.y, r5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (36) pow r0.x, v0.z, c5.y";
	PASSBEGIN
	TESTBEGIN
	def c1, 1.10453092427, 0.0, 0.0, 0.0
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow r0.x, v0.z, c5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (37) pow r0.xyzw, v0.x, c5.x";
	PASSBEGIN
	TESTBEGIN
	def c1, 0.368819613581, 0.368819613581, 0.368819613581, 0.368819613581
	dcl v0
	mov r0, c0.y
	mov r2, c0.w
	pow r0.xyzw, v0.x, c5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (38) (p0.z) pow r0, r4.y, r5.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.865603055254, 0.865603055254, 0.865603055254, 0.865603055254
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(p0.z) pow r0, r4.y, r5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (39) (!p0.z) pow r0.y, t0.z, r5.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.z) pow r0.y, t0.z, r5.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (40) (!p0.y) pow r0.w, c4.z, v1.z";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 0, 1, 0};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 1.15920231194
	dcl v1
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(!p0.y) pow r0.w, c4.z, v1.z
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (41) (p0.w) pow r0.z, v0.z, c5.w";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.615896643013, 0.0
	dcl v0
	SET_PRED
	mov r0, c0.y
	mov r2, c0.w
	(p0.w) pow r0.z, v0.z, c5.w
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (42) (p0.y) pow r0.xz, t0.y, r5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 1.48721361692, 0.0, 1.48721361692, 0.0
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(p0.y) pow r0.xz, t0.y, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (43) (!p0.w) pow r0.yw, r4.x, r5.x";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {0, 1, 0, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	SET_PRED
	mov r4, c4
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.w) pow r0.yw, r4.x, r5.x
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND

TESTCASE "pow - Pred/Mask (44) (!p0.x) pow r0.xyw, t0.z, r5.y";
	USEPREDICATE
	PASSBEGIN
	PixelShaderConstantF[2] = {1, 1, 1, 1};
	TESTBEGIN
	def c1, 0.0, 0.0, 0.0, 0.0
	dcl t0
	SET_PRED
	mov r5, c5
	mov r0, c0.y
	mov r2, c0.z
	(!p0.x) pow r0.xyw, t0.z, r5.y
	VERIFY_RESULT
	V_X V_Y V_Z V_W
	TESTEND



// End of file.  72 tests generated.