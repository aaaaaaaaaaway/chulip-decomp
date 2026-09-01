/* newlib __mcmp: compare two _Bigint magnitudes. */
typedef struct Bigint {
    struct Bigint *next;
    int k;
    int maxwds;
    int sign;
    int wds;
    unsigned int x[1];
} Bigint;

int func_00197868(Bigint *a, Bigint *b) {
    unsigned int *xa;
    unsigned int *xa0;
    unsigned int *xb;
    unsigned int *xb0;
    int i;
    int j;

    i = a->wds;
    j = b->wds;
    i -= j;
    if (i != 0) {
        return i;
    }
    xa0 = a->x;
    xa = xa0 + j;
    xb0 = b->x;
    xb = xb0 + j;
    for (;;) {
        if (*--xa != *--xb) {
            return *xa < *xb ? -1 : 1;
        }
        if (xa <= xa0) {
            break;
        }
    }
    return 0;
}
