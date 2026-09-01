extern int D_002DE880[];
extern int D_002DE640[];
extern int func_0019B760(int *name, int a, int b, int *in, int inlen,
                         int *out, int outlen, int f, int g);
extern void func_00189830(int arg0, int arg1, int arg2);

int func_00189FA0(int arg0, int arg1, int arg2) {
    int status;

    D_002DE880[0] = 0xA; //#P
    D_002DE880[1] = arg0; //#P
    D_002DE880[2] = arg1; //#P
    D_002DE880[3] = arg2; //#P
    if (func_0019B760(D_002DE640, 1, 0, D_002DE880, 0x80, D_002DE880, 0x80, 0, 0) < 0) {
        return 0;
    }
    status = D_002DE880[4];
    if (status == 1) {
        func_00189830(arg0, arg1, 2);
        status = D_002DE880[4];
    }
    return status;
}
