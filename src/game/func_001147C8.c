typedef struct { float x; float y; float z; float w; } __attribute__((aligned(16))) Vec4f;
typedef struct { int f0; int f4; float f8; float fC; Vec4f v; } Entry;
extern Entry D_001EEBE0[];
extern int D_001ED1B8;
void func_001147C8(int a, Vec4f *src, float c, float d, int b) {
    int i;
    i = D_001ED1B8;
    D_001EEBE0[i].f0 = a;
    D_001EEBE0[i].f4 = b;
    D_001EEBE0[i].f8 = c;
    D_001EEBE0[i].fC = d;
    *(Vec4f *)((char *)D_001EEBE0 + i * 32 + 16) = *src;
    D_001ED1B8 = i + 1;
}
