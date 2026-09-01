extern int D_002DB540[];

int func_0017FA98(int a, int n);
void func_0017F9F0(void *fn);
void func_0017F9B8(void *fn, int a, int b);
void func_0017FBB0(void);
void func_001803D0(void);
void func_00180F48(void);
void func_0017FC00(void);
void func_00181700(void);

int func_0017FA98(int a, int n) {
    int i;

    switch (D_002DB540[n]) {
    case 0:
        D_002DB540[n] = 1;
        break;
    case 1:
        i = n + 1;
        func_0017F9F0(func_0017FA98);
        func_0017F9B8(func_0017FBB0, 0, 0);
        D_002DB540[0] = 0;
        func_0017F9B8(func_001803D0, 0, 0);
        D_002DB540[n] = 0;
        func_0017F9B8(func_00180F48, n, 0);
        D_002DB540[i] = 0;
        func_0017F9B8(func_0017FC00, i, 0);
        i++;
        D_002DB540[i] = 0;
        func_0017F9B8(func_00181700, i, 0);
        break;
    }
    return 0;
}
