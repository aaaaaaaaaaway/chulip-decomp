typedef union {
    double d;
    long i;
} DoubleBits;

int func_0018E5D0(double value) {
    DoubleBits u;
    int low;
    int high;

    u.d = value;
    low = (int)u.i;
    high = ((int)(u.i >> 32) & 0x7FFFFFFF) | (int)((unsigned int)(low | -low) >> 31);
    return (int)((unsigned int)(0x7FF00000 - high) >> 31);
}
