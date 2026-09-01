/*
 * Derived from newlib 1.9.0 vfprintf.c, whose formatting core is derived
 * from software contributed to Berkeley by Chris Torek. Redistribution and
 * use in source and binary forms, with or without modification, are permitted
 * provided that the original copyright notice and disclaimer are retained.
 * This software is provided by the Regents and contributors "as is", without
 * express or implied warranties.
 *
 * The floating-point union follows David M. Gay's vfieeefp.h. Permission to
 * use, copy, modify, and distribute that software for any purpose without fee
 * is granted when its notice is retained. That software is also provided
 * "as is", without warranty.
 */

typedef unsigned int u32;

struct Reent;

union DoubleBits {
    double d;
    u32 words[2];
};

extern char *func_00194C78(
    struct Reent *data,
    double value,
    int mode,
    int ndigits,
    int *decpt,
    int *sign,
    char **end);
extern double func_00185D10(double left, double right);
extern int func_001862A0(double left, double right);

char *func_001946C0(
    struct Reent *data,
    double value,
    int ndigits,
    int flags,
    char *sign,
    int *decpt,
    int ch,
    int *length) {
    int mode;
    int dtoa_sign;
    char *digits;
    char *limit;
    char *end;
    union DoubleBits bits;

    if (ch == 'f') {
        mode = 3;
    } else {
        if (ch == 'e' || ch == 'E') {
            ndigits++;
        }
        mode = 2;
    }

    bits.d = value;
    if (bits.words[1] & 0x80000000U) {
        value = func_00185D10(0.0, value);
        *sign = '-';
    } else {
        *sign = '\0';
    }

    digits = func_00194C78(
        data, value, mode, ndigits, decpt, &dtoa_sign, &end);

    if ((ch != 'g' && ch != 'G') || (flags & 1)) {
        limit = digits + ndigits;
        if (ch == 'f') {
            if (*digits == '0' && func_001862A0(value, 0.0)) {
                *decpt = -ndigits + 1;
            }
            limit += *decpt;
        }
        if (!func_001862A0(value, 0.0)) {
            end = limit;
        }
        while (end < limit) {
            *end++ = '0';
        }
    }

    *length = end - digits;
    return digits;
}
