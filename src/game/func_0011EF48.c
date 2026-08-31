typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;

extern unsigned short D_001ED220[];

int func_00158868(unsigned short id, Vec4 *out);
void func_00114730(int index, Vec4 *value, unsigned int color);

void func_0011EF48(void) {
    Vec4 v;

    if (func_00158868(D_001ED220[0], &v) == 0) {
        v.w = 1.0f;
        v.y = v.y - 308.0f;
        func_00114730(3, &v, 0x80808080u);
    }
}
