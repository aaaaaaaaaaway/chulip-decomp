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
    float x;
    float y;
    float z;
    float w;
} Vec4f;

extern int D_001ED89C;
extern int D_001ED8A8;
extern int D_001ED8C4;
extern int D_001ED8C8;
extern int D_001ED8CC;
extern float D_001EDCC0[];

int func_0012CC18(int index, unsigned char field, void *buffer);
void func_00158868(unsigned short id, Vec4f *out);
void func_00120BE0(int *out, float *proj, Vec4f *src);
int func_00119840(void *dl, Params *p);
int func_00117E58(void *dl, Params *p);
int func_00113228(void *dl, int n);
int func_00113A00(void *dl, int handle, int a, int b, int c, int d, int e);

int func_0017B5E0(char *dl, int mode) {
    Params pr;
    Vec4f pos;
    int out[4];
    Hdr *h;
    int n;
    int r;
    int index;
    int handle;
    int lim;

    if (mode < 0) {
        return 0;
    }
    index = -1;
    switch (D_001ED89C) {
    case 0:
        index = ((unsigned char *)(D_001ED8C8 + D_001ED8A8))[2];
        break;
    case 1:
        index = ((unsigned char *)(D_001ED8CC + D_001ED8A8))[2];
        break;
    }
    handle = func_0012CC18(index, 9, 0);

    h = (Hdr *)dl;
    dl += 0x10;
    pr.f00 = 0;
    pr.f0C = 0x07FFFFF0;
    pr.f2C = 0x80;
    pr.f2D = 0x80;
    pr.f2E = 0x80;
    pr.f2F = 0x80;
    pr.f24 = 1.0f;
    pr.f28 = 0.5f;
    h->f03 = 0x10;
    *(long *)(dl + 0x00) = 0x1000000000008001L;
    *(long *)(dl + 0x08) = 0xEL;
    *(long *)(dl + 0x18) = 0x42L;
    *(long *)(dl + 0x10) = 0x8000000044L;
    dl += 0x20;
    n = 2;

    pr.f04 = 0x8500;
    pr.f08 = 0x7B60;
    pr.f10 = 0x600;
    pr.f14 = 0xC00;
    pr.f18 = 0x600;
    pr.f1C = 0x400;
    pr.f24 = 1.7f;
    pr.f28 = 0.5f;
    r = func_00119840(dl, &pr);
    n = n + r;
    dl = dl + r * 16;

    if (mode == 5) {
        func_00158868(*(unsigned short *)D_001ED8C4, &pos);
        pos.w = 1.0f;
        func_00120BE0(out, D_001EDCC0, &pos);
        out[0] = out[0] + 0x140;
        lim = 0x8C80;
        if (out[0] > lim) {
            out[0] = lim;
        } else {
            lim = 0x8640;
            if (out[0] < lim) {
                out[0] = lim;
            }
        }
        pr.f00 = 1;
        pr.f04 = out[0];
        pr.f08 = 0x7DC0;
        pr.f10 = 0;
        pr.f14 = 0xC00;
        pr.f18 = 0x200;
        pr.f1C = 0x200;
        pr.f24 = 1.0f;
        pr.f28 = 0.5f;
        r = func_00117E58(dl, &pr);
        n = n + r;
        dl = dl + r * 16;
        r = func_00113228(dl, 6);
        n = n + r;
        dl = dl + r * 16;
        pr.f00 = 0;
        pr.f04 = 0x8DA0;
        pr.f08 = 0x7C50;
        pr.f0C = 0x7FFFF0;
        pr.f18 = 0x400;
        pr.f10 = 0xA00;
        pr.f1C = 0x200;
        pr.f14 = 0x200;
        pr.f24 = 1.0f;
        pr.f28 = 0.5f;
        r = func_00117E58(dl, &pr);
        n = n + r;
        dl = dl + r * 16;
        n = n + func_00113A00(dl, handle, 1, 0xBE, -0x7D, 0x7FFFF0, 0x80808080);
    }
    h->f00 = n;
    return n + 1;
}
