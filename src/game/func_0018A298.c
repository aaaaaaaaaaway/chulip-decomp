struct Command { int command; int argument; int f8; int result; };
extern struct Command D_002DE880;
extern char D_002DE640[];
extern int func_0019B760(char *name, int a, int b, void *in, int inlen, void *out, int outlen, int g, int h);

int func_0018A298(int argument) {
    D_002DE880.argument = argument;
    D_002DE880.command = 0xD;
    if (func_0019B760(D_002DE640, 1, 0, &D_002DE880, 0x80, &D_002DE880, 0x80, 0, 0) < 0) {
        return 0;
    }
    return D_002DE880.result;
}
