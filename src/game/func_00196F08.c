typedef struct Bigint {
    struct Bigint *_next;
    int _k;
    int _maxwds;
    int _sign;
    int _wds;
    unsigned int _x[1];
} Bigint;

typedef struct Reent {
    char pad0[0x4C];
    Bigint **_freelist;
} Reent;

extern void *func_00198140(Reent *ptr, unsigned int n, unsigned int size);

Bigint *func_00196F08(Reent *ptr, int k) {
    int x;
    Bigint *rv;

    if (ptr->_freelist == 0) {
        ptr->_freelist = (Bigint **)func_00198140(ptr, 4, 0x10);
        if (ptr->_freelist == 0) {
            return 0;
        }
    }
    rv = ptr->_freelist[k];
    if (rv != 0) {
        ptr->_freelist[k] = rv->_next;
    } else {
        x = 1 << k;
        rv = (Bigint *)func_00198140(ptr, 1, x * 4 + 0x14);
        if (rv == 0) {
            return 0;
        }
        rv->_k = k;
        rv->_maxwds = x;
    }
    rv->_wds = 0;
    rv->_sign = 0;
    return rv;
}
