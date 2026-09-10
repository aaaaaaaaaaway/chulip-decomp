typedef struct {
    short f00;
    unsigned char pad;
    unsigned char f03;
} Hdr;

typedef struct {
    int f00;
    int f04;
    int f08;
} Ctx;

int D_001EC8AC = 0;
int D_001EC8B0 = 20;

unsigned char *func_00136AE8(void);
int func_00113228(void *p, int n);
int func_00113648(void *p, unsigned long first, unsigned long second);
int func_00113670(void *p, int ax, int ay, int bx, int by, int u0, int v0,
                  int u1, int v1, int z, int col);
int func_00113710(void *p, int a, int b, int c, int d, int e, int f, int g,
                  float x, float y, float ang, int h, int i, int j);
float func_00113FB0(int a, int b);

int func_00114010(char *dl) {
    Hdr *hdr;
    int fr;
    int t;
    int y;
    int n;
    int qwc;

    t = D_001EC8B0;
    y = -0xDC - t * t / 2;
    fr = ((Ctx *)func_00136AE8())->f08;
    if (D_001EC8AC) {
        if (D_001EC8B0 > 0) {
            D_001EC8B0 = D_001EC8B0 - 1;
        }
    } else if (D_001EC8B0 < 0x14) {
        D_001EC8B0 = D_001EC8B0 + 1;
    }
    *(long long *)dl = 0;
    hdr = (Hdr *)dl;
    dl += 0x10;
    hdr->f03 = 0x10;
    n = func_00113228(dl, 0xA);
    qwc = n;
    dl = dl + qwc * 16;
    n = func_00113648(dl, 0x42, 0x8000000044L);
    qwc = qwc + n;
    dl = dl + n * 16;
    n = func_00113648(dl, 0x47, 0x5140BL);
    qwc = qwc + n;
    dl = dl + n * 16;
    n = func_00113710(dl, 0x1D, 0x1D, -0x1D, -0x1D, 0x500, 0x500, 0x800,
                      188.0f, (float)(y + 0x48), func_00113FB0(fr, 0xA8C0),
                      0x800, 0xFFFFF0, 0x80808080);
    qwc = qwc + n;
    dl = dl + n * 16;
    n = func_00113670(dl, 0x9C, y, 0xDC, y + 0x20, 0, 0, 0x300, 0x180,
                      0xFFFFF4, 0x80808080);
    qwc = qwc + n;
    dl = dl + n * 16;
    n = func_00113670(dl, 0x8C, y + 0x18, 0xEC, y + 0x78, 0, 0x200, 0x500,
                      0x700, 0xFFFFF4, 0x80808080);
    qwc = qwc + n;
    dl = dl + n * 16;
    n = func_00113710(dl, -0x8, -0x30, 0x8, 0xA, 0x700, 0, 0x800,
                      188.0f, (float)(y + 0x48), func_00113FB0(fr, 0x5460),
                      0x300, 0xFFFFF8, 0x80808080);
    qwc = qwc + n;
    dl = dl + n * 16;
    n = func_00113710(dl, -0x8, -0x30, 0x8, 0xA, 0x600, 0, 0x700,
                      188.0f, (float)(y + 0x48), func_00113FB0(fr, 0x708),
                      0x300, 0xFFFFF8, 0x80808080);
    qwc = qwc + n;
    dl = dl + n * 16;
    qwc = qwc + 1;
    *(long *)dl = 0x8000L;
    hdr->f00 = qwc;
    return qwc + 1;
}
