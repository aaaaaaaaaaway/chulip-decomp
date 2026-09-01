typedef struct {
    int x;
    int y;
    int z;
    int w;
} Vec4i;

typedef struct {
    Vec4i corner[4];
    int u;
    int v;
    int w;
    int h;
    int unused50;
    int unused54;
    int unused58;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Model;

typedef struct {
    int c0;
    int c1;
    int c2;
    int c3;
} __attribute__((aligned(16))) Quad;

void func_0018AED0(Vec4i *out, void *matrix, Vec4i *in, int mode);

int func_00118380(unsigned char *packet, void *matrix, Model *model) {
    Vec4i pos[4];
    Quad color;

    color.c0 = model->r;
    color.c1 = model->g;
    color.c2 = model->b;
    color.c3 = model->a;

    func_0018AED0(&pos[0], matrix, &model->corner[0], 0);
    func_0018AED0(&pos[1], matrix, &model->corner[1], 0);
    func_0018AED0(&pos[2], matrix, &model->corner[2], 0);
    func_0018AED0(&pos[3], matrix, &model->corner[3], 0);

    *(long *)packet = 0x90AA400000008001L;
    *(long *)(packet + 8) = 0x434343431L;
    packet += 0x10;

    *(Quad *)packet = color;
    packet += 0x10;

    *(int *)(packet + 0x00) = model->u + 8;
    *(int *)(packet + 0x04) = model->v + 8;
    *(int *)(packet + 0x08) = 0;
    *(int *)(packet + 0x0C) = 0;

    *(int *)(packet + 0x20) = model->u - 8 + model->w;
    *(int *)(packet + 0x24) = model->v + 8;
    *(int *)(packet + 0x28) = 0;
    *(int *)(packet + 0x2C) = 0;

    *(int *)(packet + 0x40) = model->u + 8;
    *(int *)(packet + 0x44) = model->v - 8 + model->h;
    *(int *)(packet + 0x48) = 0;
    *(int *)(packet + 0x4C) = 0;

    *(int *)(packet + 0x60) = model->u - 8 + model->w;
    *(int *)(packet + 0x64) = model->v - 8 + model->h;
    *(int *)(packet + 0x68) = 0;
    *(int *)(packet + 0x6C) = 0;

    *(int *)(packet + 0x10) = pos[0].x;
    *(int *)(packet + 0x14) = pos[0].y;
    *(int *)(packet + 0x18) = pos[0].z;
    *(int *)(packet + 0x1C) = 0x8000;

    *(int *)(packet + 0x30) = pos[1].x;
    *(int *)(packet + 0x34) = pos[1].y;
    *(int *)(packet + 0x38) = pos[1].z;
    *(int *)(packet + 0x3C) = 0x8000;

    *(int *)(packet + 0x50) = pos[2].x;
    *(int *)(packet + 0x54) = pos[2].y;
    *(int *)(packet + 0x58) = pos[2].z;
    *(int *)(packet + 0x5C) = 0;

    *(int *)(packet + 0x70) = pos[3].x;
    *(int *)(packet + 0x74) = pos[3].y;
    *(int *)(packet + 0x78) = pos[3].z;
    *(int *)(packet + 0x7C) = 0;

    return 0xA;
}
