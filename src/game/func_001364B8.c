typedef struct {
    float m[3][4][4];
} MatrixSet;

extern MatrixSet D_001FF8E0[];
extern MatrixSet D_001FF1A0[];
extern float D_001FFB20[4][4];
extern float D_001A7790[4][4];

extern void func_0018A680(float *, float *);

void func_001364B8(void) {
    int i;
    int j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            func_0018A680(D_001FF8E0[i].m[j][0], D_001FF1A0[i].m[j][0]);
            func_0018A680(D_001FF8E0[i].m[j][1], D_001FF1A0[i].m[j][1]);
            func_0018A680(D_001FF8E0[i].m[j][2], D_001FF1A0[i].m[j][2]);
        }
    }
    func_0018A680(D_001FFB20[0], D_001A7790[0]);
}
