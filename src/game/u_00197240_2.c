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

int func_001972C8(unsigned int *p)
{
    unsigned int v = *p;
    int n;

    if ((v & 7) != 0) {
        if ((v & 1) != 0) return 0;
        if ((v & 2) != 0) { *p = v >> 1; return 1; }
        *p = v >> 2;
        return 2;
    }
    n = 0;
    if ((v & 0xFFFF) == 0) { n = 16; v >>= 16; }
    if ((v & 0xFF) == 0) { n += 8; v >>= 8; }
    if ((v & 0xF) == 0) { n += 4; v >>= 4; }
    if ((v & 3) == 0) { n += 2; v >>= 2; }
    if ((v & 1) == 0) {
        v >>= 1;
        n += 1;
        if (v == 0) return 32;
    }
    *p = v;
    return n;
}
