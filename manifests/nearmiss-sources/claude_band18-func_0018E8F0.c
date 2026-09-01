typedef union {
    float f;
    int i;
} FloatBits;

int func_0018E8F0(float x) {
    FloatBits u;

    u.f = x;
    return (unsigned int)(0x7F800000 - (u.i & 0x7FFFFFFF)) >> 31;
}
