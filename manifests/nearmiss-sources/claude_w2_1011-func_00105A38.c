extern unsigned short D_001ED08A;
extern int D_001ED08C;

void func_00105A38(unsigned short index, unsigned char on) {
    unsigned short *p;

    if (on) {
        *(unsigned short *)((D_001ED08A + index) * 0x2C + D_001ED08C) |= 0x800;
        p = (unsigned short *)((D_001ED08A + index) * 0x2C + D_001ED08C);
        *p |= 0x8000;
    } else {
        *(unsigned short *)((D_001ED08A + index) * 0x2C + D_001ED08C) &= 0xF7FF;
        p = (unsigned short *)((D_001ED08A + index) * 0x2C + D_001ED08C);
        *p &= 0x7FFF;
    }
}
