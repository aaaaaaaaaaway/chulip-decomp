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
    unsigned char f2F;
} Params;

typedef struct {
    short f00;
    unsigned char pad;
    unsigned char f03;
} Hdr;

typedef struct {
    int r;
    int g;
    int b;
} Rgb;

typedef struct {
    Rgb c[2];
} Table;

typedef struct {
    int pad00[8];
    int f20;
    int f24;
    int f28;
} Obj;

extern Table D_001E9C60;
extern Table D_001E9C78;
/* Provisional single-source provider; original TU boundaries are unproved. */
int D_001ED4C0 __attribute__((section(".sbss"))) = 0;
extern int D_001ED4C8;
extern int D_001ED4CC;

int func_00113228(void *p, int n);
int func_00117E58(void *dl, Params *p);

int func_001606A0(char *dl, Obj *o) {
    Params pr;
    Table a = D_001E9C60;
    Table b = D_001E9C78;
    Hdr *h;
    int n;
    int m;
    int i;

    h = (Hdr *)dl;
    dl += 0x10;
    h->f03 = 0x10;
    n = func_00113228(dl, 0x19);
    dl = dl + n * 16;
    pr.f00 = 0;
    pr.f10 = 0x400;
    pr.f14 = 0xE00;
    pr.f18 = 0x200;
    pr.f1C = 0x200;
    pr.f2C = a.c[D_001ED4C8].r;
    pr.f2D = a.c[D_001ED4C8].g;
    pr.f2E = a.c[D_001ED4C8].b;
    pr.f2F = 0x50;
    pr.f24 = 1.0f;
    pr.f28 = 0.5f;
    pr.f04 = (o->f20 - 10) << 4;
    pr.f08 = (o->f24 + 14) << 4;
    pr.f0C = 0x07FFFFF0;
    for (i = 0; i < D_001ED4CC; i++) {
        pr.f04 = pr.f04 + 577.92f;
        m = func_00117E58(dl, &pr);
        n = n + m;
        dl = dl + m * 16;
    }
    if (D_001ED4CC < 8) {
        pr.f2C = b.c[D_001ED4C8].r;
        pr.f2D = b.c[D_001ED4C8].g;
        pr.f2E = b.c[D_001ED4C8].b;
        pr.f2F = ((D_001ED4C0 % 45) / 23) << 7;
        pr.f04 = pr.f04 + (577.92f + 4.48f);
        m = func_00117E58(dl, &pr);
        n = n + m;
        dl = dl + m * 16;
    }
    if (D_001ED4C8 == 0) {
        pr.f10 = 0xC00;
        pr.f04 = (o->f20 - 0x12) << 4;
    } else {
        pr.f10 = 0x800;
        pr.f04 = (o->f20 + o->f28 + 0x12) << 4;
    }
    pr.f08 = (o->f24 - 1) << 4;
    pr.f14 = 0xC00;
    pr.f18 = 0x400;
    pr.f1C = 0x400;
    pr.f2C = 0x80;
    pr.f2D = 0x80;
    pr.f2E = 0x80;
    pr.f2F = 0x80;
    m = func_00117E58(dl, &pr);
    n = n + m;
    *(short *)h = n;
    D_001ED4C0 = D_001ED4C0 + 1;
    return n + 1;
}
