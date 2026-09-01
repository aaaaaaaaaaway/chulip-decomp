extern char D_001E4310[];
extern int D_001E31C0[];
extern int D_001E3168[];
extern int func_0018F3E0(int mode);
extern void func_001987C0(int handle);
extern int func_0019B760(char *name, int a, int b, void *in, int inlen, void *out, int outlen, int g, int h);
extern int D_001E3150[];
extern int D_001E3170[];
extern char D_001EBAB0[];
extern void func_0019A778(char *message);
extern void func_0018EB18(int ticks);
extern int func_0019B950(char *name);

int func_0018F550(void) {
    int value;
    if (func_0018F3E0(2) == 0) {
        return 0;
    }
    if (func_0019B760(D_001E4310, 0xE, 0, 0, 0, D_001E31C0, 4, 0, 0) < 0) {
        func_001987C0(D_001E3168[0]);
        return 0;
    }
    value = *(int *)((unsigned int)D_001E31C0 | 0x20000000);
    func_001987C0(D_001E3168[0]);
    return value;
}

int func_0018F5E8(int mode) {
    if (mode == 0) {
        if (D_001E3150[0] > 0) {
            func_0019A778(D_001EBAB0);
        }
        while (D_001E3170[0] != 0 || func_0019B950(D_001E4310) != 0) {
            func_0018EB18(0x3C);
        }
        return 0;
    }
    if (D_001E3170[0] != 0 || func_0019B950(D_001E4310) != 0) {
        return 1;
    }
    return 0;
}
