extern int D_002D8880[];

void func_00172168(int bits, unsigned char enable) {
    if (enable != 0) {
        D_002D8880[5] |= bits;
    } else {
        D_002D8880[5] &= ~bits;
    }
}
