
extern unsigned int D_001ED400;
extern unsigned int D_001ED404;

extern void func_00198A20(int arg0);

void func_0014B5C8(void) {
    *(volatile unsigned int *)0x1000A020 = D_001ED404;
    *(volatile unsigned int *)0x1000A010 = D_001ED400 & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000E010 = 1;
    func_00198A20(0);
    *(volatile unsigned int *)0x1000A000 = 0x101;
}
