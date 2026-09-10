extern long D_001FFB40;

void func_00136AF8(unsigned char kind, unsigned char value) {
    switch (kind) {
    case 0:
        D_001FFB40 = (D_001FFB40 & -2) | (value & 1);
        break;
    case 0x11:
        D_001FFB40 = (D_001FFB40 & -0x20001) | ((long)(value & 1) << 17);
        break;
    case 0xA:
        D_001FFB40 = (D_001FFB40 & -0x101) | ((long)(value & 1) << 8);
        break;
    }
}
