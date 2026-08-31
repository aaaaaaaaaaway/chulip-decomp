extern unsigned short D_001ECF88;

void func_0017F738(unsigned char bits, unsigned char enable) {
    if (enable != 0) {
        D_001ECF88 |= bits;
    } else {
        D_001ECF88 &= ~bits;
    }
}
