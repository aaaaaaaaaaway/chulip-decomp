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

typedef struct {
    int v[7];
} Row;

extern int D_002DB540[];
extern Row D_001EACE0;
extern Row D_001EAD00;
extern Row D_001EAD20;
extern Row D_001EAD40;
extern Row D_001EAD60;

void *func_001923F4(void *dst, int c, int n);

int func_00113228(void *p, int n);

int func_00119840(void *dl, Params *p);

int func_00180748(char *dl, int idx) {
    Params pr;
    Row a0 = D_001EACE0;
    Row a1 = D_001EAD00;
    Row a2 = D_001EAD20;
    Row a3;
    Hdr *h;
    int n;
    int m;
    int i;

    func_001923F4(&a3, 0, 0x1C);
    a3.v[6] = 0x50;
    h = (Hdr *)dl;
    {
        Row a4 = D_001EAD40;
        Row a5 = D_001EAD60;

        dl += 0x10;
        h->f03 = 0x10;
        n = func_00113228(dl, 0x1B);
        dl = dl + n * 16;
        *(long *)(dl + 0x0) = 0x1000000000008001L;
        *(long *)(dl + 0x8) = 0xEL;
        *(long *)(dl + 0x18) = 0x42L;
        *(long *)(dl + 0x10) = 0x8000000044L;
        n = n + 2;
        dl += 0x20;
        pr.f00 = 0;
        pr.f0C = 0x07FFFFF0;
        pr.f2C = 0x80;
        pr.f2D = 0x80;
        pr.f2E = 0x80;
        pr.f24 = 1.0f;
        pr.f28 = 0.5f;
        pr.f2F = -0x80 - (D_002DB540[idx] << 7) / 0x2D;
        for (i = 0; i < 7; i++) {
            pr.f04 = (a0.v[i] + 0x700) << 4;
            pr.f08 = (a1.v[i] / 2 + 0x790) << 4;
            pr.f10 = a2.v[i] << 4;
            pr.f14 = a3.v[i] << 4;
            pr.f18 = a4.v[i] << 4;
            pr.f1C = a5.v[i] << 4;
            m = func_00119840(dl, &pr);
            n = n + m;
            dl = dl + m * 16;
        }
        if (D_002DB540[idx] < 0x2D) {
            D_002DB540[idx] = D_002DB540[idx] + 1;
        }
        h->f00 = n;
        return n + 1;
    }
}
