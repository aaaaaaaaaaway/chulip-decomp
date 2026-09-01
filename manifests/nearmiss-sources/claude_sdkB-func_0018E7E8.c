typedef unsigned int u32;
typedef union { float value; u32 word; } tf;
float func_0018E7E8(float x) {
    u32 ix; tf u;
    u.value = x; ix = u.word;
    ix = ix & 0x7FFFFFFF;
    u.word = ix;
    return u.value;
}
