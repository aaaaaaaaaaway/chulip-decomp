typedef struct { float x; float y; float z; float w; } Vec4f;
typedef struct { float m[16]; } __attribute__((aligned(16))) Mat4;

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
    int f00;
    int frame;
    int f08;
    int f0C;
    float x;
    float y;
    float z;
    float w;
    int f20;
    int f24;
    int f28;
    int f2C;
    int r;
    int g;
    int b;
    int a;
} Particle;

extern int D_001ED090;
extern int D_001ED098;
extern float D_001EDCC0[];

int func_00113228(void *dl, int size);
void func_00158A00();
void func_0018A3D0(void *out, Mat4 *m, void *src);
int func_00120BE0(int *out, float *proj, Vec4f *src);
int func_00117E58(unsigned char *packet, Sprite *sprite);

int func_00105F28(unsigned char *dl, int count) {
    int out[4];
    Vec4f v;
    Mat4 m;
    Sprite sprite;
    unsigned char *head;
    Particle *p;
    int i;
    int j;
    int off;
    int total;
    int n;
    int k;

    if (D_001ED098 != 0) {
        return 0;
    }

    head = dl;
    dl += 0x10;
    head[3] = 0x10;
    total = func_00113228(dl, 0x1018);
    dl += total * 0x10;

    *(long *)(dl + 0x00) = 0x1000000000008001L;
    *(long *)(dl + 0x08) = 0xE;
    *(long *)(dl + 0x18) = 8;
    *(long *)(dl + 0x10) = 5;
    dl += 0x20;
    *(long *)(dl + 0x00) = 0x1000000000008001L;
    *(long *)(dl + 0x08) = 0xE;
    *(long *)(dl + 0x18) = 0x42;
    *(long *)(dl + 0x10) = 0x8000000048L;
    dl += 0x20;
    total += 4;

    sprite.v = 0x200;
    sprite.flags = 0;
    sprite.u = 0;
    sprite.w = 0x100;
    sprite.h = 0x100;
    sprite.r = 0xFF;
    sprite.g = 0xAC;
    sprite.b = 0x80;
    sprite.a = 0x30;
    sprite.sx = 0.5f;
    sprite.sy = 1.0f;

    for (i = 0; i < count; i++) {
        if (*(int *)(i * 0x2B0 + D_001ED090 + 0x14) != 1) {
            continue;
        }
        func_00158A00(*(unsigned short *)(i * 0x2B0 + D_001ED090 + 0x00),
                      *(unsigned char *)(i * 0x2B0 + D_001ED090 + 0x04), &m);
        for (j = 0; j < 0xA; j++) {
            off = j * 0x40;
            p = &((Particle *)(D_001ED090 + i * 0x2B0 + 0x30))[j];
            v.x = p->x;
            v.y = p->y;
            v.z = p->z;
            v.w = 1.0f;
            func_0018A3D0(&v, &m, &v);
            if (func_00120BE0(out, D_001EDCC0, &v) == 0) {
                k = p->frame / 5 % 4;
                sprite.x = out[0];
                sprite.y = out[1];
                sprite.z = out[2];
                sprite.v = k * sprite.h + 0x200;
                sprite.r = *(int *)(i * 0x2B0 + D_001ED090 + off + 0x60);
                sprite.g = *(int *)(i * 0x2B0 + D_001ED090 + off + 0x64);
                sprite.b = *(int *)(i * 0x2B0 + D_001ED090 + off + 0x68);
                sprite.a = *(int *)(i * 0x2B0 + D_001ED090 + off + 0x6C) *
                           *(int *)(i * 0x2B0 + D_001ED090 + 0x0C) /
                           *(int *)(i * 0x2B0 + D_001ED090 + 0x10);
                n = func_00117E58(dl, &sprite);
                total += n;
                dl += n * 0x10;
                p->frame += 1;
            }
        }
        *(int *)(i * 0x2B0 + D_001ED090 + 0x0C) += *(int *)(i * 0x2B0 + D_001ED090 + 0x08);
        if (*(int *)(i * 0x2B0 + D_001ED090 + 0x0C) < 0) {
            *(int *)(i * 0x2B0 + D_001ED090 + 0x0C) = 0;
        } else if (*(int *)(i * 0x2B0 + D_001ED090 + 0x10) < *(int *)(i * 0x2B0 + D_001ED090 + 0x0C)) {
            *(int *)(i * 0x2B0 + D_001ED090 + 0x0C) = *(int *)(i * 0x2B0 + D_001ED090 + 0x10);
        }
    }
    *(unsigned short *)head = total;
    return total + 1;
}
