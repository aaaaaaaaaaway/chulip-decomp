typedef struct {
    int unk00;
    int unk04;
    int unk08;
    int unk0C;
    float unk10[4];
    int unk20[4];
} Ripple;

extern Ripple *D_001ED0B4[1];
extern int func_00192568(void);

void func_001074E8(int index, int mode, float *pos, int *color) {
    D_001ED0B4[0][index].unk04 = mode;
    D_001ED0B4[0][index].unk08 = 0;
    D_001ED0B4[0][index].unk0C = func_00192568() % 0x168;
    D_001ED0B4[0][index].unk10[0] = pos[0];
    D_001ED0B4[0][index].unk10[1] = pos[1];
    D_001ED0B4[0][index].unk10[2] = pos[2];
    D_001ED0B4[0][index].unk10[3] = 1.0f;
    D_001ED0B4[0][index].unk20[0] = color[0];
    D_001ED0B4[0][index].unk20[1] = color[1];
    D_001ED0B4[0][index].unk20[2] = color[2];
    D_001ED0B4[0][index].unk20[3] = color[3];
}
