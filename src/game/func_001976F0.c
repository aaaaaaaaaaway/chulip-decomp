typedef struct Bigint {
    struct Bigint *_next;
    int _k;
    int _maxwds;
    int _sign;
    int _wds;
    unsigned int _x[1];
} Bigint;

typedef struct Reent Reent;

extern Bigint *func_00196F08(Reent *ptr, int k);
extern void func_00196FB0(Reent *ptr, Bigint *b);

Bigint *func_001976F0(Reent *ptr, Bigint *b, int k) {
    int i;
    int k1;
    int n;
    int n1;
    Bigint *b1;
    unsigned int *x;
    unsigned int *x1;
    unsigned int *xe;
    unsigned int z;

    n = k >> 5;
    k1 = b->_k;
    n1 = n + b->_wds + 1;
    for (i = b->_maxwds; n1 > i; i <<= 1) {
        k1++;
    }
    b1 = func_00196F08(ptr, k1);
    x1 = b1->_x;
    for (i = 0; i < n; i++) {
        *x1++ = 0;
    }
    x = b->_x;
    xe = x + b->_wds;
    k &= 0x1F;
    if (k != 0) {
        k1 = 32 - k;
        z = 0;
        do {
            *x1++ = *x << k | z;
            z = *x++ >> k1;
        } while (x < xe);
        *x1 = z;
        if (z != 0) {
            ++n1;
        }
    } else {
        do {
            *x1++ = *x++;
        } while (x < xe);
    }
    b1->_wds = n1 - 1;
    func_00196FB0(ptr, b);
    return b1;
}
