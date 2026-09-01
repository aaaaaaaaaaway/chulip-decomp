typedef union {
    double d;
    long i;
} DoubleBits;

double func_0018EA78(double value, double sign) {
    DoubleBits v;
    DoubleBits s;
    int high;

    v.d = value;
    s.d = sign;
    high = ((int)(v.i >> 32) & 0x7FFFFFFF) | ((int)(s.i >> 32) & 0x80000000);
    v.i = (v.i & 0xFFFFFFFFL) | ((long)high << 32);
    return v.d;
}
