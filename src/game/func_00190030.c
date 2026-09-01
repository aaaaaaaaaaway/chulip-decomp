extern int D_001E4BC0[];
extern int D_001E4BC4[];
extern int D_002DEBC0[];
extern int D_002DEC40[];
extern int D_002E0180[];
extern int func_001987F0(int semaphore);
extern void func_001987C0(int semaphore);
extern int func_0019B760(int *name, int a, int b, int *in, int inlen,
                         int *out, int outlen, int f, int g);

int func_00190030(int arg) {
    int result;

    if (func_001987F0(D_001E4BC4[0]) < 0) {
        return -0xC8;
    }
    if (D_002DEBC0[9] == 0) {
        func_001987C0(D_001E4BC4[0]);
        return -0x64;
    }
    D_002DEC40[5] = arg;
    result = func_0019B760(D_002DEBC0, 0x14, 1, D_002DEC40, 0x30, D_002E0180, 4, 0, 0);
    if (result == 0) {
        D_001E4BC0[0] = 0x14;
    } else {
        func_001987C0(D_001E4BC4[0]);
    }
    return result;
}
