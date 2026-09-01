typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    int pad;
    unsigned long mant;
} DoubleParts;

extern void func_001859D8(double *value, DoubleParts *out);

unsigned int func_00186440(double x) {
    DoubleParts p;
    double a;

    a = x;
    func_001859D8(&a, &p);
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
    if (p.exp >= 0x3D) {
        return (unsigned int)(p.mant << (p.exp - 0x3C));
    }
    return (unsigned int)(p.mant >> (0x3C - p.exp));
}
