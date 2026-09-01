extern double func_001862F0(int value);
extern double func_00185D78(double a, double b);
extern double func_00185CB8(double a, double b);

double func_00185810(long value) {
    double high;
    double low;
    int lo;

    high = func_00185D78(func_00185D78(func_001862F0((int)(value >> 32)), 65536.0), 65536.0);
    lo = (int)(value & 0xFFFFFFFF);
    low = func_001862F0(lo);
    if (lo < 0) {
        low = func_00185CB8(low, 4294967296.0);
    }
    return func_00185CB8(high, low);
}
