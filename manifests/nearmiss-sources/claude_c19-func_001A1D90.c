extern int func_001862A0(double a, double b);
extern double func_00185D78(double a, double b);
extern double func_00185D10(double a, double b);
extern double func_00185CB8(double a, double b);
extern double func_00185810(long long v);
extern unsigned int func_00186440(double v);

unsigned long long func_001A1D90(double x) {
    unsigned long long r;
    double d;
    double z;
    double f;
    unsigned int hi;

    if (func_001862A0(x, 0.0) < 0) {
        return 0;
    }
    hi = func_00186440(func_00185D78(x, 2.3283064365386963e-10));
    r = (unsigned long long)hi << 32;
    if ((long long)r < 0) {
        d = func_00185810((long long)((r >> 1) | (r & 1)));
        d = func_00185CB8(d, d);
    } else {
        d = func_00185810((long long)r);
    }
    f = func_00185D10(x, d);
    z = 0.0;
    if (func_001862A0(f, z) >= 0) {
        r = r + func_00186440(f);
    } else {
        r = r - func_00186440(func_00185D10(z, f));
    }
    return r;
}
