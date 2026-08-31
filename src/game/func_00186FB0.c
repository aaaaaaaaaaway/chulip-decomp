typedef struct {
    int kind;
    int sign;
    int exponent;
    int mantissa;
} FloatParts;

extern void func_001866B0(const float *value, FloatParts *out);

int func_00186FB0(float value) {
    FloatParts parts;
    float local = value;
    int shift;
    int result;

    func_001866B0(&local, &parts);
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
    shift = 0x1E - parts.exponent;
    result = (int)((unsigned int)parts.mantissa >> shift);
    return parts.sign ? -result : result;
}
