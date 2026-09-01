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
    struct { unsigned int lo, hi; } word;
} DoubleBits;

extern Bigint *func_00196F08(Reent *ptr, int k);
extern int func_00197868(Bigint *a, Bigint *b);

Bigint *func_001978D0(Reent *ptr, Bigint *a, Bigint *b) {
    int i;
    int wa;
    int wb;
    Bigint *c;
    int borrow;
    int y;
    int z;
    unsigned int *xa;
    unsigned int *xae;
    unsigned int *xb;
    unsigned int *xbe;
    unsigned int *xc;

    i = func_00197868(a, b);
    if (i == 0) {
        c = func_00196F08(ptr, 0);
        c->_wds = 1;
        c->_x[0] = 0;
        return c;
    }
    if (i < 0) {
        c = a;
        a = b;
        b = c;
        i = 1;
    } else {
        i = 0;
    }
    c = func_00196F08(ptr, a->_k);
    c->_sign = i;
    wa = a->_wds;
    xa = a->_x;
    xae = xa + wa;
    wb = b->_wds;
    xb = b->_x;
    xbe = xb + wb;
    xc = c->_x;
    borrow = 0;
    do {
        y = (*xa & 0xFFFF) - (*xb & 0xFFFF) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) - (*xb++ >> 16) + borrow;
        borrow = z >> 16;
        ((unsigned short *)xc)[1] = z;
        ((unsigned short *)xc)[0] = y;
        xc++;
    } while (xb < xbe);
    while (xa < xae) {
        y = (*xa & 0xFFFF) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) + borrow;
        borrow = z >> 16;
        ((unsigned short *)xc)[1] = z;
        ((unsigned short *)xc)[0] = y;
        xc++;
    }
    while (*--xc == 0) {
        wa--;
    }
    c->_wds = wa;
    return c;
}
