typedef enum {
    CLASS_SNAN,
    CLASS_QNAN,
    CLASS_ZERO,
    CLASS_NUMBER,
    CLASS_INFINITY
} fp_class_type;

typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    int pad;
    union {
        unsigned long ll;
        unsigned int l[2];
    } fraction;
} fp_number_type;

static __inline__ int isnan(fp_number_type *x)
{
    return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}

static __inline__ int isinf(fp_number_type *x)
{
    return x->class == CLASS_INFINITY;
}

static __inline__ int iszero(fp_number_type *x)
{
    return x->class == CLASS_ZERO;
}

int func_00186188(fp_number_type *a, fp_number_type *b)
{
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

extern void func_001859D8(double *value, fp_number_type *out);

int func_001862A0(double x, double y)
{
    fp_number_type a;
    fp_number_type b;
    double local_x;
    double local_y;

    local_x = x;
    local_y = y;
    func_001859D8(&local_x, &a);
    func_001859D8(&local_y, &b);
    return func_00186188(&a, &b);
}

extern double func_001858A8(fp_number_type *parts);

double func_001862F0(int value)
{
    fp_number_type parts;
    unsigned long mantissa;
    unsigned long shifted;
    int exponent;

    parts.class = CLASS_NUMBER;
    parts.sign = (unsigned int)value >> 31;
    if (value == 0) {
        parts.class = CLASS_ZERO;
    } else {
        parts.normal_exp = 0x3C;
        if (parts.sign != 0) {
            if (value == 0x80000000) {
                return -2147483648.0;
            }
            parts.fraction.ll = -value;
        } else {
            parts.fraction.ll = value;
        }
        mantissa = parts.fraction.ll;
        if (mantissa <= 0x0FFFFFFFFFFFFFFFUL) {
            exponent = parts.normal_exp;
            do {
                shifted = mantissa << 1;
                exponent--;
                mantissa = shifted;
            } while (shifted <= 0x0FFFFFFFFFFFFFFFUL);
            parts.normal_exp = exponent;
            parts.fraction.ll = shifted;
        }
    }
    return func_001858A8(&parts);
}
