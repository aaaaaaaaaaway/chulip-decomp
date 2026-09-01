typedef union {
    double value;
    struct { int lo, hi; } parts;
} DoubleBits;

double func_0018E3C0(double x) {
    DoubleBits gh;
    DoubleBits sh;
    int high;

    gh.value = x;
    sh.value = x;
    high = gh.parts.hi;
    sh.parts.hi = high & 0x7FFFFFFF;
    return sh.value;
}
