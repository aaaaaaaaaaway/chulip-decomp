typedef struct { float x, y, z, w; } Vec4;
extern void func_0018A680(Vec4 *dst, const Vec4 *src);

void func_0018AB78(Vec4 *dst, const Vec4 *a, const Vec4 *b, const Vec4 *c, const Vec4 *d) {
    func_0018A680(dst, a);
    func_0018A680(dst + 1, b);
    func_0018A680(dst + 2, c);
    func_0018A680(dst + 3, d);
}
