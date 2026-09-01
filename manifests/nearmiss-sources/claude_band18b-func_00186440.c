typedef struct {
    int kind;
    int sign;
    int exponent;
    int pad;
    unsigned long mantissa;
} DoubleParts;

extern void func_001859D8(const double *value, DoubleParts *out);

unsigned int func_00186440(double value) {
    DoubleParts parts;
    double local = value;

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
    if (parts.exponent < 0x3D) {
        goto shift_right;
    }
    return (unsigned int)(int)(parts.mantissa << (parts.exponent - 0x3C));
shift_right:
    return (unsigned int)(int)(parts.mantissa >> (0x3C - parts.exponent));
}
