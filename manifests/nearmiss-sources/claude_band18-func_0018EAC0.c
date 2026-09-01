typedef union {
    float f;
    int i;
} FloatBits;

float func_0018EAC0(float value, float sign) {
    FloatBits v;
    FloatBits s;

    s.f = sign;
    v.f = value;
    v.i = (v.i & 0x7FFFFFFF) | (s.i & 0x80000000);
    return v.f;
}
