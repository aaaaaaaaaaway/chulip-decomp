typedef union {
    double value;
    struct { int lo, hi; } parts;
} DoubleBits;

double func_0018EA78(double x, double y) {
    int hx;
    int hy;

    {
        DoubleBits gh;
        gh.value = x;
        hx = gh.parts.hi;
    }
    {
        DoubleBits gh;
        gh.value = y;
        hy = gh.parts.hi;
    }
    {
        DoubleBits sh;
        sh.value = x;
        sh.parts.hi = (hx & 0x7FFFFFFF) | (hy & 0x80000000);
        x = sh.value;
    }
    return x;
}
