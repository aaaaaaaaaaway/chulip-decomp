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

extern int func_00197240(unsigned int x);

double func_00197AF8(Bigint *a, int *e) {
    unsigned int *xa;
    unsigned int *xa0;
    unsigned int w;
    unsigned int y;
    unsigned int z;
    int k;
    DoubleBits d;

    xa0 = a->_x;
    xa = xa0 + a->_wds;
    y = *--xa;
    k = func_00197240(y);
    *e = 32 - k;
    if (k < 11) {
        d.parts.hi = 0x3FF00000 | y >> (11 - k);
        w = xa > xa0 ? *--xa : 0;
        d.parts.lo = y << (21 + k) | w >> (11 - k);
        goto ret_d;
    }
    z = xa > xa0 ? *--xa : 0;
    k -= 11;
    if (k != 0) {
        d.parts.hi = 0x3FF00000 | y << k | z >> (32 - k);
        y = xa > xa0 ? *--xa : 0;
        d.parts.lo = z << k | y >> (32 - k);
    } else {
        d.parts.hi = 0x3FF00000 | y;
        d.parts.lo = z;
    }
ret_d:
    return d.value;
}
