extern unsigned short D_001ED08A;
extern int D_001ED08C;

void func_00105A38(unsigned short index, unsigned char on) {
    if (on) {
        *(unsigned short *)(D_001ED08C + (D_001ED08A + index) * 0x2C) |= 0x800;
        *(unsigned short *)(D_001ED08C + (D_001ED08A + index) * 0x2C) |= 0x8000;
    } else {
        *(unsigned short *)(D_001ED08C + (D_001ED08A + index) * 0x2C) &= 0xF7FF;
        *(unsigned short *)(D_001ED08C + (D_001ED08A + index) * 0x2C) &= 0x7FFF;
    }
}
