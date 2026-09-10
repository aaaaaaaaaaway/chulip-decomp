
/* @(#)s_sin.c 5.1 93/09/24 */
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
        <<sin>>, <<sinf>>, <<cos>>, <<cosf>>---sine or cosine
INDEX
sin
INDEX
sinf
INDEX
cos
INDEX
cosf
ANSI_SYNOPSIS
        #include <math.h>
        double func_0018B118(double <[x]>);
        float  sinf(float <[x]>);
        double cos(double <[x]>);
        float cosf(float <[x]>);

TRAD_SYNOPSIS
        #include <math.h>
        double func_0018B118(<[x]>)
        double <[x]>;
        float  sinf(<[x]>)
        float <[x]>;

        double cos(<[x]>)
        double <[x]>;
        float cosf(<[x]>)
        float <[x]>;

DESCRIPTION
        <<sin>> and <<cos>> compute (respectively) the sine and cosine
        of the argument <[x]>.  Angles are specified in radians.

        <<sinf>> and <<cosf>> are identical, save that they take and
        return <<float>> values.


RETURNS
        The sine or cosine of <[x]> is returned.

PORTABILITY
        <<sin>> and <<cos>> are ANSI C.
        <<sinf>> and <<cosf>> are extensions.

QUICKREF
        sin ansi pure
        sinf - pure
*/

/* func_0018B118(x)
 * Return sine function of x.
 *
 * kernel function:
 *	func_0018D638		... sine function on [-pi/4,pi/4]
 *	func_0018C880		... cose function on [-pi/4,pi/4]
 *	func_0018B710	... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *	[-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *	in [-pi/4 , +pi/4], and let n = k mod 4.
 *	We have
 *
 *          n        func_0018B118(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *	    0	       S	   C		 T
 *	    1	       C	  -S		-1/T
 *	    2	      -S	  -C		 T
 *	    3	      -C	   S		-1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *	TRIG(x) returns trig(x) nearly rounded
 */

typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union {
    float value;
    unsigned int word;
} ieee_float_shape_type;
typedef union {
    double value;
    struct {
        unsigned int lsw, msw;
    } parts;
} ieee_double_shape_type;
#define GET_FLOAT_WORD(i, d)                                                                       \
    do {                                                                                           \
        ieee_float_shape_type u;                                                                   \
        u.value = (d);                                                                             \
        (i) = u.word;                                                                              \
    } while (0)
#define GET_HIGH_WORD(i, d)                                                                        \
    do {                                                                                           \
        ieee_double_shape_type u;                                                                  \
        u.value = (d);                                                                             \
        (i) = u.parts.msw;                                                                         \
    } while (0)
extern double func_0018D638(double, double, int);
extern double func_0018C880(double, double);
extern int func_0018B710(double, double *);
struct exception {
    int type;
    char *name;
    double arg1, arg2, retval;
    int err;
};
enum __fdlibm_version { __fdlibm_ieee = -1, __fdlibm_svid, __fdlibm_xopen, __fdlibm_posix };
extern const enum __fdlibm_version D_001EB988;
extern int *func_00191698(void);
#define _LIB_VERSION D_001EB988
#define _IEEE_ __fdlibm_ieee
#define _SVID_ __fdlibm_svid
#define _POSIX_ __fdlibm_posix
#define DOMAIN 1
#define EDOM 33
#define errno (*func_00191698())

double func_0018B118(double x) {
    double y[2], z = 0.0;
    __int32_t n, ix;

    /* High word of x. */
    GET_HIGH_WORD(ix, x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if (ix <= 0x3fe921fb)
        return func_0018D638(x, z, 0);

    /* func_0018B118(Inf or NaN) is NaN */
    else if (ix >= 0x7ff00000)
        return x - x;

    /* argument reduction needed */
    else {
        n = func_0018B710(x, y);
        switch (n & 3) {
        case 0:
            return func_0018D638(y[0], y[1], 1);
        case 1:
            return func_0018C880(y[0], y[1]);
        case 2:
            return -func_0018D638(y[0], y[1], 1);
        default:
            return -func_0018C880(y[0], y[1]);
        }
    }
}
