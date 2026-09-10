/* sf_cos.c -- float version of s_cos.c.
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
extern float func_0018E2B8(float, float, int);
extern float func_0018D810(float, float);
extern int func_0018C368(float, float *);
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

#define one ((float)1.0)

float func_0018B210(float x) {
    float y[2], z = 0.0;
    __int32_t n, ix;

    GET_FLOAT_WORD(ix, x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if (ix <= 0x3f490fd8)
        return func_0018D810(x, z);

    /* cos(Inf or NaN) is NaN */
    else if (ix >= 0x7f800000)
        return x - x;

    /* argument reduction needed */
    else {
        n = func_0018C368(x, y);
        switch (n & 3) {
        case 0:
            return func_0018D810(y[0], y[1]);
        case 1:
            return -func_0018E2B8(y[0], y[1], 1);
        case 2:
            return -func_0018D810(y[0], y[1]);
        default:
            return func_0018E2B8(y[0], y[1], 1);
        }
    }
}
