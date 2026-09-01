typedef struct {
    char pad0[0x20];
    unsigned short f20;
    unsigned short f22;
    unsigned short f24;
    unsigned short f26;
    int f28;
} Surface;

typedef struct {
    Surface *p;
    int pad;
} SurfRef;

extern SurfRef D_001ED940;

Surface *func_0017D040();
int func_0017D830(int a, int b, int c);
int func_0017E840(int a, int b);
void func_00187A90(void *buf, short a, int b, short c, int d, int e, short f, short g);
void func_00198A20(int a);
void func_00187C78(void *buf, int addr);
void func_00187280(int a, int b);

void func_0017E330(int arg0, int arg1, int arg2) {
    int n;
    int r;
    int buf[0x18];

    D_001ED940.p = func_0017D040();
    if (D_001ED940.p->f20 == 0) {
        if ((unsigned int)(D_001ED940.p->f22 - 0x13) < 2) {
            n = ((D_001ED940.p->f24 + 127) / 128) * 2;
        } else {
            n = (D_001ED940.p->f24 + 63) / 64;
        }
        r = func_0017D830(n, D_001ED940.p->f22, D_001ED940.p->f26);
        r = func_0017E840(r << 6, 0);
        D_001ED940.p->f20 = r;
        func_00187A90(buf, r, n, D_001ED940.p->f22, 0, 0, D_001ED940.p->f24, D_001ED940.p->f26);
        func_00198A20(0);
        func_00187C78(buf, D_001ED940.p->f28 + (int)(((unsigned int)(arg1 * arg2) >> 4) << 4));
        func_00187280(0, 0);
    }
}
