extern int D_001FF070[];
extern int D_001FF074[];
extern int D_001FF104[];

void func_001353E0(void) {
    D_001FF070[1] = 1;
    D_001FF070[25] = 0;
    D_001FF070[19] = 0;
    D_001FF070[20] = 0;
}

void func_00135400(int value) {
    D_001FF074[0] = value;
}

int func_00135410(void) {
    return D_001FF074[0];
}

void func_00135420(void) {
    D_001FF074[0] = 4;
}

int func_00135430(void) {
    return D_001FF104[0];
}
