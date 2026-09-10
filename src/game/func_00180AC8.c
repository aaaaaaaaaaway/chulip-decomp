typedef struct {
    int flags;
    int x;
    int y;
    int z;
    int u;
    int v;
    int w;
    int h;
    int unused20;
    float sx;
    float sy;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Sprite;

typedef struct {
    unsigned short count;
    unsigned char pad;
    unsigned char tag;
} Hdr;

extern int D_002DB540[];

int func_00113228(void *p, int n);
int func_00117E58(void *dl, Sprite *p);
void func_0017F898(void);
typedef int (*DrawCallback)(char *packet, int arg0, int arg1);
void func_0017F9B8(DrawCallback fn, int a, int b);
int func_0017FBB0(char *packet, int arg0, int arg1);
int func_001803D0(char *packet, int arg0, int arg1);
int func_00180F48(char *packet, int arg0, int arg1);
int func_0017FC00(char *packet, int arg0, int arg1);
int func_00181700(char *packet, int arg0, int arg1);

int func_00180AC8(char *dl, int idx, int unused) {
    Sprite sprite;
    Hdr *h;
    int n;
    int r;
    int t;
    int original_index = idx;
    int *state;

    h = (Hdr *)dl;
    dl += 0x10;
    h->tag = 0x10;
    n = func_00113228(dl, 0x1B);
    dl = dl + n * 16;
    *(unsigned long *)(dl + 0x0) = 0x1000000000008001UL;
    *(unsigned long *)(dl + 0x8) = 0xEUL;
    *(unsigned long *)(dl + 0x18) = 0x42UL;
    *(unsigned long *)(dl + 0x10) = 0x8000000048UL;
    n = n + 2;
    dl = dl + 0x20;

    state = &D_002DB540[idx];
    sprite.flags = 0;
    sprite.v = 0;
    sprite.x = 0x8160;
    sprite.y = 0x7C60;
    sprite.z = 0x07FFFFF0;
    sprite.u = 0x9A0;
    sprite.w = 0x220;
    sprite.h = 0x500;
    sprite.r = 0xFF;
    sprite.g = 0x20;
    sprite.b = 0x80;
    sprite.a = -0x80 - ((*state) << 7) / 0x3C;
    sprite.sx = (float)(*state) / 60.0f + 1.0f;
    sprite.sy = (float)(*state) * 0.5f / 60.0f + 0.5f;
    sprite.y -= (*state) * 0x50 / 0x3C;
    r = func_00117E58(dl, &sprite);
    n = n + r;

    sprite.x = 0x8160;
    sprite.y = 0x7C60;
    sprite.a = -0x80 - ((*state) << 7) / 0x3C;
    sprite.sx = (float)(*state) / 60.0f + 0.5f;
    sprite.sy = (float)(*state) * 0.5f / 60.0f + 0.25f;
    sprite.y -= (float)(*state) * 40.0f / 60.0f;
    n = n + func_00117E58(dl + r * 16, &sprite);

    t = *state + 1;
    *state = t;
    if (t > 0x3C) {
        idx++;
        func_0017F898();
        func_0017F9B8(func_0017FBB0, 0, 0);
        D_002DB540[0] = 0x2D;
        func_0017F9B8(func_001803D0, 0, 0);
        *state = 0;
        func_0017F9B8(func_00180F48, original_index, 0);
        D_002DB540[idx] = 0;
        func_0017F9B8(func_0017FC00, idx++, 0);
        D_002DB540[idx] = 0;
        func_0017F9B8(func_00181700, idx, 0);
    }
    h->count = n;
    return n + 1;
}
