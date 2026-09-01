typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    char name[0x400];
} Request;

extern Request D_002DEC70;
extern int D_001E4BC0[];
extern int D_001E4BC4[];
extern int D_002DEBC0[];
extern int D_002E0180[];
extern int func_001987F0(int semaphore);
extern void func_001987C0(int semaphore);
extern char *func_00192B90(char *dst, const char *src, int size);
extern int func_0019B760(int *name, int a, int b, int *in, int inlen,
                         int *out, int outlen, int f, int g);

int func_001901A8(int arg0, int arg1, const char *name, int arg3) {
    int result;

    if (func_001987F0(D_001E4BC4[0]) < 0) {
        return -0xC8;
    }
    if (D_002DEBC0[9] == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -0x64;
    }
    if (name == 0 || *name == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -0xD2;
    }
    func_00192B90(D_002DEC70.name, name, 0x3FF);
    D_002DEC70.unk0 = arg0; //#P
    D_002DEC70.unk8 = arg3; //#P
    D_002DEC70.unk4 = arg1; //#P
    D_002DEC70.name[0x3FF] = 0;
    result = func_0019B760(D_002DEBC0, 2, 1, (int *)&D_002DEC70, 0x414,
                           D_002E0180, 4, 0, 0);
    if (result == 0) {
        D_001E4BC0[0] = 2;
    } else {
        func_001987C0(D_001E4BC4[0]);
    }
    return result;
}
