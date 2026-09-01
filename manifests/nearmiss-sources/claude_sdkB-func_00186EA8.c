typedef struct { float x, y, z, w; } Vec4;
extern void func_001866B0(const float *source, Vec4 *destination);
extern void func_00186D90(Vec4 *a, Vec4 *b);

void func_00186EA8(float x, float y) {
    Vec4 a;
    Vec4 b;
    float fx;
    float fy;
    fx = x;
    fy = y;
    func_001866B0(&fx, &a);
    func_001866B0(&fy, &b);
    func_00186D90(&a, &b);
}
