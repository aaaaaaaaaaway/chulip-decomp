typedef struct {
    int flags;
    int x;
    int y;
    int z;
    int u;
    int v;
    int w;
    int h;
    float angle;
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

float func_0018B210(float radians);
float func_0018B2F8(float radians);

int func_00118058(unsigned char *packet, Sprite *sprite) {
    Quad color;
    float radians;
    float fw;
    float fh;
    int hw;
    int hh;
    int signx;
    int signy;
    float ax;
    float ay;
    float bx;
    float by;
    float fx;
    float fy;

    fw = (float)sprite->w;
    fh = (float)(sprite->h / 2);
    radians = sprite->angle * 3.1415927f / 180.0f;

    color.c0 = sprite->r;
    color.c1 = sprite->g;
    color.c2 = sprite->b;
    color.c3 = sprite->a;

    hw = (int)(fw * func_0018B210(radians) - fh * func_0018B2F8(radians)) / 2;
    hh = (int)(fw * func_0018B2F8(radians) + fh * func_0018B210(radians)) / 2;
    fx = (float)sprite->x;
    fy = (float)sprite->y;

    signx = (sprite->flags & 1) ? -1 : 1;
    signy = (sprite->flags & 2) ? -1 : 1;

    ax = (float)hw * sprite->sx * (float)signx;
    by = (float)hh * sprite->sy * (float)signy;
    bx = (float)hh * sprite->sx * (float)signx;
    ay = (float)hw * sprite->sy * (float)signy;

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

    *(int *)(packet + 0x10) = (int)(fx - ax);
    *(int *)(packet + 0x14) = (int)(fy - by);
    *(int *)(packet + 0x18) = sprite->z;
    *(int *)(packet + 0x1C) = 0x8000;

    *(int *)(packet + 0x30) = (int)(fx + bx);
    *(int *)(packet + 0x34) = (int)(fy - ay);
    *(int *)(packet + 0x38) = sprite->z;
    *(int *)(packet + 0x3C) = 0x8000;

    *(int *)(packet + 0x50) = (int)(fx - bx);
    *(int *)(packet + 0x54) = (int)(fy + ay);
    *(int *)(packet + 0x58) = sprite->z;
    *(int *)(packet + 0x5C) = 0;

    *(int *)(packet + 0x70) = (int)(fx + ax);
    *(int *)(packet + 0x74) = (int)(fy + by);
    *(int *)(packet + 0x78) = sprite->z;
    *(int *)(packet + 0x7C) = 0;

    return 0xA;
}
