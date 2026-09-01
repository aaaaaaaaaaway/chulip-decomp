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
    int c0;
    int c1;
    int c2;
    int c3;
} __attribute__((aligned(16))) Quad;

int func_00117E58(unsigned char *packet, Sprite *sprite) {
    Quad color;
    int hw;
    int hh;

    color.c0 = sprite->r;
    color.c1 = sprite->g;
    color.c2 = sprite->b;
    color.c3 = sprite->a;

    hw = (int)((float)sprite->w * sprite->sx * 0.5f);
    hh = (int)((float)sprite->h * sprite->sy * 0.5f);
    if (sprite->flags & 1) {
        hw = -hw;
    }
    if (sprite->flags & 2) {
        hh = -hh;
    }

    *(long *)packet = 0x90AA400000008001L;
    *(long *)(packet + 8) = 0x434343431L;
    packet += 0x10;

    *(Quad *)packet = color;
    packet += 0x10;

    *(int *)(packet + 0x00) = sprite->u + 8;
    *(int *)(packet + 0x04) = sprite->v + 8;
    *(int *)(packet + 0x08) = 0;
    *(int *)(packet + 0x0C) = 0;

    *(int *)(packet + 0x20) = sprite->u - 8 + sprite->w;
    *(int *)(packet + 0x24) = sprite->v + 8;
    *(int *)(packet + 0x28) = 0;
    *(int *)(packet + 0x2C) = 0;

    *(int *)(packet + 0x40) = sprite->u + 8;
    *(int *)(packet + 0x44) = sprite->v - 8 + sprite->h;
    *(int *)(packet + 0x48) = 0;
    *(int *)(packet + 0x4C) = 0;

    *(int *)(packet + 0x60) = sprite->u - 8 + sprite->w;
    *(int *)(packet + 0x64) = sprite->v - 8 + sprite->h;
    *(int *)(packet + 0x68) = 0;
    *(int *)(packet + 0x6C) = 0;

    *(int *)(packet + 0x10) = sprite->x - hw;
    *(int *)(packet + 0x14) = sprite->y - hh;
    *(int *)(packet + 0x18) = sprite->z;
    *(int *)(packet + 0x1C) = 0x8000;

    *(int *)(packet + 0x30) = sprite->x + hw;
    *(int *)(packet + 0x34) = sprite->y - hh;
    *(int *)(packet + 0x38) = sprite->z;
    *(int *)(packet + 0x3C) = 0x8000;

    *(int *)(packet + 0x50) = sprite->x - hw;
    *(int *)(packet + 0x54) = sprite->y + hh;
    *(int *)(packet + 0x58) = sprite->z;
    *(int *)(packet + 0x5C) = 0;

    *(int *)(packet + 0x70) = sprite->x + hw;
    *(int *)(packet + 0x74) = sprite->y + hh;
    *(int *)(packet + 0x78) = sprite->z;
    *(int *)(packet + 0x7C) = 0;

    return 0xA;
}
