typedef float Vec4[4] __attribute__((aligned(16)));
typedef float Matrix[4][4] __attribute__((aligned(16)));
typedef struct {
    unsigned char unknown00[0x20];
    unsigned char *model;
} Actor;
extern float D_001EDBB0[];
extern Matrix D_001A76C0;
void func_0018A6F8(Matrix out);
void func_0018A840(Matrix out, Matrix in, float angle);
void func_0018A8E8(Matrix out, Matrix in, float angle);
void func_0018A798(Matrix out, Matrix in, float angle);
void func_0018A3D0(Vec4 out, Matrix matrix, const float *in);
void func_0018A680(void *out, const void *in);
void func_0018A690(void *out, const void *in);

void func_0012FD08(Actor *actor) {
    Vec4 rotated;
    Matrix rotation;
    func_0018A6F8(rotation);
    func_0018A840(rotation, rotation, D_001EDBB0[12]);
    func_0018A8E8(rotation, rotation, D_001EDBB0[13]);
    func_0018A798(rotation, rotation, D_001EDBB0[14]);
    func_0018A3D0(rotated, rotation, D_001EDBB0);
    func_0018A680(D_001A76C0, rotated);
    func_0018A690(actor->model + 0xC0, D_001A76C0);
}
