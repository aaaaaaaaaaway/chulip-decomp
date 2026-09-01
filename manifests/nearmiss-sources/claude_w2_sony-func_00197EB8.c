extern double func_00185D78(double a, double b);
extern double D_001EBFE0[];

double func_00197EB8(int n) {
    double r;

    if (n < 24) {
        return D_001EBFE0[n];
    }
    r = 1.0;
    while (n > 0) {
        r = func_00185D78(r, 10.0);
        n--;
    }
    return r;
}
