extern unsigned char D_001ECE40;
extern unsigned char D_002D8A00[];
extern void func_001638B0(void);

void func_00163908(void) {
    D_001ECE40 = 16;
    D_002D8A00[0] = 255;
    func_001638B0();
}
