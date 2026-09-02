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
    union {
        unsigned int ll;
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

int func_00186D90(fp_number_type *a, fp_number_type *b)
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

extern void func_001866B0(float *value, fp_number_type *out);

int func_00186EA8(float x, float y)
{
    fp_number_type a;
    fp_number_type b;
    float local_x;
    float local_y;

    local_x = x;
    local_y = y;
    func_001866B0(&local_x, &a);
    func_001866B0(&local_y, &b);
    return func_00186D90(&a, &b);
}

extern float func_001865A0(fp_number_type *parts);

float func_00186EF8(int value)
{
    fp_number_type parts;

    parts.class = CLASS_NUMBER;
    parts.sign = value < 0;
    if (!value) {
        parts.class = CLASS_ZERO;
    } else {
        parts.normal_exp = 30;
        if (parts.sign) {
            if (value == (int)0x80000000) {
                return -2147483648.0;
            }
            parts.fraction.ll = -value;
        } else {
            parts.fraction.ll = value;
        }

        while (parts.fraction.ll < (1LL << 30)) {
            parts.fraction.ll <<= 1;
            parts.normal_exp -= 1;
        }
    }
    return func_001865A0(&parts);
}
