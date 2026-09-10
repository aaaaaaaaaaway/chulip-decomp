
/* @(#)s_fabs.c 5.1 93/09/24 */
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
       <<func_0018E3C0>>, <<fabsf>>---absolute value (magnitude)
INDEX
        func_0018E3C0
INDEX
        fabsf

ANSI_SYNOPSIS
        #include <math.h>
       double func_0018E3C0(double <[x]>);
       float fabsf(float <[x]>);

TRAD_SYNOPSIS
        #include <math.h>
       double func_0018E3C0(<[x]>)
       double <[x]>;

       float fabsf(<[x]>)
       float <[x]>;

DESCRIPTION
<<func_0018E3C0>> and <<fabsf>> calculate
@tex
$|x|$,
@end tex
the absolute value (magnitude) of the argument <[x]>, by direct
manipulation of the bit representation of <[x]>.

RETURNS
The calculated value is returned.  No errors are detected.

PORTABILITY
<<func_0018E3C0>> is ANSI.
<<fabsf>> is an extension.

*/

/*
 * func_0018E3C0(x) returns the absolute value of x.
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

double func_0018E3C0(double x)

{
    __uint32_t high;
    GET_HIGH_WORD(high, x);
    SET_HIGH_WORD(x, high & 0x7fffffff);
    return x;
}
