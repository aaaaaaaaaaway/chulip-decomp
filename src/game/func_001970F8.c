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
extern Bigint *func_00196FE0(Reent *ptr, Bigint *b, int m, int a);

Bigint *func_001970F8(Reent *ptr, const char *s, int nd0, int nd, unsigned int y9) {
    Bigint *b;
    int i;
    int k;
    int x;
    int y;

    x = (nd + 8) / 9;
    for (k = 0, y = 1; x > y; y <<= 1, k++) {
    }
    b = func_00196F08(ptr, k);
    b->_x[0] = y9;
    b->_wds = 1;
    i = 9;
    if (9 < nd0) {
        s += 9;
        do {
            b = func_00196FE0(ptr, b, 10, *s++ - '0');
        } while (++i < nd0);
        s++;
    } else {
        s += 10;
    }
    for (; i < nd; i++) {
        b = func_00196FE0(ptr, b, 10, *s++ - '0');
    }
    return b;
}
