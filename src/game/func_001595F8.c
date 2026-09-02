extern float D_001EDC00[16];

void func_001923F4(void *dst, int value, int size);
void func_001039D8(float *out);
void func_0018A518(float *dst, const float *src);
void func_0018A3D0(float *out, const float *m, const float *src);
void func_0018A5F0(float *dst, const float *a, const float *b);
void func_00156BC8(int id, float *v);
void func_00158BB8(int id, int mode);

void func_001595F8(unsigned short id, short sx, short sy) {
    float proj[16];
    float mtx[16];
    float dir[4];
    float tmp[4];
    float cam[4];
    float nx;
    float ny;

    func_001923F4(proj, 0, 0x40);
    proj[0] = 1.0f;
    proj[5] = 1.0f;
    proj[10] = -84.0f;
    proj[11] = 0.0029296875f;
    proj[14] = 10.5f;
    nx = -(float)sx / 512.0f * 2.0f + 1.0f;
    ny = -(float)sy / 224.0f * 1.5f + 0.75f;
    func_001039D8(cam);
    dir[0] = nx * 1.5f * -300.0f;
    dir[1] = ny * 1.5f * -100.0f;
    dir[2] = 0.0f;
    dir[3] = 1.0f;
    func_0018A518(mtx, proj);
    func_0018A3D0(tmp, mtx, dir);
    func_0018A518(mtx, D_001EDC00);
    func_0018A3D0(dir, mtx, tmp);
    func_0018A5F0(dir, dir, cam);
    func_00156BC8(id, dir);
    func_00158BB8(id, 1);
}
