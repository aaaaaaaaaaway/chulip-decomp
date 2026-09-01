typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;

void func_00161328(Vec4 *dst, const Vec4 *src) {
    *dst = *src;
}
