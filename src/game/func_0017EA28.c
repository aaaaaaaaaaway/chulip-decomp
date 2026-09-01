typedef struct {
    char pad0[0x22];
    unsigned short f22;
    unsigned short f24;
    unsigned short f26;
} Surface;

typedef struct {
    Surface *p;
} SurfRef;

extern SurfRef D_001ED940;
Surface *func_0017D040();

int func_0017EA28(void) {
    D_001ED940.p = func_0017D040();
    switch (D_001ED940.p->f22) {
    case 0: case 1: case 2: case 10: case 27: case 36: case 44:
    case 48: case 49: case 50: case 58:
        return (D_001ED940.p->f24 * D_001ED940.p->f26) * 4;
    case 19: case 20:
        return D_001ED940.p->f24 * D_001ED940.p->f26;
    }
    return 0;
}
