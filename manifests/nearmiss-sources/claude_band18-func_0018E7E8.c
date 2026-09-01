typedef union {
    float f;
    int i;
} FloatBits;

float func_0018E7E8(float x) {
    FloatBits in;
    FloatBits out;

    in.f = x;
    out.i = in.i & 0x7FFFFFFF;
    return out.f;
}
