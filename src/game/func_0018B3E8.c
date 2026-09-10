
/* @(#)w_sqrt.c 5.1 93/09/24 */
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
        <<sqrt>>, <<sqrtf>>---positive square root

INDEX
        sqrt
INDEX
        sqrtf

ANSI_SYNOPSIS
        #include <math.h>
        double func_0018B3E8(double <[x]>);
        float  sqrtf(float <[x]>);

TRAD_SYNOPSIS
        #include <math.h>
        double func_0018B3E8(<[x]>);
        float  sqrtf(<[x]>);

DESCRIPTION
        <<sqrt>> computes the positive square root of the argument.
        You can modify error handling for this function with
        <<func_0018E608>>.

RETURNS
        On success, the square root is returned. If <[x]> is real and
        positive, then the result is positive.  If <[x]> is real and
        negative, the global value <<errno>> is set to <<EDOM>> (domain error).


PORTABILITY
        <<sqrt>> is ANSI C.  <<sqrtf>> is an extension.
*/

/*
 * wrapper func_0018B3E8(x)
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
extern double func_0018BC30(double);
extern int func_0018E5D0(double);
struct exception {
    int type;
    char *name;
    double arg1, arg2, retval;
    int err;
};
enum __fdlibm_version { __fdlibm_ieee = -1, __fdlibm_svid, __fdlibm_xopen, __fdlibm_posix };
extern const enum __fdlibm_version D_001EB988;
extern int func_0018E608(struct exception *);
extern int *func_00191698(void);
#define _LIB_VERSION D_001EB988
#define _IEEE_ __fdlibm_ieee
#define _SVID_ __fdlibm_svid
#define _POSIX_ __fdlibm_posix
#define DOMAIN 1
#define EDOM 33
#define errno (*func_00191698())

double func_0018B3E8(double x) /* wrapper sqrt */
{
    struct exception exc;
    double z;
    z = func_0018BC30(x);
    if (_LIB_VERSION == _IEEE_ || func_0018E5D0(x))
        return z;
    if (x < 0.0) {
        exc.type = DOMAIN;
        exc.name = "sqrt";
        exc.err = 0;
        exc.arg1 = exc.arg2 = x;
        if (_LIB_VERSION == _SVID_)
            exc.retval = 0.0;
        else
            exc.retval = 0.0 / 0.0;
        if (_LIB_VERSION == _POSIX_)
            errno = EDOM;
        else if (!func_0018E608(&exc)) {
            errno = EDOM;
        }
        if (exc.err != 0)
            errno = exc.err;
        return exc.retval;
    } else
        return z;
}
