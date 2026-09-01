typedef struct Bigint {
    struct Bigint *_next;
    int _k;
    int _maxwds;
    int _sign;
    int _wds;
    unsigned int _x[1];
} Bigint;

typedef union {
    double value;
    struct { int lo, hi; } parts;
} DoubleBits;

extern double func_00197AF8(Bigint *b, int *e);
extern double func_00186020(double a, double b);

double func_00197DF8(Bigint *a, Bigint *b) {
    DoubleBits da;
    DoubleBits db;
    int k;
    int ka;
    int kb;

    da.value = func_00197AF8(a, &ka);
    db.value = func_00197AF8(b, &kb);
    k = ka - kb + 32 * (a->_wds - b->_wds);
    if (k > 0) {
        da.parts.hi += k * 0x100000;
    } else {
        k = -k;
        db.parts.hi += k * 0x100000;
    }
    return func_00186020(da.value, db.value);
}
