typedef struct { float x; float y; float z; float w; } Vec4f;
typedef struct { float m[16]; } __attribute__((aligned(16))) Mat4;

void func_00154758(unsigned short id, Vec4f *out);
void func_0018A6F8(Mat4 *m);
void func_0018A798(Mat4 *d, Mat4 *s, float a);
void func_0018A8E8(Mat4 *d, Mat4 *s, float a);
void func_0018A840(Mat4 *d, Mat4 *s, float a);
void func_0018A3D0(void *out, Mat4 *m, void *extra);

void func_0011FA48(void *out, unsigned short id, void *extra) {
    Mat4 m;
    Vec4f v;

    func_00154758(id, &v);
    v.w = 1.0f;
    func_0018A6F8(&m);
    func_0018A798(&m, &m, v.z);
    func_0018A8E8(&m, &m, v.y);
    func_0018A840(&m, &m, v.x);
    func_0018A3D0(out, &m, extra);
}
