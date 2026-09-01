typedef struct { float x; float y; float z; float w; } Vec4f;
typedef struct { float a; float p1; float p2; float p3; Vec4f b; int c[4]; } Item;

extern int D_001ED144;
int func_00192568(void);

void func_0010D040(int index, int p2, Item *u, Item *v) {
    int i;
    int off;

    *(int *)(index * 0x660 + D_001ED144 + 0x00) = 0;
    *(int *)(index * 0x660 + D_001ED144 + 0x04) = p2;
    *(int *)(index * 0x660 + D_001ED144 + 0x20) = u->c[0];
    *(int *)(index * 0x660 + D_001ED144 + 0x24) = u->c[1];
    *(int *)(index * 0x660 + D_001ED144 + 0x28) = u->c[2];
    *(int *)(index * 0x660 + D_001ED144 + 0x2C) = u->c[3];
    *(int *)(index * 0x660 + D_001ED144 + 0x30) = v->c[0];
    *(int *)(index * 0x660 + D_001ED144 + 0x34) = v->c[1];
    *(int *)(index * 0x660 + D_001ED144 + 0x38) = v->c[2];
    *(int *)(index * 0x660 + D_001ED144 + 0x3C) = v->c[3];
    *(float *)(index * 0x660 + D_001ED144 + 0x08) = u->a;
    *(float *)(index * 0x660 + D_001ED144 + 0x10) = u->a * 0.5f;
    *(float *)(index * 0x660 + D_001ED144 + 0x0C) = v->a;
    *(float *)(index * 0x660 + D_001ED144 + 0x14) = v->a * 0.5f;
    *(float *)(index * 0x660 + D_001ED144 + 0x40) = u->b.x;
    *(float *)(index * 0x660 + D_001ED144 + 0x44) = u->b.y;
    *(float *)(index * 0x660 + D_001ED144 + 0x48) = u->b.z;
    *(float *)(index * 0x660 + D_001ED144 + 0x50) = v->b.x;
    *(float *)(index * 0x660 + D_001ED144 + 0x54) = v->b.y;
    *(float *)(index * 0x660 + D_001ED144 + 0x58) = v->b.z;
    for (i = 0; i < 0x20; i++) {
        off = i * 0x30;
        *(float *)(index * 0x660 + D_001ED144 + off + 0x70) = u->b.x;
        *(float *)(index * 0x660 + D_001ED144 + off + 0x74) = u->b.y;
        *(float *)(index * 0x660 + D_001ED144 + off + 0x78) = u->b.z;
        *(float *)(index * 0x660 + D_001ED144 + off + 0x7C) = 1.0f;
        *(float *)(index * 0x660 + D_001ED144 + off + 0x80) = v->b.x + (float)((func_00192568() - func_00192568()) % 0xF) / 100.0f;
        *(float *)(index * 0x660 + D_001ED144 + off + 0x84) = v->b.y + (float)((func_00192568() - func_00192568()) % 0xF) / 100.0f;
        *(float *)(index * 0x660 + D_001ED144 + off + 0x88) = v->b.z + (float)((func_00192568() - func_00192568()) % 0xF) / 100.0f;
        *(float *)(index * 0x660 + D_001ED144 + off + 0x8C) = (float)(func_00192568() % 0xC8) / 100.0f;
        *(int *)(index * 0x660 + D_001ED144 + off + 0x60) = p2;
    }
}
