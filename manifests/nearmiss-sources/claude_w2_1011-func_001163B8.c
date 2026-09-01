extern signed char D_001ED1DD;
extern int D_001ED1E8;
float D_001EC8BC __attribute__((section(".sdata"))) = 0.0f;
char D_001EC8C0[4] __attribute__((section(".sdata"))) = { 0, 0, 0, 0 };
void func_0017DBD0(int a, int b);
void func_0017E6C8(int a, int b);

void func_001163B8(unsigned char on) {
    if (on) {
        func_0017DBD0(0xF, 2);
        func_0017DBD0(0x10, 2);
        D_001ED1DD = 1;
    } else {
        func_0017E6C8(0xF, 0x41);
        func_0017E6C8(0x10, 0x41);
        D_001ED1DD = 0;
    }
    D_001EC8C0[0] = 0;
    D_001ED1E8 = 0;
    D_001EC8BC = 1.5707964f;
}
