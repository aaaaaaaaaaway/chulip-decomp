typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
} ThreadParam;

extern int D_001E3160[];
extern int D_001E3168[];
extern int D_001E316C[];
extern int D_001E3170[];
extern int func_001987A0(ThreadParam *param);

int func_0018EEB0(void) {
    ThreadParam param;

    if (D_001E3168[0] == -1 || D_001E316C[0] == -1) {
        param.unk14 = 0;
        param.unk8 = 1;
        param.unk4 = 1;
        D_001E3168[0] = func_001987A0(&param);
        D_001E316C[0] = func_001987A0(&param);
        param.unk8 = 0;
        D_001E3160[0] = func_001987A0(&param);
        D_001E3170[0] = 0;
        return D_001E3160[0];
    }
    return D_001E316C[0];
}
