/* sf_scalbn.c -- float version of s_scalbn.c.
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

#define INT_MAX 2147483647

#if INT_MAX > 50000
#define OVERFLOW_INT 50000
#else
#define OVERFLOW_INT 30000
#endif

#define two25 ((float)(3.355443200e+07))
#define twom25 ((float)(2.9802322388e-08))
#define huge ((float)(1.0e+30))
#define tiny ((float)(1.0e-30))

float func_0018E918(float x, int n)

{
    __int32_t k, ix;
    GET_FLOAT_WORD(ix, x);
    k = (ix & 0x7f800000) >> 23; /* extract exponent */
    if (k == 0) {                /* 0 or subnormal x */
        if ((ix & 0x7fffffff) == 0)
            return x; /* +-0 */
        x *= two25;
        GET_FLOAT_WORD(ix, x);
        k = ((ix & 0x7f800000) >> 23) - 25;
        if (n < -50000)
            return tiny * x; /*underflow*/
    }
    if (k == 0xff)
        return x + x; /* NaN or Inf */
    k = k + n;
    if (k > 0xfe)
        return huge * func_0018EAC0(huge, x); /* overflow  */
    if (k > 0)                                /* normal result */
    {
        SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
        return x;
    }
    if (k <= -25)
        if (n > OVERFLOW_INT)                     /* in case integer overflow in n+k */
            return huge * func_0018EAC0(huge, x); /*overflow*/
        else
            return tiny * func_0018EAC0(tiny, x); /*underflow*/
    k += 25;                                      /* subnormal result */
    SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
    return x * twom25;
}
