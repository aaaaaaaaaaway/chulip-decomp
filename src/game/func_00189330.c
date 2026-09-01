struct Command { int command; int argument; int f8; int result; };
extern struct Command D_002DE880;
extern char D_002DE640[];
extern int D_001E30A0[];
extern int func_0019B760(char *name, int a, int b, void *in, int inlen, void *out, int outlen, int g, int h);

int func_00189330(void) {
    int result;
    D_002DE880.command = 0xF;
    if (func_0019B760(D_002DE640, 1, 0, &D_002DE880, 0x80, &D_002DE880, 0x80, 0, 0) < 0) {
        return 0;
    }
    result = D_002DE880.result;
    if (result == 1) {
        D_001E30A0[0] = 0;
    }
    return result;
}
