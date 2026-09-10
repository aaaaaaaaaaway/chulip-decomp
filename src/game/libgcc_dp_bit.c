/* This is a software floating point library which can be used instead of
   the floating point routines in libgcc1.c for targets without hardware
   floating point.
 Copyright (C) 1994, 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file with other programs, and to distribute
those programs without any restriction coming from the use of this
file.  (The General Public License restrictions do apply in other
respects; for example, they cover modification of the file, and
distribution when not linked into another program.)

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

/* Historical R5900 build macros: US_SOFTWARE_GOFAST, NO_DENORMALS, little-endian bit fields. */
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));
typedef int HItype __attribute__((mode(HI)));
typedef int SItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UHItype __attribute__((mode(HI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef UDItype fractype;
typedef USItype halffractype;
typedef DFtype FLO_type;
typedef DItype intfrac;
typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union {
        fractype ll;
        halffractype l[2];
    } fraction;
} fp_number_type;
typedef union {
    FLO_type value;
    fractype value_raw;
    halffractype words[2];
    struct {
        fractype fraction : 52 __attribute__((packed));
        unsigned int exp : 11 __attribute__((packed));
        unsigned int sign : 1 __attribute__((packed));
    } bits;
} FLO_union_type;
__inline__ static fp_number_type *nan() {
    extern fp_number_type D_002DE5F0;
    return &D_002DE5F0;
}
__inline__ static int isnan(fp_number_type *x) {
    return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}
__inline__ static int isinf(fp_number_type *x) { return x->class == CLASS_INFINITY; }
__inline__ static int iszero(fp_number_type *x) { return x->class == CLASS_ZERO; }
__inline__ static void flip_sign(fp_number_type *x) { x->sign = !x->sign; }
extern FLO_type func_001858A8(fp_number_type *);
FLO_type func_001858A8(fp_number_type *src) {
    FLO_union_type dst;
    fractype fraction = src->fraction.ll;
    int sign = src->sign;
    int exp = 0;
    if (isnan(src)) {
        exp = (0x7ff);
        if (src->class == CLASS_QNAN || 1) {
            fraction |= 0x8000000000000LL;
        }
    } else if (isinf(src)) {
        exp = (0x7ff);
        fraction = 0;
    } else if (iszero(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < (-(1023) + 1)) {
            int shift = (-(1023) + 1) - src->normal_exp;
            exp = 0;
            if (shift > 64 - 8L) {
                fraction = 0;
            } else {
                fraction >>= shift;
            }
            fraction >>= 8L;
        } else if (src->normal_exp > 1023) {
            exp = (0x7ff);
            fraction = 0;
        } else {
            exp = src->normal_exp + 1023;
            if ((fraction & 0xff) == 0x80) {
                if (fraction & (1 << 8L))
                    fraction += 0x7f + 1;
            } else {
                fraction += 0x7f;
            }
            if (fraction >= (1LL << (52 + 1 + 8L))) {
                fraction >>= 1;
                exp += 1;
            }
            fraction >>= 8L;
        }
    }
    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}
extern void func_001859D8(FLO_union_type *, fp_number_type *);
void func_001859D8(FLO_union_type *src, fp_number_type *dst) {
    fractype fraction;
    int exp;
    int sign;
    fraction = src->bits.fraction;
    exp = src->bits.exp;
    sign = src->bits.sign;
    dst->sign = sign;
    if (exp == 0) {
        if (fraction == 0 || 1) {
            dst->class = CLASS_ZERO;
        } else {
            dst->normal_exp = exp - 1023 + 1;
            fraction <<= 8L;
            dst->class = CLASS_NUMBER;
            while (fraction < (1LL << (52 + 8L))) {
                fraction <<= 1;
                dst->normal_exp--;
            }
            dst->fraction.ll = fraction;
        }
    } else if (exp == (0x7ff)) {
        if (fraction == 0) {
            dst->class = CLASS_INFINITY;
        } else {
            if (fraction & 0x8000000000000LL) {
                dst->class = CLASS_QNAN;
            } else {
                dst->class = CLASS_SNAN;
            }
            dst->fraction.ll = fraction;
        }
    } else {
        dst->normal_exp = exp - 1023;
        dst->class = CLASS_NUMBER;
        dst->fraction.ll = (fraction << 8L) | (1LL << (52 + 8L));
    }
}
static fp_number_type *func_00185A78(fp_number_type *a, fp_number_type *b, fp_number_type *tmp) {
    intfrac tfraction;
    int a_normal_exp;
    int b_normal_exp;
    fractype a_fraction;
    fractype b_fraction;
    if (isnan(a)) {
        return a;
    }
    if (isnan(b)) {
        return b;
    }
    if (isinf(a)) {
        if (isinf(b) && a->sign != b->sign)
            return nan();
        return a;
    }
    if (isinf(b)) {
        return b;
    }
    if (iszero(b)) {
        if (iszero(a)) {
            *tmp = *a;
            tmp->sign = a->sign & b->sign;
            return tmp;
        }
        return a;
    }
    if (iszero(a)) {
        return b;
    }
    {
        int diff;
        a_normal_exp = a->normal_exp;
        b_normal_exp = b->normal_exp;
        a_fraction = a->fraction.ll;
        b_fraction = b->fraction.ll;
        diff = a_normal_exp - b_normal_exp;
        if (diff < 0)
            diff = -diff;
        if (diff < 64) {
            while (a_normal_exp > b_normal_exp) {
                b_normal_exp++;
                { b_fraction = (b_fraction & 1) | (b_fraction >> 1); };
            }
            while (b_normal_exp > a_normal_exp) {
                a_normal_exp++;
                { a_fraction = (a_fraction & 1) | (a_fraction >> 1); };
            }
        } else {
            if (a_normal_exp > b_normal_exp) {
                b_normal_exp = a_normal_exp;
                b_fraction = 0;
            } else {
                a_normal_exp = b_normal_exp;
                a_fraction = 0;
            }
        }
    }
    if (a->sign != b->sign) {
        if (a->sign) {
            tfraction = -a_fraction + b_fraction;
        } else {
            tfraction = a_fraction - b_fraction;
        }
        if (tfraction >= 0) {
            tmp->sign = 0;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction.ll = tfraction;
        } else {
            tmp->sign = 1;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction.ll = -tfraction;
        }
        while (tmp->fraction.ll < (1LL << (52 + 8L)) && tmp->fraction.ll) {
            tmp->fraction.ll <<= 1;
            tmp->normal_exp--;
        }
    } else {
        tmp->sign = a->sign;
        tmp->normal_exp = a_normal_exp;
        tmp->fraction.ll = a_fraction + b_fraction;
    }
    tmp->class = CLASS_NUMBER;
    if (tmp->fraction.ll >= (1LL << (52 + 1 + 8L))) {
        {
            tmp->fraction.ll = (tmp->fraction.ll & 1) | (tmp->fraction.ll >> 1);
        };
        tmp->normal_exp++;
    }
    return tmp;
}
FLO_type func_00185CB8(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;
    func_001859D8((FLO_union_type *)&arg_a, &a);
    func_001859D8((FLO_union_type *)&arg_b, &b);
    res = func_00185A78(&a, &b, &tmp);
    return func_001858A8(res);
}
FLO_type func_00185D10(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;
    func_001859D8((FLO_union_type *)&arg_a, &a);
    func_001859D8((FLO_union_type *)&arg_b, &b);
    b.sign ^= 1;
    res = func_00185A78(&a, &b, &tmp);
    return func_001858A8(res);
}
static __inline__ fp_number_type *_fpmul_parts(fp_number_type *a, fp_number_type *b,
                                               fp_number_type *tmp) {
    fractype low = 0;
    fractype high = 0;
    if (isnan(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isnan(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    if (isinf(a)) {
        if (iszero(b))
            return nan();
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isinf(b)) {
        if (iszero(a)) {
            return nan();
        }
        b->sign = a->sign != b->sign;
        return b;
    }
    if (iszero(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (iszero(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    {
        {
            UDItype nl = a->fraction.ll & 0xffffffff;
            UDItype nh = a->fraction.ll >> 32;
            UDItype ml = b->fraction.ll & 0xffffffff;
            UDItype mh = b->fraction.ll >> 32;
            UDItype pp_ll = ml * nl;
            UDItype pp_hl = mh * nl;
            UDItype pp_lh = ml * nh;
            UDItype pp_hh = mh * nh;
            UDItype res2 = 0;
            UDItype res0 = 0;
            UDItype ps_hh__ = pp_hl + pp_lh;
            if (ps_hh__ < pp_hl)
                res2 += 0x100000000LL;
            pp_hl = (ps_hh__ << 32) & 0xffffffff00000000LL;
            res0 = pp_ll + pp_hl;
            if (res0 < pp_ll)
                res2++;
            res2 += ((ps_hh__ >> 32) & 0xffffffffL) + pp_hh;
            high = res2;
            low = res0;
        }
    }
    tmp->normal_exp = a->normal_exp + b->normal_exp;
    tmp->sign = a->sign != b->sign;
    tmp->normal_exp += 4;
    while (high >= (1LL << (52 + 1 + 8L))) {
        tmp->normal_exp++;
        if (high & 1) {
            low >>= 1;
            low |= 0x8000000000000000LL;
        }
        high >>= 1;
    }
    while (high < (1LL << (52 + 8L))) {
        tmp->normal_exp--;
        high <<= 1;
        if (low & 0x8000000000000000LL)
            high |= 1;
        low <<= 1;
    }
    if ((high & 0xff) == 0x80) {
        if (high & (1 << 8L)) {
            high += 0x7f + 1;
        } else if (low) {
            high += 0x7f + 1;
        }
    }
    tmp->fraction.ll = high;
    tmp->class = CLASS_NUMBER;
    return tmp;
}
FLO_type func_00185D78(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;
    func_001859D8((FLO_union_type *)&arg_a, &a);
    func_001859D8((FLO_union_type *)&arg_b, &b);
    res = _fpmul_parts(&a, &b, &tmp);
    return func_001858A8(res);
}
static __inline__ fp_number_type *_fpdiv_parts(fp_number_type *a, fp_number_type *b) {
    fractype bit;
    fractype numerator;
    fractype denominator;
    fractype quotient;
    if (isnan(a)) {
        return a;
    }
    if (isnan(b)) {
        return b;
    }
    a->sign = a->sign ^ b->sign;
    if (isinf(a) || iszero(a)) {
        if (a->class == b->class)
            return nan();
        return a;
    }
    if (isinf(b)) {
        a->fraction.ll = 0;
        a->normal_exp = 0;
        return a;
    }
    if (iszero(b)) {
        a->class = CLASS_INFINITY;
        return a;
    }
    {
        a->normal_exp = a->normal_exp - b->normal_exp;
        numerator = a->fraction.ll;
        denominator = b->fraction.ll;
        if (numerator < denominator) {
            numerator *= 2;
            a->normal_exp--;
        }
        bit = (1LL << (52 + 8L));
        quotient = 0;
        while (bit) {
            if (numerator >= denominator) {
                quotient |= bit;
                numerator -= denominator;
            }
            bit >>= 1;
            numerator *= 2;
        }
        if ((quotient & 0xff) == 0x80) {
            if (quotient & (1 << 8L)) {
                quotient += 0x7f + 1;
            } else if (numerator) {
                quotient += 0x7f + 1;
            }
        }
        a->fraction.ll = quotient;
        return (a);
    }
}
FLO_type func_00186020(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type *res;
    func_001859D8((FLO_union_type *)&arg_a, &a);
    func_001859D8((FLO_union_type *)&arg_b, &b);
    res = _fpdiv_parts(&a, &b);
    return func_001858A8(res);
}
int func_00186188(fp_number_type *a, fp_number_type *b);
int func_00186188(fp_number_type *a, fp_number_type *b) {
    if (isnan(a) || isnan(b)) {
        return 1;
    }
    if (isinf(a) && isinf(b)) {
        return b->sign - a->sign;
    }
    if (isinf(a)) {
        return a->sign ? -1 : 1;
    }
    if (isinf(b)) {
        return b->sign ? 1 : -1;
    }
    if (iszero(a) && iszero(b)) {
        return 0;
    }
    if (iszero(a)) {
        return b->sign ? 1 : -1;
    }
    if (iszero(b)) {
        return a->sign ? -1 : 1;
    }
    if (a->sign != b->sign) {
        return a->sign ? -1 : 1;
    }
    if (a->normal_exp > b->normal_exp) {
        return a->sign ? -1 : 1;
    }
    if (a->normal_exp < b->normal_exp) {
        return a->sign ? 1 : -1;
    }
    if (a->fraction.ll > b->fraction.ll) {
        return a->sign ? -1 : 1;
    }
    if (a->fraction.ll < b->fraction.ll) {
        return a->sign ? 1 : -1;
    }
    return 0;
}
SItype func_001862A0(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    func_001859D8((FLO_union_type *)&arg_a, &a);
    func_001859D8((FLO_union_type *)&arg_b, &b);
    return func_00186188(&a, &b);
}
FLO_type func_001862F0(SItype arg_a) {
    fp_number_type in;
    in.class = CLASS_NUMBER;
    in.sign = arg_a < 0;
    if (!arg_a) {
        in.class = CLASS_ZERO;
    } else {
        in.normal_exp = 52 + 8L;
        if (in.sign) {
            if (arg_a == (SItype)0x80000000) {
                return -2147483648.0;
            }
            in.fraction.ll = (-arg_a);
        } else
            in.fraction.ll = arg_a;
        while (in.fraction.ll < (1LL << (52 + 8L))) {
            in.fraction.ll <<= 1;
            in.normal_exp -= 1;
        }
    }
    return func_001858A8(&in);
}
SItype func_001863A8(FLO_type arg_a) {
    fp_number_type a;
    SItype tmp;
    func_001859D8((FLO_union_type *)&arg_a, &a);
    if (iszero(&a))
        return 0;
    if (isnan(&a))
        return 0;
    if (isinf(&a))
        return a.sign ? (-((SItype)((unsigned)(~0) >> 1))) - 1 : ((SItype)((unsigned)(~0) >> 1));
    if (a.normal_exp < 0)
        return 0;
    if (a.normal_exp > 30)
        return a.sign ? (-((SItype)((unsigned)(~0) >> 1))) - 1 : ((SItype)((unsigned)(~0) >> 1));
    tmp = a.fraction.ll >> ((52 + 8L) - a.normal_exp);
    return a.sign ? (-tmp) : (tmp);
}
USItype func_00186440(FLO_type arg_a) {
    fp_number_type a;
    func_001859D8((FLO_union_type *)&arg_a, &a);
    if (iszero(&a))
        return 0;
    if (isnan(&a))
        return 0;
    if (a.sign)
        return 0;
    if (isinf(&a))
        return ((USItype)~0);
    if (a.normal_exp < 0)
        return 0;
    if (a.normal_exp > 31)
        return ((USItype)~0);
    else if (a.normal_exp > (52 + 8L))
        return a.fraction.ll << (a.normal_exp - (52 + 8L));
    else
        return a.fraction.ll >> ((52 + 8L) - a.normal_exp);
}
FLO_type func_001864E0(FLO_type arg_a) {
    fp_number_type a;
    func_001859D8((FLO_union_type *)&arg_a, &a);
    flip_sign(&a);
    return func_001858A8(&a);
}
extern SFtype func_00187110(fp_class_type, unsigned int, int, USItype);
DFtype func_00186518(fp_class_type class, unsigned int sign, int exp, UDItype frac) {
    fp_number_type in;
    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction.ll = frac;
    return func_001858A8(&in);
}
SFtype func_00186548(DFtype arg_a) {
    fp_number_type in;
    USItype sffrac;
    func_001859D8((FLO_union_type *)&arg_a, &in);
    sffrac = in.fraction.ll >> (52 + 8 - (23 + 7));
    if ((in.fraction.ll & (((USItype)1 << (52 + 8 - (23 + 7))) - 1)) != 0)
        sffrac |= 1;
    return func_00187110(in.class, in.sign, in.normal_exp, sffrac);
}
