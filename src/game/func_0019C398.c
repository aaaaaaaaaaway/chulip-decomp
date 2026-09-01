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
extern int D_001E5B84[];
extern int func_001987A0(ThreadParam *param);
void func_0019C398(void) {
    ThreadParam param;
    if (D_001E5B84[0] == (-1)) {
        param.unk14 = 0;
        param.unk8 = 1;
        param.unk4 = 1;
        D_001E5B84[0] = func_001987A0(&param);
    }
    return D_001E5B84[0];
}
