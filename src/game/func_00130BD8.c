extern void func_00161338(long *dest, int a, int b, int c, int d);
extern void func_00198A20(int a);
extern void func_00187280(int a, int b);

void func_00130BD8(void) {
    long tag[2];
    long dest[2];

    tag[0] = 0x1000000000008001L;
    tag[1] = 0xE;
    func_00161338(dest, 0, 0x3D, 0, 0x404040);
    *(volatile int *)0x1000A020 = 2;
    *(volatile int *)0x1000A010 = (int)tag & 0xFFFFFFF;
    *(volatile int *)0x1000E010 = 2;
    func_00198A20(0);
    *(volatile int *)0x1000A000 = 0x101;
    func_00187280(0, 0);
}
