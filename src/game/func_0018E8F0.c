/* sf_isnan.c -- float version of s_isnan.c.
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

/*
 * func_0018E8F0(x) returns 1 is x is nan, else 0;
 * no branching!
 */

typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union {
    float value;
    __uint32_t word;
} ieee_float_shape_type;
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

int func_0018E8F0(float x)

{
    __int32_t ix;
    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    ix = 0x7f800000 - ix;
    return (int)(((__uint32_t)(ix)) >> 31);
}
