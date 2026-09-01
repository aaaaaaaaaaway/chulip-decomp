typedef struct { float x; float y; float z; } Vec3f;
typedef struct { int x; int y; int z; } Vec3i;
extern int D_001ED1A8;
int func_00192568(void);
void func_00112860(int index, int value);

void func_00112798(int index, Vec3f *pos, void *unused, Vec3i *color, Vec3f *scale, float f) {
    int p;

    p = D_001ED1A8 + index * 0x60;
    *(float *)(p + 0x08) = f;
    *(float *)(p + 0x1C) = 1.0f;
    *(float *)(p + 0x2C) = 1.0f;
    *(float *)(p + 0x30) = pos->x;
    *(float *)(p + 0x34) = pos->y;
    *(float *)(p + 0x38) = pos->z;
    *(float *)(p + 0x3C) = 1.0f;
    *(float *)(p + 0x50) = scale->x;
    *(float *)(p + 0x54) = scale->y;
    *(float *)(p + 0x58) = scale->z;
    *(float *)(p + 0x5C) = 1.0f;
    *(int *)(p + 0x40) = color->x;
    *(int *)(p + 0x44) = color->y;
    *(int *)(p + 0x48) = color->z;
    *(int *)(p + 0x4C) = 1;
    func_00112860(index, func_00192568() % 100 + 100);
}
