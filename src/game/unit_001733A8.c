extern unsigned short *D_001ED740;

void func_001733A8(unsigned short bits, unsigned char enable) {
    if (enable != 0) {
        D_001ED740[0] |= bits;
    } else {
        D_001ED740[0] &= ~bits;
    }
}

void func_001733E8(unsigned short bits, unsigned char enable) {
    if (enable != 0) {
        D_001ED740[1] |= bits;
    } else {
        D_001ED740[1] &= ~bits;
    }
}
