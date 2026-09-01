extern int D_001E5AA8[];
extern int D_001E5340[];
extern int D_001E5A80[];

extern void func_001994A0(int a, int b);
extern void func_001994B0(unsigned int addr, void *src, int size);
extern int func_001994F8(int a);
extern void func_00198A20(int a);

void func_00199508(void) {
    unsigned int i;
    int *p;
    int r;

    if ((*(volatile int *)0x10001810U & 0x100) != 0) {
        return;
    }
    func_001994A0(D_001E5AA8[0], D_001E5AA8[1]);
    func_001994B0(0x80076000U, D_001E5340, 0x740);
    func_001994B0(0x82000U, D_001E5A80, 0x28);
    func_00198A20(0);
    func_00198A20(2);
    func_001994A0(D_001E5AA8[2], D_001E5AA8[3]);
    p = &D_001E5AA8[4];
    for (i = 2; i < 8; i++) {
        r = func_001994F8(p[0]);
        func_001994A0(p[0], r);
        p += 2;
    }
}
