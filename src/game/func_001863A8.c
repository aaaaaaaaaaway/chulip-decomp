typedef struct {
    int kind;
    int sign;
    int exponent;
    int pad;
    unsigned long mantissa;
} DoubleParts;

extern void func_001859D8(const double *value, DoubleParts *out);

int func_001863A8(double value) {
    DoubleParts parts;
    double local = value;
    int shift;
    int result;

    func_001859D8(&local, &parts);
    if ((parts.kind ^ 2) == 0) {
        goto zero;
    }
    if ((unsigned int)parts.kind >= 2) {
        goto classified;
    }
zero:
    return 0;
classified:
    if ((parts.kind ^ 4) == 0) {
        goto saturate;
    }
    if (parts.exponent < 0) {
        goto zero;
    }
    if (parts.exponent < 0x1F) {
        goto convert;
    }
saturate:
    return parts.sign ? 0x80000000 : 0x7FFFFFFF;
convert:
    shift = 0x3C - parts.exponent;
    result = (int)(parts.mantissa >> shift);
    return parts.sign ? -result : result;
}
