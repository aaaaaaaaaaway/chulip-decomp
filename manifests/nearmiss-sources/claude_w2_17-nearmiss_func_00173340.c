extern unsigned short *D_001ED740;

int func_00173340(int mask) {
    unsigned int bits;

    if (mask < 0) {
        bits = -mask;
        return (D_001ED740[bits >> 16] & bits) == 0;
    }
    bits = mask;
    return (D_001ED740[bits >> 16] & bits) != 0;
}
