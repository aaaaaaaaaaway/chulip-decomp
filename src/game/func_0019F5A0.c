extern int D_001E5B94[];
extern char D_002E3CC0[];
extern int D_002E3D00[];
extern int D_002E3D40[];
extern int func_0019B760(char *name, int a, int b, void *in, int inlen, void *out, int outlen, int g, int h);

int func_0019F5A0(int argument) {
    if (D_001E5B94[0] < 0) {
        return 0;
    }
    D_002E3D40[0] = argument;
    if (func_0019B760(D_002E3CC0, 1, 0, D_002E3D40, 4, D_002E3D00, 4, 0, 0) < 0) {
        return 0;
    }
    return D_002E3D00[0];
}
