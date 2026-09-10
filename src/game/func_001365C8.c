typedef struct {
    float m[3][4][4];
} MatrixSet;

extern MatrixSet D_001FF1A0[];
extern MatrixSet D_001FF8E0[];
extern float D_001FFB20[4];
extern float D_001A7790[4];

extern void func_0018A680(float *dst, float *src);

void func_001365C8(void) {
    int i;
    int j;

    if (D_001FFB20[0] == 0.0f && D_001FFB20[1] == 0.0f && D_001FFB20[2] == 0.0f) {
        return;
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            func_0018A680(D_001FF1A0[i].m[j][1], D_001FF8E0[i].m[j][1]);
            func_0018A680(D_001FF1A0[i].m[j][0], D_001FF8E0[i].m[j][0]);
            func_0018A680(D_001FF1A0[i].m[j][2], D_001FF8E0[i].m[j][2]);
        }
    }

    func_0018A680(D_001A7790, D_001FFB20);
    D_001FFB20[0] = 0.0f;
    D_001FFB20[1] = 0.0f;
    D_001FFB20[2] = 0.0f;
    D_001FFB20[3] = 1.0f;
}
