typedef struct {
    int unk000;
    int unk004;
    int unk008;
    int unk00C[10][10];
    int unk19C[10][10];
    int pad32C[401];
    float unk970[3];
    int unk97C;
    int unk980[4];
} Board;

extern Board *D_001ED188[1];

extern int D_001ED190;

void func_00111300(int index, float x, float y, float *pos, int *color) {
    int i;
    int j;

    D_001ED188[0][index].unk000 = 0;
    D_001ED188[0][index].unk004 = (int)x;
    D_001ED188[0][index].unk008 = (int)y;
    D_001ED188[0][index].unk970[0] = pos[0];
    D_001ED188[0][index].unk970[1] = pos[1];
    D_001ED188[0][index].unk970[2] = pos[2];
    D_001ED188[0][index].unk97C = 0;
    D_001ED188[0][index].unk980[0] = color[0];
    D_001ED188[0][index].unk980[1] = color[1];
    D_001ED188[0][index].unk980[2] = color[2];
    D_001ED188[0][index].unk980[3] = color[3];
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            D_001ED188[0][index].unk00C[i][j] = 0;
            D_001ED188[0][index].unk19C[i][j] = 0;
        }
    }
}

void func_00111448(int arg0) {
    D_001ED190 = arg0;
}
