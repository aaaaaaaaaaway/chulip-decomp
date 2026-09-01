typedef struct { float x, y, z, w; } Vec4;
extern void func_001866B0(const float *source, Vec4 *destination);
extern int func_00186740(Vec4 *a, Vec4 *b, Vec4 *c);
extern void func_001865A0(int value);

void func_00186978(float x, float y) {
    Vec4 a;
    Vec4 b;
    Vec4 c;
    float fx;
    float fy;
    fx = x;
    fy = y;
    func_001866B0(&fx, &a);
    func_001866B0(&fy, &b);
    func_001865A0(func_00186740(&a, &b, &c));
}
