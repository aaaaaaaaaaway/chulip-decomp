typedef struct {
    int unk00;
    int unk04;
    int pad08[2];
    float unk10[4];
    int unk20[4];
    int unk30;
    int pad34[3];
    float unk40[4];
    int unk50[4];
    int unk60;
    int pad64[3];
} Emitter;

extern Emitter *D_001ED0D4[1];

extern int D_001ED0DC;

void func_00108FB0(int index, int mode, float *pos, int flags, int *color,
                   float *pos2, int flags2, int *color2) {
    D_001ED0D4[0][index].unk04 = mode;
    D_001ED0D4[0][index].unk10[0] = pos[0];
    D_001ED0D4[0][index].unk10[1] = pos[1];
    D_001ED0D4[0][index].unk10[2] = pos[2];
    D_001ED0D4[0][index].unk10[3] = 1.0f;
    D_001ED0D4[0][index].unk20[0] = color[0];
    D_001ED0D4[0][index].unk20[1] = color[1];
    D_001ED0D4[0][index].unk20[2] = color[2];
    D_001ED0D4[0][index].unk20[3] = color[3];
    D_001ED0D4[0][index].unk30 = flags;
    D_001ED0D4[0][index].unk40[0] = pos2[0];
    D_001ED0D4[0][index].unk40[1] = pos2[1];
    D_001ED0D4[0][index].unk40[2] = pos2[2];
    D_001ED0D4[0][index].unk40[3] = 1.0f;
    D_001ED0D4[0][index].unk50[0] = color2[0];
    D_001ED0D4[0][index].unk50[1] = color2[1];
    D_001ED0D4[0][index].unk50[2] = color2[2];
    D_001ED0D4[0][index].unk50[3] = color2[3];
    D_001ED0D4[0][index].unk60 = flags2;
}

void func_00109130(int arg0) {
    D_001ED0DC = arg0;
}
