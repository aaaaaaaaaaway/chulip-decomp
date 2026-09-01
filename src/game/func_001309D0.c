extern unsigned char D_001FE240[];

extern void func_00187308(int a, int b, int c, int d);
extern void func_001871E0(void);
extern void func_00187590(unsigned char *buffer, int a, int b, int c, int d, int e, int f);
extern void func_00198A20(int a);
extern void func_001886A8(int a);
extern void func_00130A68(void);
extern void func_00187280(int a, int b);

void func_001309D0(void) {
    func_00187308(1, 1, 2, 1);
    func_001871E0();
    func_00187590(D_001FE240, 0, 0x200, 0xE0, 2, 0x31, 1);
    *(long *)(D_001FE240 + 0x100) = 0x3F80000080000000L;
    *(long *)(D_001FE240 + 0x1F0) = 0x3F80000080000000L;
    func_00198A20(0);
    func_001886A8(0);
    func_00130A68();
    func_00187280(0, 0);
}
