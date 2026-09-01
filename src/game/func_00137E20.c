extern int D_001EC9E0;
extern char D_001E7C38[];

extern void func_00151CA8(int handle);
extern void func_00125ED0(char *name, int *out, int a, int b, int c);

void func_00137E20(void) {
    int base;
    unsigned int i;
    int *entry;

    if (D_001EC9E0 != 0) {
        func_00151CA8(D_001EC9E0);
        D_001EC9E0 = 0;
    }
    func_00125ED0(D_001E7C38, &D_001EC9E0, 0, -1, 1);
    base = D_001EC9E0;
    for (i = 0; i < 0x17; i++) {
        entry = (int *)(i * 8 + D_001EC9E0);
        if (entry[2] != 0) {
            entry[2] = entry[2] + base;
        }
    }
}
