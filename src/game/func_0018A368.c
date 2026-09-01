extern int D_002DE880[];
extern int D_002DE640[];
extern int func_0019B760(int *name, int a, int b, int *c, int d, int *e, int f, int g, int h);

int func_0018A368(int arg) {
    D_002DE880[1] = arg;
    D_002DE880[0] = 0x14;
    if (func_0019B760(D_002DE640, 1, 0, D_002DE880, 0x80, D_002DE880, 0x80, 0, 0) < 0) {
        return 0;
    }
    return D_002DE880[2];
}
