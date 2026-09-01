typedef struct Bigint {
    struct Bigint *_next;
    int _k;
    int _maxwds;
    int _sign;
    int _wds;
    unsigned int _x[1];
} Bigint;

typedef struct Reent Reent;

typedef union {
    double value;
    struct { unsigned int lo, hi; } parts;
} DoubleBits;

extern Bigint *func_00196F08(Reent *ptr, int k);
extern int func_001972C8(unsigned int *y);
extern int func_00197240(unsigned int x);

Bigint *func_00197C78(Reent *ptr, double dd, int *e, int *bits) {
    int de;
    Bigint *b;
    unsigned int *x;
    unsigned int y;
    unsigned int z;
    int i;
    int k;
    DoubleBits d;

    d.value = dd;
    b = func_00196F08(ptr, 1);
    x = b->_x;
    z = d.parts.hi & 0xFFFFF;
    d.parts.hi &= 0x7FFFFFFF;
    de = (int)(d.parts.hi >> 20);
    if (de != 0) {
        z |= 0x100000;
    }
    y = d.parts.lo;
    if (y != 0) {
        k = func_001972C8(&y);
        if (k != 0) {
            x[0] = y | z << (32 - k);
            z >>= k;
        } else {
            x[0] = y;
        }
        x[1] = z;
        i = b->_wds = z ? 2 : 1;
    } else {
        k = func_001972C8(&z);
        x[0] = z;
        i = b->_wds = 1;
        k += 32;
    }
    if (de != 0) {
        *e = de - 0x433 + k;
        *bits = 53 - k;
    } else {
        *e = de - 0x432 + k;
        *bits = 32 * i - func_00197240(x[i - 1]);
    }
    return b;
}
