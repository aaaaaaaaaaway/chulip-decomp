extern int D_001ECCB8;
extern void func_00151CA8(int handle);
extern void func_0015A250(void);
extern void func_0015DB40(void);

void func_0015A628(void) {
    if (D_001ECCB8 != 0) {
        func_00151CA8(D_001ECCB8);
        D_001ECCB8 = 0;
    }
    func_0015A250();
}

void func_0015A658(void) {
    func_0015DB40();
}
