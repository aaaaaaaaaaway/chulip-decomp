struct Quad_001367E8 { unsigned char data[0x10]; };

extern unsigned short D_001EC9B0;
extern struct Quad_001367E8 D_001FF1A0[];

extern void func_001368D0(unsigned char index, struct Quad_001367E8 *a, struct Quad_001367E8 *b);

unsigned char func_001367E8(void) {
    int mask = D_001EC9B0;
    unsigned int i;

    for (i = 1; i < 0x14 && ((mask >> i) & 1) != 0; i++) {
    }
    D_001EC9B0 = mask | (1 << i);
    func_001368D0(i, &D_001FF1A0[0], &D_001FF1A0[1]);
    return i;
}
