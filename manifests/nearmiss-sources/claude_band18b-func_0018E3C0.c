typedef union {
    double d;
    long i;
} DoubleBits;

double func_0018E3C0(double value) {
    DoubleBits u;
    int high;

    u.d = value;
    high = (int)(u.i >> 32) & 0x7FFFFFFF;
    u.i = (u.i & 0xFFFFFFFFL) | ((long)high << 32);
    return u.d;
}
