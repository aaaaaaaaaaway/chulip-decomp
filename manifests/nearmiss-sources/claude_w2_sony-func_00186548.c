typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    int pad;
    unsigned long mant;
} DoubleParts;

extern void func_001859D8(double *value, DoubleParts *out);

extern int func_00187110(unsigned int cls, int sign, int exp, int mant);

int func_00186548(double x) {
    DoubleParts p;
    double a;
    int m;

    a = x;
    func_001859D8(&a, &p);
    m = (int)(p.mant << 2);
    return func_00187110(p.cls, p.sign, p.exp, (p.mant & 0x3FFFFFFF) != 0 ? m | 1 : m);
}
