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

Bigint *func_00197388(Reent *ptr, int i) {
    Bigint *b;

    b = func_00196F08(ptr, 1);
    b->_x[0] = i;
    b->_wds = 1;
    return b;
}
