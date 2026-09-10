
/* @(#)s_scalbn.c 5.1 93/09/24 */
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
FUNCTION
<<func_0018E630>>, <<scalbnf>>---scale by integer
INDEX
        func_0018E630
INDEX
        scalbnf

ANSI_SYNOPSIS
        #include <math.h>
        double func_0018E630(double <[x]>, int <[y]>);
        float scalbnf(float <[x]>, int <[y]>);

TRAD_SYNOPSIS
        #include <math.h>
        double func_0018E630(<[x]>,<[y]>)
        double <[x]>;
        int <[y]>;
        float scalbnf(<[x]>,<[y]>)
        float <[x]>;
        int <[y]>;

DESCRIPTION
<<func_0018E630>> and <<scalbnf>> scale <[x]> by <[n]>, returning <[x]> times
2 to the power <[n]>.  The result is computed by manipulating the
exponent, rather than by actually performing an exponentiation or
multiplication.

RETURNS
<[x]> times 2 to the power <[n]>.

PORTABILITY
Neither <<func_0018E630>> nor <<scalbnf>> is required by ANSI C or by the System V
Interface Definition (Issue 2).

*/

/*
 * func_0018E630 (double x, int n)
 * func_0018E630(x,n) returns x* 2**n  computed by  exponent
 * manipulation rather than by actually performing an
 * exponentiation or a multiplication.
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

static const double

    two54 = 1.80143985094819840000e+16,  /* 0x43500000, 0x00000000 */
    twom54 = 5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
    huge = 1.0e+300, tiny = 1.0e-300;

double func_0018E630(double x, int n)

{
    __int32_t k, hx, lx;
    EXTRACT_WORDS(hx, lx, x);
    k = (hx & 0x7ff00000) >> 20; /* extract exponent */
    if (k == 0) {                /* 0 or subnormal x */
        if ((lx | (hx & 0x7fffffff)) == 0)
            return x; /* +-0 */
        x *= two54;
        GET_HIGH_WORD(hx, x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000)
            return tiny * x; /*underflow*/
    }
    if (k == 0x7ff)
        return x + x; /* NaN or Inf */
    k = k + n;
    if (k > 0x7fe)
        return huge * func_0018EA78(huge, x); /* overflow  */
    if (k > 0)                                /* normal result */
    {
        SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
        return x;
    }
    if (k <= -54)
        if (n > 50000)                            /* in case integer overflow in n+k */
            return huge * func_0018EA78(huge, x); /*overflow*/
        else
            return tiny * func_0018EA78(tiny, x); /*underflow*/
    k += 54;                                      /* subnormal result */
    SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
    return x * twom54;
}
