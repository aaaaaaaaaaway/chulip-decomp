extern unsigned short *D_001ED740;

void func_00173468(unsigned int bits, unsigned char enable) {
    if (enable != 0) {
        D_001ED740[bits >> 16] |= bits;
    } else {
        D_001ED740[bits >> 16] &= ~bits;
    }
}
