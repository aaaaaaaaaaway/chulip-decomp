/* sf_fabs.c -- float version of s_fabs.c.
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
 * func_0018E7E8(x) returns the absolute value of x.
 */

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

float func_0018E7E8(float x)

{
    __uint32_t ix;
    GET_FLOAT_WORD(ix, x);
    SET_FLOAT_WORD(x, ix & 0x7fffffff);
    return x;
}
