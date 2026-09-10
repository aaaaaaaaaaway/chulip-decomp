/* sf_floor.c -- float version of s_floor.c.
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
 * func_0018E808(x)
 * Return x rounded toward -inf to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to func_0018E808(x).
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

#define huge ((float)(1.0e30))

float func_0018E808(float x)

{
    __int32_t i0, j0;
    __uint32_t i;
    GET_FLOAT_WORD(i0, x);
    j0 = ((i0 >> 23) & 0xff) - 0x7f;
    if (j0 < 23) {
        if (j0 < 0) {                    /* raise inexact if x != 0 */
            if (huge + x > (float)0.0) { /* return 0*sign(x) if |x|<1 */
                if (i0 >= 0) {
                    i0 = 0;
                } else if ((i0 & 0x7fffffff) != 0) {
                    i0 = 0xbf800000;
                }
            }
        } else {
            i = (0x007fffff) >> j0;
            if ((i0 & i) == 0)
                return x;                /* x is integral */
            if (huge + x > (float)0.0) { /* raise inexact flag */
                if (i0 < 0)
                    i0 += (0x00800000) >> j0;
                i0 &= (~i);
            }
        }
    } else {
        if (j0 == 0x80)
            return x + x; /* inf or NaN */
        else
            return x; /* x is integral */
    }
    SET_FLOAT_WORD(x, i0);
    return x;
}
