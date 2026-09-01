typedef union {
    double value;
    struct {
        int lo;
        int hi;
    } word;
} DoubleBits;
int func_0018E5D0(double x) {
    DoubleBits bits;
    int hx;
    int lx;
    do {
        bits.value = x;
        hx = bits.word.hi;
        lx = bits.word.lo;
    } while (0);
    hx &= 0x7FFFFFFF;
    hx |= ((unsigned int) (lx | (-lx))) >> 31;
    hx = 0x7FF00000 - hx;
    return (int) (((unsigned int) hx) >> 31);
}
