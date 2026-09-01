typedef union {
    double d;
    struct { unsigned int lo; unsigned int hi; } parts;
} DblShape;

double func_00197A60(double x) {
    DblShape ux;
    DblShape a;
    int L;

    ux.d = x;
    L = (ux.parts.hi & 0x7FF00000) - 0x03400000;
    if (L > 0) {
        a.parts.hi = L;
        a.parts.lo = 0;
    } else {
        L = -L >> 20;
        if (L < 20) {
            a.parts.hi = 0x80000 >> L;
            a.parts.lo = 0;
        } else {
            a.parts.hi = 0;
            L -= 20;
            a.parts.lo = (L >= 31) ? 1 : (1 << (31 - L));
        }
    }
    return a.d;
}
