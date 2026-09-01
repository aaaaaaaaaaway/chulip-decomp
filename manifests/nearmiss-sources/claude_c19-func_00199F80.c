typedef union { double d; long long ll; } DblBits;

int func_00199F80(double x) {
    DblBits u;
    long long e;
    unsigned long long m;

    u.d = x;
    e = (long long)((unsigned long long)(u.ll << 1) >> 53) - 0x433;
    if (e < -0x35) {
        return 0;
    }
    if (e >= 0xD) {
        return 0x270F;
    }
    m = ((unsigned long long)(u.ll << 12) >> 12) | 0x10000000000000LL;
    if (e < 0) {
        e = -e;
        m = m >> (int)(e - 2);
        if ((m & 3) == 3) {
            m = (m >> 2) + 1;
        } else {
            m = m >> 2;
        }
    } else {
        m = m << (int)e;
    }
    return (int)m;
}
