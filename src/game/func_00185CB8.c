typedef struct {
    unsigned int cls;
    int sign;
    int exp;
    int pad;
    unsigned long mant;
} DoubleParts;

extern void func_001859D8(double *value, DoubleParts *out);

extern int func_00185A78(DoubleParts *a, DoubleParts *b, DoubleParts *r);
extern double func_001858A8(int r);

double func_00185CB8(double x, double y) {
    DoubleParts px;
    DoubleParts py;
    DoubleParts pr;
    double a;
    double b;

    a = x;
    b = y;
    func_001859D8(&a, &px);
    func_001859D8(&b, &py);
    return func_001858A8(func_00185A78(&px, &py, &pr));
}
