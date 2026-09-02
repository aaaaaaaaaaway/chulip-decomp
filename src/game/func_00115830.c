typedef struct { float x; float y; float z; float w; } __attribute__((aligned(16))) Vec4f;

extern int D_001ED1D8;
extern Vec4f D_001F9DC0;

float func_0018B2F8(float angle);
float func_0018B210(float angle);

void func_001147C8(int a, Vec4f *src, float c, float d, int b);

int func_00115830(void) {
    float scale;
    float x;
    float y;

    if (D_001ED1D8 > 0) {
        D_001ED1D8 = D_001ED1D8 + 1;
        if (D_001ED1D8 < 50) {
            scale = D_001ED1D8 / 50.0f;
        } else {
            scale = 1.0f;
        }
        x = (func_0018B2F8((D_001ED1D8 % 360) * 3.14f / 18.0f) + 5.0f) / 6.0f * scale;
        y = (func_0018B210((D_001ED1D8 % 360) * 3.14f / 18.0f) + 5.0f) / 6.0f * scale;
        func_001147C8(6, &D_001F9DC0, x, y, 0x80808080);
    }
    return 0;
}
