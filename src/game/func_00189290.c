typedef struct {
    char pad0[0x10];
    int unk10;
    int unk14;
    int unk18;
} Slot;

extern Slot D_002DE690[];
extern int D_002DE880[];
extern int D_002DE640[];
extern int func_0019B760(int *name, int a, int b, int *in, int inlen,
                         int *out, int outlen, int f, int g);

int func_00189290(void) {
    int i;

    for (i = 0; i < 4; i++) {
        D_002DE690[i].unk10 = 0;
        D_002DE690[i].unk18 = 0;
        D_002DE690[i].unk14 = 0;
        D_002DE690[i + 4].unk10 = 0;
        D_002DE690[i + 4].unk18 = 0;
        D_002DE690[i + 4].unk14 = 0;
    }
    D_002DE880[0] = 0x10;
    D_002DE880[4] = 0;
    if (func_0019B760(D_002DE640, 1, 0, D_002DE880, 0x80, D_002DE880, 0x80, 0, 0) < 0) {
        return 0;
    }
    return D_002DE880[3];
}
