extern int D_002DB540[];

typedef int (*DrawCallback)(char *packet, int arg0, int arg1);
int func_0017FA98(char *packet, int n, int unused);
void func_0017F9F0(DrawCallback fn);
void func_0017F9B8(DrawCallback fn, int a, int b);
int func_0017FBB0(char *packet, int arg0, int arg1);
int func_001803D0(char *packet, int arg0, int arg1);
int func_00180F48(char *packet, int arg0, int arg1);
int func_0017FC00(char *packet, int arg0, int arg1);
int func_00181700(char *packet, int arg0, int arg1);

int func_0017FA98(char *packet, int n, int unused) {
    int i = n;
    int *state = &D_002DB540[n];

    switch (*state) {
    case 0:
        *state = 1;
        break;
    case 1:
        n++;
        func_0017F9F0(func_0017FA98);
        func_0017F9B8(func_0017FBB0, 0, 0);
        D_002DB540[0] = 0;
        func_0017F9B8(func_001803D0, 0, 0);
        *state = 0;
        func_0017F9B8(func_00180F48, i, 0);
        D_002DB540[n] = 0;
        func_0017F9B8(func_0017FC00, n++, 0);
        D_002DB540[n] = 0;
        func_0017F9B8(func_00181700, n, 0);
        break;
    }
    return 0;
}
