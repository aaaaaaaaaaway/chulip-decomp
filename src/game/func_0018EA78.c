
/* @(#)s_copysign.c 5.1 93/09/24 */
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
<<func_0018EA78>>, <<copysignf>>---sign of <[y]>, magnitude of <[x]>

INDEX
        func_0018EA78
INDEX
        copysignf

ANSI_SYNOPSIS
        #include <math.h>
        double func_0018EA78 (double <[x]>, double <[y]>);
        float copysignf (float <[x]>, float <[y]>);

TRAD_SYNOPSIS
        #include <math.h>
        double func_0018EA78 (<[x]>, <[y]>)
        double <[x]>;
        double <[y]>;

        float copysignf (<[x]>, <[y]>)
        float <[x]>;
        float <[y]>;

DESCRIPTION
<<func_0018EA78>> constructs a number with the magnitude (absolute value)
of its first argument, <[x]>, and the sign of its second argument,
<[y]>.

<<copysignf>> does the same thing; the two functions differ only in
the type of their arguments and result.

RETURNS
<<func_0018EA78>> returns a <<double>> with the magnitude of
<[x]> and the sign of <[y]>.
<<copysignf>> returns a <<float>> with the magnitude of
<[x]> and the sign of <[y]>.

PORTABILITY
<<func_0018EA78>> is not required by either ANSI C or the System V Interface
Definition (Issue 2).

*/

/*
 * func_0018EA78(double x, double y)
 * func_0018EA78(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 */

typedef unsigned int __uint32_t;
typedef union {
    double value;
    struct {
        __uint32_t lsw, msw;
    } parts;
} ieee_double_shape_type;
#define GET_HIGH_WORD(i, d)                                                                        \
    do {                                                                                           \
        ieee_double_shape_type u;                                                                  \
        u.value = (d);                                                                             \
        (i) = u.parts.msw;                                                                         \
    } while (0)
#define SET_HIGH_WORD(d, v)                                                                        \
    do {                                                                                           \
        ieee_double_shape_type u;                                                                  \
        u.value = (d);                                                                             \
        u.parts.msw = (v);                                                                         \
        (d) = u.value;                                                                             \
    } while (0)

double func_0018EA78(double x, double y)

{
    __uint32_t hx, hy;
    GET_HIGH_WORD(hx, x);
    GET_HIGH_WORD(hy, y);
    SET_HIGH_WORD(x, (hx & 0x7fffffff) | (hy & 0x80000000));
    return x;
}
