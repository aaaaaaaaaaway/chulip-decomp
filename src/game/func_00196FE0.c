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
extern void *func_00192344(void *dest, const void *src, unsigned int n);

Bigint *func_00196FE0(Reent *ptr, Bigint *b, int m, int a) {
    int i;
    int wds;
    unsigned int *x;
    unsigned int y;
    unsigned int xi;
    unsigned int z;
    Bigint *b1;

    wds = b->_wds;
    x = b->_x;
    i = 0;
    do {
        xi = *x;
        y = (xi & 0xFFFF) * m + a;
        z = (xi >> 16) * m + (y >> 16);
        a = (int)(z >> 16);
        *x++ = (z << 16) + (y & 0xFFFF);
    } while (++i < wds);
    if (a != 0) {
        if (wds >= b->_maxwds) {
            b1 = func_00196F08(ptr, b->_k + 1);
            func_00192344(&b1->_sign, &b->_sign, b->_wds * 4 + 8);
            func_00196FB0(ptr, b);
            b = b1;
        }
        b->_x[wds++] = a;
        b->_wds = wds;
    }
    return b;
}
