extern int D_001E5B94[];
extern int D_002E3CC0[];
extern int D_002E3D40[];
extern int D_002E3D00[];
extern int func_0019B760(int *name, int a, int b, int *in, int inlen,
                         int *out, int outlen, int f, int g);

int func_0019F690(int arg) {
    if (D_001E5B94[0] < 0) {
        return 0;
    }
    D_002E3D40[0] = arg;
    if (func_0019B760(D_002E3CC0, 2, 0, D_002E3D40, 4, D_002E3D00, 4, 0, 0) < 0) {
        return -1;
    }
    return D_002E3D00[0];
}
