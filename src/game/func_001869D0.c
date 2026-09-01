typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    unsigned int mant;
} FloatParts;

extern void func_001866B0(float *value, FloatParts *out);
extern int func_00186740(FloatParts *a, FloatParts *b, FloatParts *r);
extern float func_001865A0(int r);

float func_001869D0(float x, float y) {
    FloatParts px;
    FloatParts py;
    FloatParts pr;
    float a;
    float b;

    a = x;
    b = y;
    func_001866B0(&a, &px);
    func_001866B0(&b, &py);
    py.sign = py.sign ^ 1;
    return func_001865A0(func_00186740(&px, &py, &pr));
}
