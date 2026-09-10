/* wf_sqrt.c -- float version of w_sqrt.c.
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
 * wrapper func_0018B5F8(x)
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
extern float func_0018C748(float);
extern int func_0018E8F0(float);
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

float func_0018B5F8(float x) /* wrapper sqrtf */
{
    float z;
    struct exception exc;
    z = func_0018C748(x);
    if (_LIB_VERSION == _IEEE_ || func_0018E8F0(x))
        return z;
    if (x < (float)0.0) {
        /* func_0018B5F8(negative) */
        exc.type = DOMAIN;
        exc.name = "sqrtf";
        exc.err = 0;
        exc.arg1 = exc.arg2 = (double)x;
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
        return (float)exc.retval;
    } else
        return z;
}
