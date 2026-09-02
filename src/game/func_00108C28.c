typedef struct {
    int mode;
    int x;
    int y;
    int z;
    int w;
    int h;
    int unused18;
    int unused1c;
    int u0;
    int v0;
    int q0;
    int r0;
    int u1;
    int v1;
    int q1;
    int r1;
    int u2;
    int v2;
    int q2;
    int r2;
    int u3;
    int v3;
    int q3;
    int r3;
} Sprite;

extern int D_001ED0CC;
extern int D_001ED0D0;

#define G ((Sprite *)D_001ED0CC)

int func_00108C28(unsigned char *packet) {
    unsigned char *base;

    if (D_001ED0D0 != 0) {
        return 0;
    }

    base = packet;
    base[3] = 0x10;
    packet = base + 0x10;

    switch (G->mode) {
    case 1:
        *(long *)(packet + 0x00) = 0x1000000000008001L;
        *(long *)(packet + 0x08) = 14;
        *(long *)(packet + 0x18) = 0x42;
        *(long *)(packet + 0x10) = 0x8000000048L;
        break;
    case 2:
        *(long *)(packet + 0x00) = 0x1000000000008001L;
        *(long *)(packet + 0x08) = 14;
        *(long *)(packet + 0x18) = 0x42;
        *(long *)(packet + 0x10) = 0x8000000042L;
        break;
    default:
        *(long *)(packet + 0x00) = 0x1000000000008001L;
        *(long *)(packet + 0x08) = 14;
        *(long *)(packet + 0x18) = 0x42;
        *(long *)(packet + 0x10) = 0x8000000044L;
        break;
    }
    packet += 0x20;

    *(long *)(packet + 0x00) = 0x8026400000008001L;
    *(long *)(packet + 0x08) = 0x41414141L;
    packet += 0x10;

    *(int *)(packet + 0x00) = G->u0;
    *(int *)(packet + 0x04) = G->v0;
    *(int *)(packet + 0x08) = G->q0;
    *(int *)(packet + 0x0C) = G->r0;

    *(int *)(packet + 0x20) = G->u1;
    *(int *)(packet + 0x24) = G->v1;
    *(int *)(packet + 0x28) = G->q1;
    *(int *)(packet + 0x2C) = G->r1;

    *(int *)(packet + 0x40) = G->u2;
    *(int *)(packet + 0x44) = G->v2;
    *(int *)(packet + 0x48) = G->q2;
    *(int *)(packet + 0x4C) = G->r2;

    *(int *)(packet + 0x60) = G->u3;
    *(int *)(packet + 0x64) = G->v3;
    *(int *)(packet + 0x68) = G->q3;
    *(int *)(packet + 0x6C) = G->r3;

    *(int *)(packet + 0x10) = G->x;
    *(int *)(packet + 0x14) = G->y;
    *(int *)(packet + 0x18) = G->z;
    *(int *)(packet + 0x1C) = 0x8000;

    *(int *)(packet + 0x30) = G->x + G->w;
    *(int *)(packet + 0x34) = G->y;
    *(int *)(packet + 0x38) = G->z;
    *(int *)(packet + 0x3C) = 0x8000;

    *(int *)(packet + 0x50) = G->x;
    *(int *)(packet + 0x54) = G->y + G->h;
    *(int *)(packet + 0x58) = G->z;
    *(int *)(packet + 0x5C) = 0;

    *(int *)(packet + 0x70) = G->x + G->w;
    *(int *)(packet + 0x74) = G->y + G->h;
    *(int *)(packet + 0x78) = G->z;
    *(int *)(packet + 0x7C) = 0;

    *(short *)base = 0xB;
    return 0xC;
}
