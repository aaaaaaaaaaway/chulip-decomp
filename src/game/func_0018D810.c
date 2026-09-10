/* kf_cos.c -- float version of k_cos.c
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
    float value;
    unsigned int word;
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

#define one ((float)(1.0000000000e+00))
#define C1 ((float)(4.1666667908e-02))
#define C2 ((float)(-1.3888889225e-03))
#define C3 ((float)(2.4801587642e-05))
#define C4 ((float)(-2.7557314297e-07))
#define C5 ((float)(2.0875723372e-09))
#define C6 ((float)(-1.1359647598e-11)) /* 0xad47d74e */

float func_0018D810(float x, float y)

{
    float a, hz, z, r, qx;
    __int32_t ix;
    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;      /* ix = |x|'s high word*/
    if (ix < 0x32000000) { /* if x < 2**27 */
        if (((int)x) == 0)
            return one; /* generate inexact */
    }
    z = x * x;
    r = z * (C1 + z * (C2 + z * (C3 + z * (C4 + z * (C5 + z * C6)))));
    if (ix < 0x3e99999a) /* if |x| < 0.3 */
        return one - ((float)0.5 * z - (z * r - x * y));
    else {
        if (ix > 0x3f480000) { /* x > 0.78125 */
            qx = (float)0.28125;
        } else {
            SET_FLOAT_WORD(qx, ix - 0x01000000); /* x/4 */
        }
        hz = (float)0.5 * z - qx;
        a = one - qx;
        return a - (hz - (z * r - x * y));
    }
}
