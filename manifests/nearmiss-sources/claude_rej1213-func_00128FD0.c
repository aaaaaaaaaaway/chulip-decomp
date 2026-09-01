extern unsigned char *D_001ED32C;
extern unsigned char *D_001ED330;

extern void *func_00151A00(int size);
extern void func_001923F4(unsigned char *dst, int value, int size);

void func_00128FD0(void) {
    D_001ED330 = func_00151A00(0x400);
    D_001ED32C = func_00151A00(0x800);
    func_001923F4(D_001ED330, 0, 0x400);
    func_001923F4(D_001ED32C, 0, 0x800);
    D_001ED32C[0] = 0x23;
    D_001ED32C[1] = 0x23;
}
