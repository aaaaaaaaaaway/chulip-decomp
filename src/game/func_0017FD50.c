typedef struct {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    float f24;
    float f28;
    unsigned char f2C;
    unsigned char f2D;
    unsigned char f2E;
    signed char f2F;
} Params;

typedef struct {
    short f00;
    unsigned char pad;
    unsigned char f03;
} Hdr;

extern int D_002DB540[];

int func_00113228(void *p, int n);
int func_00119840(void *dl, Params *p);

int func_0017FD50(char *dl, int idx) {
    Params pr;
    Hdr *h;
    int n;

    h = (Hdr *)dl;
    dl += 0x10;
    h->f03 = 0x10;
    n = func_00113228(dl, 0x1C);
    dl = dl + n * 16;
    *(long *)(dl + 0x0) = 0x1000000000008001L;
    *(long *)(dl + 0x8) = 0xEL;
    *(long *)(dl + 0x18) = 0x42L;
    *(long *)(dl + 0x10) = 0x8000000044L;
    n = n + 2;
    pr.f04 = 0x7800;
    pr.f00 = 0;
    pr.f10 = 0;
    pr.f08 = 0x7B20;
    pr.f0C = 0x07FFFFF0;
    pr.f18 = 0x1000;
    pr.f14 = 0;
    pr.f1C = 0x600;
    pr.f2C = 0x80;
    pr.f2D = 0x80;
    pr.f2E = 0x80;
    pr.f2F = -0x80 - (D_002DB540[idx] << 7) / 0x2D;
    pr.f24 = 1.0f;
    pr.f28 = 0.5f;
    n = n + func_00119840(dl + 0x20, &pr);
    h->f00 = n;
    return n + 1;
}
