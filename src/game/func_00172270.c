extern unsigned int D_002D8880[];

void func_00172270(unsigned char enable) {
    if (enable != 0) {
        D_002D8880[5] |= 0x80;
    } else {
        D_002D8880[5] &= 0xFFFFFF7F;
    }
}
