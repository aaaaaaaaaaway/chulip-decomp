extern char *D_001ED0A4[];
extern char *D_001ED0A8;

void func_00106DB8(int index, int mode) {
    *(int *)(D_001ED0A4[1] + index * 0x1940 + 8) = 1;
    if (mode != 0) {
        if (mode == 1) {
            *(int *)(D_001ED0A8 + index * 0x1940 + 0x10) = mode;
        }
    } else {
        *(int *)(D_001ED0A4[1] + index * 0x1940 + 0x10) = -1;
    }
}
