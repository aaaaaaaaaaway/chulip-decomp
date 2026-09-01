extern unsigned short D_001EC9B0;
extern unsigned char D_001FF1A0[];

extern void func_001368D0(unsigned char slot, unsigned char *a, unsigned char *b);

unsigned char func_001367E8(void) {
    unsigned short mask;
    unsigned int i;

    mask = D_001EC9B0;
    for (i = 1; i < 0x14; i++) {
        if (((mask >> i) & 1) == 0) {
            break;
        }
    }
    D_001EC9B0 = D_001EC9B0 | (1 << i);
    func_001368D0((unsigned char)i, D_001FF1A0, D_001FF1A0 + 0x10);
    return (unsigned char)i;
}
