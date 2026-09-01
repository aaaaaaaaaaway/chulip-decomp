typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    int mant;
} FloatParts;

extern void func_001866B0(float *value, FloatParts *out);
extern int func_00186518(unsigned int cls, int sign, int exp, unsigned long mant);

int func_00187140(float x) {
    FloatParts p;
    float a;

    a = x;
    func_001866B0(&a, &p);
    return func_00186518(p.cls, p.sign, p.exp, (unsigned long)((long)p.mant << 32) >> 2);
}
