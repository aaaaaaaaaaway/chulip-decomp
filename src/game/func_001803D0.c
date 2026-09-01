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
extern int D_001EACE0[7];
extern int D_001EAD00[7];
extern int D_001EAD20[7];
extern int D_001EAD40[7];
extern int D_001EAD60[7];

void *memcpy(void *dst, const void *src, unsigned int len);
void *func_001923F4(void *dst, int value, unsigned int len);

int func_00113228(void *p, int n);

int func_00119840(void *dl, Params *p);

int func_001803D0(char *dl, int idx) {
    Params pr;
    int xs[7];
    int ys[7];
    int us[7];
    int vs[7];
    int ws[7];
    int hs[7];
    Hdr *h;
    int n;
    int r;
    int i;
    memcpy(xs, D_001EACE0, sizeof(xs));
    memcpy(ys, D_001EAD00, sizeof(ys));
    memcpy(us, D_001EAD20, sizeof(us));
    func_001923F4(vs, 0, sizeof(vs));
    vs[6] = 0x50;
    memcpy(ws, D_001EAD40, sizeof(ws));
    memcpy(hs, D_001EAD60, sizeof(hs));
    h = (Hdr *)dl;
    dl += 0x10;
    h->f03 = 0x10;
    n = func_00113228(dl, 0x1B);
    dl = dl + n * 16;
    *(long *)(dl + 0x0) = 0x1000000000008001L;
    *(long *)(dl + 0x8) = 0xEL;
    *(long *)(dl + 0x18) = 0x42L;
    *(long *)(dl + 0x10) = 0x8000000044L;
    dl += 0x20;
    n = n + 2;
    pr.f00 = 0;
    pr.f0C = 0x07FFFFF0;
    pr.f2C = 0x80;
    pr.f2D = 0x80;
    pr.f2E = 0x80;
    pr.f24 = 1.0f;
    pr.f28 = 0.5f;
    pr.f2F = (D_002DB540[idx] << 7) / 0x2D;
    for (i = 0; i < 7; i++) {
        pr.f04 = (xs[i] + 0x700) << 4;
        pr.f08 = (ys[i] / 2 + 0x790) << 4;
        pr.f10 = us[i] << 4;
        pr.f14 = vs[i] << 4;
        pr.f18 = ws[i] << 4;
        pr.f1C = hs[i] << 4;
        r = func_00119840(dl, &pr);
        n = n + r;
        dl = dl + r * 16;
    }
    if (D_002DB540[idx] < 0x2D) {
        D_002DB540[idx] = D_002DB540[idx] + 1;
    }
    h->f00 = n;
    return n + 1;
}
