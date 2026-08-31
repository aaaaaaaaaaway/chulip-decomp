int func_00197240(unsigned int x)
{
    int n = 0;

    if ((x & 0xFFFF0000) == 0) { n = 16; x <<= 16; }
    if ((x & 0xFF000000) == 0) { n += 8; x <<= 8; }
    if ((x & 0xF0000000) == 0) { n += 4; x <<= 4; }
    if ((x & 0xC0000000) == 0) { n += 2; x <<= 2; }
    if ((x & 0x80000000) == 0) {
        n += 1;
        if ((x & 0x40000000) == 0) return 32;
    }
    return n;
}
