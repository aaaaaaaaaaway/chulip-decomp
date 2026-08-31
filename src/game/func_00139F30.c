extern unsigned short D_001EC9F0;
extern unsigned short D_002050F0[];

extern void func_00138798(unsigned short id);

void func_00139F30(void) {
    int i;

    for (i = 0; i < D_001EC9F0; i++) {
        func_00138798(D_002050F0[i]);
    }
    D_001EC9F0 = 0;
}
