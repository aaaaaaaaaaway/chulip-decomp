typedef struct {
    int unk00;
    int unk04;
    int unk08;
    int unk0C;
    float unk10[4];
    float unk20[4];
    int unk30[4];
    int unk40[4];
    int unk50;
    int unk54;
    int unk58;
    int unk5C;
} EntryA;

typedef struct {
    int unk00;
    int unk04;
    int unk08;
    float unk0C[3];
    int unk18[4];
    int unk28;
    float unk2C[3];
    int unk38[4];
    int unk48;
} EntryB;

extern EntryA *D_001ED128[1];
extern EntryB *D_001ED134[1];

void func_0010BF20(int index, int enable) {
    int i;

    if (enable == 0) {
        D_001ED128[0][index].unk00 = 0;
        return;
    }
    if (D_001ED128[0][index].unk00 != 0) {
        return;
    }
    D_001ED128[0][index].unk04 = D_001ED134[0][index].unk00;
    D_001ED128[0][index].unk08 = D_001ED134[0][index].unk04;
    D_001ED128[0][index].unk0C = D_001ED134[0][index].unk08;
    for (i = 0; i < 3; i++) {
        D_001ED128[0][index].unk10[i] = D_001ED134[0][index].unk0C[i];
        D_001ED128[0][index].unk20[i] = D_001ED134[0][index].unk2C[i];
    }
    D_001ED128[0][index].unk10[i] = 1.0f;
    D_001ED128[0][index].unk20[i] = 1.0f;
    for (i = 0; i < 4; i++) {
        D_001ED128[0][index].unk30[i] = D_001ED134[0][index].unk18[i];
        D_001ED128[0][index].unk40[i] = D_001ED134[0][index].unk38[i];
    }
    D_001ED128[0][index].unk50 = D_001ED134[0][index].unk28;
    D_001ED128[0][index].unk54 = D_001ED134[0][index].unk48;
    D_001ED128[0][index].unk00 = 1;
}
