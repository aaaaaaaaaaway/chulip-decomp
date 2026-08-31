extern unsigned short D_001EC9F0;
extern unsigned short D_002050F0[];

int func_001391A8(int key) {
    int i;

    for (i = 0; i < D_001EC9F0; i++) {
        if (D_002050F0[i] == key) {
            return 1;
        }
    }
    return 0;
}
