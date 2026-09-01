typedef struct {
    int pad0[5];
    char *f14;
    int f18;
    char *f1C;
    int f20;
    int f24;
} S;

char *func_0019B1B0(S *p) {
    int i = p->f24 % p->f18;
    char *result = p->f14 + i * 64;

    p->f24 = i + 1;
    return result;
}

char *func_0019B1E0(S *p, int i) {
    if (i < 0 || i >= p->f20) {
        return func_0019B1B0(p);
    }
    return p->f1C + i * 64;
}
