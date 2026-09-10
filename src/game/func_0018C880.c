
/* @(#)k_cos.c 5.1 93/09/24 */
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
 * func_0018C880( x,  y )
 * kernel cos function on [-pi/4, pi/4], pi/4 ~ 0.785398164
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *	1. Since cos(-x) = cos(x), we need only to consider positive x.
 *	2. if x < 2^-27 (hx<0x3e400000 0), return 1 with inexact if x!=0.
 *	3. cos(x) is approximated by a polynomial of degree 14 on
 *	   [0,pi/4]
 *		  	                 4            14
 *	   	cos(x) ~ 1 - x*x/2 + C1*x + ... + C6*x
 *	   where the remez error is
 *
 * 	|              2     4     6     8     10    12     14 |     -58
 * 	|cos(x)-(1-.5*x +C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  )| <= 2
 * 	|    					               |
 *
 * 	               4     6     8     10    12     14
 *	4. let r = C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  , then
 *	       cos(x) = 1 - x*x/2 + r
 *	   since cos(x+y) ~ cos(x) - sin(x)*y
 *			  ~ cos(x) - x*y,
 *	   a correction term is necessary in cos(x) and hence
 *		cos(x+y) = 1 - (x*x/2 - (r - x*y))
 *	   For better accuracy when x > 0.3, let qx = |x|/4 with
 *	   the last 32 bits mask off, and if x > 0.78125, let qx = 0.28125.
 *	   Then
 *		cos(x+y) = (1-qx) - ((x*x/2-qx) - (r-x*y)).
 *	   Note that 1-qx and (x*x/2-qx) is EXACT here, and the
 *	   magnitude of the latter is at least a quarter of x*x/2,
 *	   thus, reducing the rounding error in the subtraction.
 */

typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union {
    double value;
    struct {
        __uint32_t lsw, msw;
    } parts;
} ieee_double_shape_type;
#define INSERT_WORDS(d, hi, lo)                                                                    \
    do {                                                                                           \
        ieee_double_shape_type iw_u;                                                               \
        iw_u.parts.msw = (hi);                                                                     \
        iw_u.parts.lsw = (lo);                                                                     \
        (d) = iw_u.value;                                                                          \
    } while (0)
#define GET_HIGH_WORD(i, d)                                                                        \
    do {                                                                                           \
        ieee_double_shape_type gh_u;                                                               \
        gh_u.value = (d);                                                                          \
        (i) = gh_u.parts.msw;                                                                      \
    } while (0)

#define one (1.00000000000000000000e+00)
#define C1 (4.16666666666666019037e-02)
#define C2 (-1.38888888888741095749e-03)
#define C3 (2.48015872894767294178e-05)
#define C4 (-2.75573143513906633035e-07)
#define C5 (2.08757232129817482790e-09)
#define C6 (-1.13596475577881948265e-11)

double func_0018C880(double x, double y) {
    double a, hz, z, r, qx;
    __int32_t ix;
    GET_HIGH_WORD(ix, x);
    ix &= 0x7fffffff;      /* ix = |x|'s high word*/
    if (ix < 0x3e400000) { /* if x < 2**27 */
        if (((int)x) == 0)
            return one; /* generate inexact */
    }
    z = x * x;
    r = z * (C1 + z * (C2 + z * (C3 + z * (C4 + z * (C5 + z * C6)))));
    if (ix < 0x3FD33333) /* if |x| < 0.3 */
        return one - (0.5 * z - (z * r - x * y));
    else {
        if (ix > 0x3fe90000) { /* x > 0.78125 */
            qx = 0.28125;
        } else {
            INSERT_WORDS(qx, ix - 0x00200000, 0); /* x/4 */
        }
        hz = 0.5 * z - qx;
        a = one - qx;
        return a - (hz - (z * r - x * y));
    }
}
