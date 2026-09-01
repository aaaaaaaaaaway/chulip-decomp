extern int D_002E4080[];
extern int D_002E3E80[];
extern int func_0019F818(void);
extern int func_0019F918(void);
extern int func_0019B760(int *name, int a, int b, int *in, int inlen,
                         int *out, int outlen, int f, int g);

int func_0019FF20(int arg) {
    if (func_0019F818() < 0) {
        return 0xFFFF0000;
    }
    if (func_0019F918() != 0) {
        return 0xFFFEFFFC;
    }
    D_002E3E80[0] = arg;
    if (func_0019B760(D_002E4080, 0xA, 0, D_002E3E80, 4, D_002E3E80, 4, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    return D_002E3E80[0];
}
