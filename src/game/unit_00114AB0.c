typedef struct { float x; float y; float z; float w; } __attribute__((aligned(16))) Vec4f;
typedef struct { int f0; float f4; float f8; float fC; Vec4f v; } Entry;
extern Entry D_001F6BE0[];
extern int D_001ED1BC;

void func_00114AB0(int a, Vec4f *src, float c) {
    int i;
    i = D_001ED1BC;
    D_001F6BE0[i].f0 = a;
    D_001F6BE0[i].f4 = c;
    D_001F6BE0[i].f8 = 1.0f;
    *(Vec4f *)((char *)D_001F6BE0 + i * 32 + 16) = *src;
    D_001ED1BC = i + 1;
}

void func_00114AF8(int a, Vec4f *src, float c, float d) {
    int i;
    i = D_001ED1BC;
    D_001F6BE0[i].f0 = a;
    D_001F6BE0[i].f4 = c;
    D_001F6BE0[i].f8 = d;
    *(Vec4f *)((char *)D_001F6BE0 + i * 32 + 16) = *src;
    D_001ED1BC = i + 1;
}
