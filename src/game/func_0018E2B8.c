/* kf_sin.c -- float version of k_sin.c
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union {
    double value;
    struct {
        __uint32_t lsw, msw;
    } parts;
} ieee_double_shape_type;
typedef union {
    float value;
    __uint32_t word;
} ieee_float_shape_type;
#define EXTRACT_WORDS(hi, lo, d)                                                                   \
    do {                                                                                           \
        ieee_double_shape_type u;                                                                  \
        u.value = (d);                                                                             \
        (hi) = u.parts.msw;                                                                        \
        (lo) = u.parts.lsw;                                                                        \
    } while (0)
#define INSERT_WORDS(d, hi, lo)                                                                    \
    do {                                                                                           \
        ieee_double_shape_type u;                                                                  \
        u.parts.msw = (hi);                                                                        \
        u.parts.lsw = (lo);                                                                        \
        (d) = u.value;                                                                             \
    } while (0)
#define GET_HIGH_WORD(i, d)                                                                        \
    do {                                                                                           \
        ieee_double_shape_type u;                                                                  \
        u.value = (d);                                                                             \
        (i) = u.parts.msw;                                                                         \
    } while (0)
#define SET_HIGH_WORD(d, i)                                                                        \
    do {                                                                                           \
        ieee_double_shape_type u;                                                                  \
        u.value = (d);                                                                             \
        u.parts.msw = (i);                                                                         \
        (d) = u.value;                                                                             \
    } while (0)
#define GET_FLOAT_WORD(i, d)                                                                       \
    do {                                                                                           \
        ieee_float_shape_type u;                                                                   \
        u.value = (d);                                                                             \
        (i) = u.word;                                                                              \
    } while (0)
#define SET_FLOAT_WORD(d, i)                                                                       \
    do {                                                                                           \
        ieee_float_shape_type u;                                                                   \
        u.word = (i);                                                                              \
        (d) = u.value;                                                                             \
    } while (0)
extern double func_0018EA78(double, double);
extern float func_0018EAC0(float, float);

#define half ((float)(5.0000000000e-01))
#define S1 ((float)(-1.6666667163e-01))
#define S2 ((float)(8.3333337680e-03))
#define S3 ((float)(-1.9841270114e-04))
#define S4 ((float)(2.7557314297e-06))
#define S5 ((float)(-2.5050759689e-08))
#define S6 ((float)(1.5896910177e-10)) /* 0x2f2ec9d3 */

float func_0018E2B8(float x, float y, int iy)

{
    float z, r, v;
    __int32_t ix;
    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;    /* high word of x */
    if (ix < 0x32000000) /* |x| < 2**-27 */
    {
        if ((int)x == 0)
            return x;
    } /* generate inexact */
    z = x * x;
    v = z * x;
    r = S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));
    if (iy == 0)
        return x + v * (S1 + z * r);
    else
        return x - ((z * (half * y - v * r) - y) - v * S1);
}
