extern void *D_002A1E80[];
extern void *D_002A4280[];
extern void *D_002A5480[];
extern void *D_002A6680[];
extern void *D_002A7880[];
extern void *D_002A8A80[];
extern void *D_002A9C80[];

void func_00151CA8(void *p);

void func_001518C0(int i) {
    if (D_002A1E80[i] != 0) {
        func_00151CA8(D_002A1E80[i]);
        D_002A1E80[i] = 0;
    }
    if (D_002A5480[i] != 0) {
        func_00151CA8(D_002A5480[i]);
        D_002A5480[i] = 0;
    }
    if (D_002A6680[i] != 0) {
        func_00151CA8(D_002A6680[i]);
        D_002A6680[i] = 0;
    }
    if (D_002A7880[i] != 0) {
        func_00151CA8(D_002A7880[i]);
        D_002A7880[i] = 0;
    }
    if (D_002A8A80[i] != 0) {
        func_00151CA8(D_002A8A80[i]);
        D_002A8A80[i] = 0;
    }
    if (D_002A9C80[i] != 0) {
        func_00151CA8(D_002A9C80[i]);
        D_002A9C80[i] = 0;
    }
    if (D_002A4280[i] != 0) {
        func_00151CA8(D_002A4280[i]);
        D_002A4280[i] = 0;
    }
}
