typedef struct {
    int kind;
    int sign;
    int exponent;
    int mantissa;
} FloatParts;

extern void func_001866B0(const float *value, FloatParts *out);

unsigned int func_00187040(float value) {
    FloatParts parts;
    float local = value;

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
    if (parts.sign != 0) {
        return 0;
    }
    if ((parts.kind ^ 4) == 0) {
        goto saturate;
    }
    if (parts.exponent < 0) {
        goto zero;
    }
    if (parts.exponent < 0x20) {
        goto small;
    }
saturate:
    return 0xFFFFFFFF;
small:
    if (parts.exponent < 0x1F) {
        goto shift_right;
    }
    return (unsigned int)parts.mantissa << (parts.exponent - 0x1E);
shift_right:
    return (unsigned int)parts.mantissa >> (0x1E - parts.exponent);
}
