extern int D_001ECCAC;
extern int D_001ECCBC;
extern unsigned char D_002ABA40[];
extern unsigned short D_002BDA40[];
extern unsigned char D_002CFA40[];
extern int func_00151A00(int size);
extern char func_001923F4(void *buffer, int value, unsigned int size);
void func_00153918(void) {
    D_001ECCBC = func_00151A00(0x200000);
    D_001ECCAC = func_00151A00(0x14B000);
    func_001923F4(D_002ABA40, 0, 0x12000);
    func_001923F4(D_002BDA40, 0, 0x12000);
    func_001923F4(D_002CFA40, 0, 0x3800);
}
