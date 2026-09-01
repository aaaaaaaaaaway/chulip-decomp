typedef struct {
    int cls;
    int sign;
    int exp;
    int pad;
    long mant;
} DoubleParts;

extern void func_001859D8(double *value, DoubleParts *out);
extern int func_00186188(DoubleParts *a, DoubleParts *b);

int func_001862A0(double x, double y) {
    DoubleParts px;
    DoubleParts py;
    double a;
    double b;

    a = x;
    b = y;
    func_001859D8(&a, &px);
    func_001859D8(&b, &py);
    return func_00186188(&px, &py);
}
