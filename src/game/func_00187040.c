typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    unsigned int mant;
} FloatParts;

extern void func_001866B0(float *value, FloatParts *out);

unsigned int func_00187040(float x) {
    FloatParts p;
    float a;

    a = x;
    func_001866B0(&a, &p);
    if ((p.cls ^ 2) == 0) {
        return 0;
    }
    if (p.cls < 2) {
        return 0;
    }
    if (p.sign != 0) {
        return 0;
    }
    if ((p.cls ^ 4) == 0) {
        return 0xFFFFFFFFU;
    }
    if (p.exp < 0) {
        return 0;
    }
    if (p.exp >= 32) {
        return 0xFFFFFFFFU;
    }
    if (p.exp >= 0x1F) {
        return p.mant << (p.exp - 0x1E);
    }
    return p.mant >> (0x1E - p.exp);
}
