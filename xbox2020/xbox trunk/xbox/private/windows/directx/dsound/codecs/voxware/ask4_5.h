/******************************************************************************
*                        Voxware Proprietary Material
*                        Copyright 1996, Voxware, Inc
*                            All Rights Reserved
*
*                       DISTRIBUTION PROHIBITED without
*                      written authorization from Voxware
******************************************************************************/
 
/******************************************************************************
* Filename:    ASK4_5.h
*
* Purpose:     codebooks for 3rd ASK pair, which include 5 bits stage 1 codebook,
*              5 bits rotation-scaling matrix, 3 bits stage 2 inner cell codebook
*              and 3 bits stage 2 outer cell codebook. 
*
* $Header:   /export/phobos/pvcs/r_and_d/archives/scaleable/tables/ASK4_5.h_v   1.0   06 Feb 1998 10:12:24   johnp  $
*
******************************************************************************/
#ifndef _ASK4_5_H_
#define _ASK4_5_H_
5.729110e-001F, -4.441100e-002F,  /* stage 1 codebook (5 bits) */
1.910400e-002F, -2.647900e-002F,
4.685990e-001F, 2.309660e-001F,
5.517000e-002F, 4.823500e-001F,
5.332150e-001F, -3.284490e-001F,
3.353600e-002F, -3.657360e-001F,
3.785420e-001F, 5.252600e-002F,
-4.780900e-002F, 1.256810e-001F,
2.139100e-001F, -8.139000e-003F,
-2.049380e-001F, 1.182560e-001F,
2.738800e-001F, 3.836320e-001F,
-2.139930e-001F, 5.094260e-001F,
3.842780e-001F, -1.419810e-001F,
-1.886540e-001F, -2.896650e-001F,
2.469480e-001F, 1.921830e-001F,
-1.021440e-001F, 3.089880e-001F,
2.625970e-001F, -3.422390e-001F,
-3.278220e-001F, -1.597070e-001F,
1.065600e-001F, 1.145750e-001F,
-3.216730e-001F, 2.469620e-001F,
4.053750e-001F, -5.691150e-001F,
-1.693250e-001F, -5.111600e-001F,
1.608820e-001F, -1.736240e-001F,
-3.708500e-001F, 2.832000e-002F,
-3.940600e-002F, -1.737460e-001F,
-5.268830e-001F, -1.447340e-001F,
7.170900e-002F, 2.809880e-001F,
-4.842760e-001F, 3.875650e-001F,
1.218140e-001F, -5.766810e-001F,
-4.076600e-001F, -3.864260e-001F,
-1.695070e-001F, -5.300600e-002F,
-5.727540e-001F, 1.321520e-001F, 
9.892215e+000F, -7.668262e-001F, /* rotation and scaling matrix (5 bits) */
9.420018e+000F, -1.305657e+001F,
9.006369e+000F, 4.439115e+000F,
1.240516e+000F, 1.084581e+001F,
7.871369e+000F, -4.848594e+000F,
1.123737e+000F, -1.225522e+001F,
1.457933e+001F, 2.023010e+000F,
-5.787798e+000F, 1.521505e+001F,
1.536391e+001F, -5.845768e-001F,
-1.343288e+001F, 7.751216e+000F,
6.346276e+000F, 8.889421e+000F,
-3.562309e+000F, 8.480338e+000F,
1.215845e+001F, -4.492239e+000F,
-7.172324e+000F, -1.101260e+001F,
1.176538e+001F, 9.156204e+000F,
-4.305764e+000F, 1.302504e+001F,
7.499327e+000F, -9.773768e+000F,
-1.245941e+001F, -6.069924e+000F,
1.161812e+001F, 1.249198e+001F,
-1.017811e+001F, 7.814164e+000F,
5.027794e+000F, -7.058632e+000F,
-3.065886e+000F, -9.255326e+000F,
9.596067e+000F, -1.035608e+001F,
-1.334698e+001F, 1.019243e+000F,
-3.309622e+000F, -1.459254e+001F,
-1.013671e+001F, -2.784540e+000F,
3.672817e+000F, 1.439174e+001F,
-7.178088e+000F, 5.744608e+000F,
1.881737e+000F, -8.908352e+000F,
-7.226082e+000F, -6.849693e+000F,
-1.412621e+001F, -4.417363e+000F,
-9.500831e+000F, 2.192134e+000F, 
4.271000e-002F, 1.613100e-002F,    /* stage 2 inner cell codebook (3 bits) */
4.442900e-002F, 1.100067e+000F,
1.104499e+000F, -2.301630e-001F,
8.749920e-001F, 7.274760e-001F,
-9.451950e-001F, -3.002340e-001F,
-7.892750e-001F, 6.294330e-001F,
5.545670e-001F, -1.000008e+000F,
-3.674820e-001F, -9.551640e-001F,
-4.612130e-001F, -7.579180e-001F,  /* stage 2 inner cell codebook (3 bits) */
-7.673170e-001F, -2.748900e-002F,
4.837350e-001F, -1.048276e+000F,
-5.124220e-001F, 7.374370e-001F,
3.683950e-001F, -1.879300e-002F,
3.828040e-001F, 1.010899e+000F,
1.777711e+000F, -7.106510e-001F,
1.652714e+000F, 8.651050e-001F
#endif
