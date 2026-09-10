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
    char pad00[0x20];
    int x;
    int y;
    char pad28[4];
    int span;
} Gauge;

typedef struct {
    int x;
    int y;
} Point;

/* Provisional single-source provider; original TU boundaries are unproved. */
int D_001ECD3C __attribute__((section(".sdata"))) = 0;
extern Point D_001ED4E4;
extern Point D_001ED4EC;

extern int func_00113228(void *packet, int size);
extern float func_0018B2F8(float radians);
extern int func_00117E58(unsigned char *packet, Sprite *sprite);

int func_001609E0(unsigned char *dl, Gauge *gauge) {
    Sprite sprite;
    unsigned char *head;
    int total;
    int n;
    int bx;
    int by;
    int d;
    float angle;

    head = dl;
    dl += 0x10;
    head[3] = 0x10;
    total = func_00113228(dl, 6);
    dl += total * 0x10;

    sprite.z = 0x07FFFFF0;
    sprite.u = 0;
    sprite.w = 0x200;
    sprite.h = 0x200;
    sprite.v = 0x200;
    sprite.r = 0x80;
    sprite.g = 0x80;
    sprite.b = 0x80;
    sprite.a = 0x80;
    sprite.sx = 1.0f;
    sprite.sy = 0.5f;

    bx = gauge->x * 16;
    by = gauge->y * 16;
    angle = (float)(D_001ECD3C % 45 * 8);
    angle = angle * 3.14159265358979323846f;
    angle = angle / 180.0f;
    d = (int)(func_0018B2F8(angle) * 32.0f);
    if (D_001ED4E4.y - D_001ED4EC.y > 0) {
        sprite.x = bx;
        sprite.flags = 0;
        sprite.y = by + d;
        n = func_00117E58(dl, &sprite);
        total += n;
        dl += n * 0x10;
    }
    if (D_001ED4E4.y - D_001ED4EC.y + 6 < 6) {
        int offset = d - 0x640;
        sprite.x = bx;
        sprite.flags = 2;
        sprite.y = by - offset;
        n = func_00117E58(dl, &sprite);
        total += n;
        dl += n * 0x10;
    }

    sprite.u = sprite.w * 7;
    sprite.v = sprite.h;
    bx = gauge->x * 16;
    by = gauge->y * 16;
    angle = (float)(D_001ECD3C % 90 * 8);
    angle = angle * 3.14159265358979323846f;
    angle = angle / 180.0f;
    d = (int)(func_0018B2F8(angle) * 64.0f);
    if (D_001ED4E4.x - D_001ED4EC.x > 0) {
        int offset = d + 0x20;
        sprite.flags = 0;
        sprite.x = bx + offset;
        sprite.y = by + gauge->span / 2 * 16;
        n = func_00117E58(dl, &sprite);
        total += n;
        dl += n * 0x10;
    }
    if (D_001ED4E4.x - D_001ED4EC.x + 0xB < 0xB) {
        int offset = d - 0x15C0;
        sprite.flags = 1;
        sprite.x = bx - offset;
        sprite.y = by + gauge->span / 2 * 16;
        total += func_00117E58(dl, &sprite);
    }
    *(unsigned short *)head = total;
    D_001ECD3C += 1;
    return total + 1;
}
