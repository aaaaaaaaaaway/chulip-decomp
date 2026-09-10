
/* @(#)s_floor.c 5.1 93/09/24 */
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
<<func_0018E3F8>>, <<floorf>>, <<ceil>>, <<ceilf>>---func_0018E3F8 and ceiling
INDEX
        func_0018E3F8
INDEX
        floorf
INDEX
        ceil
INDEX
        ceilf

ANSI_SYNOPSIS
        #include <math.h>
        double func_0018E3F8(double <[x]>);
        float floorf(float <[x]>);
        double ceil(double <[x]>);
        float ceilf(float <[x]>);

TRAD_SYNOPSIS
        #include <math.h>
        double func_0018E3F8(<[x]>)
        double <[x]>;
        float floorf(<[x]>)
        float <[x]>;
        double ceil(<[x]>)
        double <[x]>;
        float ceilf(<[x]>)
        float <[x]>;

DESCRIPTION
<<func_0018E3F8>> and <<floorf>> find
@tex
$\lfloor x \rfloor$,
@end tex
the nearest integer less than or equal to <[x]>.
<<ceil>> and <<ceilf>> find
@tex
$\lceil x\rceil$,
@end tex
the nearest integer greater than or equal to <[x]>.

RETURNS
<<func_0018E3F8>> and <<ceil>> return the integer result as a double.
<<floorf>> and <<ceilf>> return the integer result as a float.

PORTABILITY
<<func_0018E3F8>> and <<ceil>> are ANSI.
<<floorf>> and <<ceilf>> are extensions.


*/

/*
 * func_0018E3F8(x)
 * Return x rounded toward -inf to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to func_0018E3F8(x).
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

static const double huge = 1.0e300;

double func_0018E3F8(double x)

{
    __int32_t i0, i1, j0;
    __uint32_t i, j;
    EXTRACT_WORDS(i0, i1, x);
    j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
    if (j0 < 20) {
        if (j0 < 0) {             /* raise inexact if x != 0 */
            if (huge + x > 0.0) { /* return 0*sign(x) if |x|<1 */
                if (i0 >= 0) {
                    i0 = i1 = 0;
                } else if (((i0 & 0x7fffffff) | i1) != 0) {
                    i0 = 0xbff00000;
                    i1 = 0;
                }
            }
        } else {
            i = (0x000fffff) >> j0;
            if (((i0 & i) | i1) == 0)
                return x;         /* x is integral */
            if (huge + x > 0.0) { /* raise inexact flag */
                if (i0 < 0)
                    i0 += (0x00100000) >> j0;
                i0 &= (~i);
                i1 = 0;
            }
        }
    } else if (j0 > 51) {
        if (j0 == 0x400)
            return x + x; /* inf or NaN */
        else
            return x; /* x is integral */
    } else {
        i = ((__uint32_t)(0xffffffff)) >> (j0 - 20);
        if ((i1 & i) == 0)
            return x;         /* x is integral */
        if (huge + x > 0.0) { /* raise inexact flag */
            if (i0 < 0) {
                if (j0 == 20)
                    i0 += 1;
                else {
                    j = i1 + (1 << (52 - j0));
                    if (j < i1)
                        i0 += 1; /* got a carry */
                    i1 = j;
                }
            }
            i1 &= (~i);
        }
    }
    INSERT_WORDS(x, i0, i1);
    return x;
}
