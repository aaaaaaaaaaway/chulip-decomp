typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    unsigned int mant;
} FloatParts;

extern void func_001866B0(float *value, FloatParts *out);
extern int func_00186D90(FloatParts *a, FloatParts *b);

int func_00186EA8(float x, float y) {
    FloatParts px;
    FloatParts py;
    float a;
    float b;

    a = x;
    b = y;
    func_001866B0(&a, &px);
    func_001866B0(&b, &py);
    return func_00186D90(&px, &py);
}
