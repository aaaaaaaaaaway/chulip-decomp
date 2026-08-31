extern char *D_001ED08C[];
extern char *D_001ED090;

void func_00105E98(int index, int mode) {
    *(int *)(D_001ED08C[1] + index * 0x2B0 + 0x14) = 1;
    if (mode != 0) {
        if (mode == 1) {
            *(int *)(D_001ED090 + index * 0x2B0 + 8) = mode;
        }
    } else {
        *(int *)(D_001ED08C[1] + index * 0x2B0 + 8) = -1;
    }
}
