#ifndef CORE_ADDR_ADDR
enum memory_map{memory_map_p=0,
memory_map_x,memory_map_y,memory_map_l,memory_map_none,

memory_map_laa,memory_map_lab,memory_map_lba,memory_map_lbb,memory_map_le,
memory_map_li,

memory_map_pa,memory_map_pb,memory_map_pe,memory_map_pi,
memory_map_pr,

memory_map_xa,memory_map_xb,memory_map_xe,memory_map_xi,
memory_map_xr,

memory_map_ya,memory_map_yb,memory_map_ye,memory_map_yi,
memory_map_yr,

memory_map_pt,memory_map_pf,

memory_map_emi,
memory_map_e0,memory_map_e1,memory_map_e2,memory_map_e3,
memory_map_e4,memory_map_e5,memory_map_e6,memory_map_e7,
memory_map_e8,memory_map_e9,memory_map_e10,memory_map_e11,
memory_map_e12,memory_map_e13,memory_map_e14,memory_map_e15,
memory_map_e16,memory_map_e17,memory_map_e18,memory_map_e19,
memory_map_e20,memory_map_e21,memory_map_e22,memory_map_e23,
memory_map_e24,memory_map_e25,memory_map_e26,memory_map_e27,
memory_map_e28,memory_map_e29,memory_map_e30,memory_map_e31,
memory_map_e32,memory_map_e33,memory_map_e34,memory_map_e35,
memory_map_e36,memory_map_e37,memory_map_e38,memory_map_e39,
memory_map_e40,memory_map_e41,memory_map_e42,memory_map_e43,
memory_map_e44,memory_map_e45,memory_map_e46,memory_map_e47,
memory_map_e48,memory_map_e49,memory_map_e50,memory_map_e51,
memory_map_e52,memory_map_e53,memory_map_e54,memory_map_e55,
memory_map_e56,memory_map_e57,memory_map_e58,memory_map_e59,
memory_map_e60,memory_map_e61,memory_map_e62,memory_map_e63,

memory_map_e64,memory_map_e65,memory_map_e66,memory_map_e67,
memory_map_e68,memory_map_e69,memory_map_e70,memory_map_e71,
memory_map_e72,memory_map_e73,memory_map_e74,memory_map_e75,
memory_map_e76,memory_map_e77,memory_map_e78,memory_map_e79,
memory_map_e80,memory_map_e81,memory_map_e82,memory_map_e83,
memory_map_e84,memory_map_e85,memory_map_e86,memory_map_e87,
memory_map_e88,memory_map_e89,memory_map_e90,memory_map_e91,
memory_map_e92,memory_map_e93,memory_map_e94,memory_map_e95,
memory_map_e96,memory_map_e97,memory_map_e98,memory_map_e99,

memory_map_e100,memory_map_e101,memory_map_e102,memory_map_e103,
memory_map_e104,memory_map_e105,memory_map_e106,memory_map_e107,
memory_map_e108,memory_map_e109,memory_map_e110,memory_map_e111,
memory_map_e112,memory_map_e113,memory_map_e114,memory_map_e115,
memory_map_e116,memory_map_e117,memory_map_e118,memory_map_e119,
memory_map_e120,memory_map_e121,memory_map_e122,memory_map_e123,
memory_map_e124,memory_map_e125,memory_map_e126,memory_map_e127,
memory_map_e128,memory_map_e129,memory_map_e130,memory_map_e131,
memory_map_e132,memory_map_e133,memory_map_e134,memory_map_e135,
memory_map_e136,memory_map_e137,memory_map_e138,memory_map_e139,
memory_map_e140,memory_map_e141,memory_map_e142,memory_map_e143,
memory_map_e144,memory_map_e145,memory_map_e146,memory_map_e147,
memory_map_e148,memory_map_e149,memory_map_e150,memory_map_e151,
memory_map_e152,memory_map_e153,memory_map_e154,memory_map_e155,
memory_map_e156,memory_map_e157,memory_map_e158,memory_map_e159,
memory_map_e160,memory_map_e161,memory_map_e162,memory_map_e163,
memory_map_e164,memory_map_e165,memory_map_e166,memory_map_e167,
memory_map_e168,memory_map_e169,memory_map_e170,memory_map_e171,
memory_map_e172,memory_map_e173,memory_map_e174,memory_map_e175,
memory_map_e176,memory_map_e177,memory_map_e178,memory_map_e179,
memory_map_e180,memory_map_e181,memory_map_e182,memory_map_e183,
memory_map_e184,memory_map_e185,memory_map_e186,memory_map_e187,
memory_map_e188,memory_map_e189,memory_map_e190,memory_map_e191,
memory_map_e192,memory_map_e193,memory_map_e194,memory_map_e195,
memory_map_e196,memory_map_e197,memory_map_e198,memory_map_e199,

memory_map_e200,memory_map_e201,memory_map_e202,memory_map_e203,
memory_map_e204,memory_map_e205,memory_map_e206,memory_map_e207,
memory_map_e208,memory_map_e209,memory_map_e210,memory_map_e211,
memory_map_e212,memory_map_e213,memory_map_e214,memory_map_e215,
memory_map_e216,memory_map_e217,memory_map_e218,memory_map_e219,
memory_map_e220,memory_map_e221,memory_map_e222,memory_map_e223,
memory_map_e224,memory_map_e225,memory_map_e226,memory_map_e227,
memory_map_e228,memory_map_e229,memory_map_e230,memory_map_e231,
memory_map_e232,memory_map_e233,memory_map_e234,memory_map_e235,
memory_map_e236,memory_map_e237,memory_map_e238,memory_map_e239,
memory_map_e240,memory_map_e241,memory_map_e242,memory_map_e243,
memory_map_e244,memory_map_e245,memory_map_e246,memory_map_e247,
memory_map_e248,memory_map_e249,memory_map_e250,memory_map_e251,
memory_map_e252,memory_map_e253,memory_map_e254,memory_map_e255,
memory_map_dm,
memory_map_p8,memory_map_u,memory_map_u8,memory_map_u16,
memory_map_xs,
memory_map_ys,
memory_map_maxp1, /* should stay at last valid memory map plus 1 */
memory_map_error=666666,
memory_map_ic = memory_map_pt
};

union addr_map{
  enum memory_map mape;long l; unsigned long u;
  };
struct core_addr_struct {
   union addr_map w0;
   union addr_map w1;
};

typedef struct core_addr_struct CORE_ADDR;
#define CORE_ADDR_ADDR(ca) ((ca).w0.l)
#define CORE_ADDR_ADDRU(ca) ((ca).w0.u)
#define CORE_ADDR_MAP(ca) ((ca).w1.mape)

char *TranslateMemoryMapID(int id);
int IsMemoryX(int id);
int IsMemoryY(int id);
int IsMemoryP(int id);

#endif
