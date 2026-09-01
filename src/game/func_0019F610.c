extern int D_001E5B94[];
extern int D_002E3CC0[];
extern int D_002E3D40[];
extern int D_002E3D00[];
extern int func_0019B760(int *name, int a, int b, int *in, int inlen,
                         int *out, int outlen, int f, int g);

int func_0019F610(int arg0, int arg1, int arg2) {
    if (D_001E5B94[0] < 0) {
        return 0;
    }
    D_002E3D40[0] = arg1;
    D_002E3D40[1] = arg0;
    D_002E3D40[2] = arg2;
    if (func_0019B760(D_002E3CC0, 4, 0, D_002E3D40, 0xC, D_002E3D00, 4, 0, 0) < 0) {
        return 0;
    }
    return D_002E3D00[0];
}
