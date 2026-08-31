extern int D_001FF10C[];
extern int D_001FF19C[];

void func_00135788(int value) {
    D_001FF10C[0] = value;
}

int func_00135798(void) {
    return D_001FF10C[0];
}

void func_001357A8(void) {
    D_001FF10C[0] = 4;
}

int func_001357B8(void) {
    return D_001FF19C[0];
}
