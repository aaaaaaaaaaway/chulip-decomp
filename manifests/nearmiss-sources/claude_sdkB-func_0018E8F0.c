typedef unsigned int u32;
typedef union { float value; u32 word; } ieee_float_shape_type;

int func_0018E8F0(float x) {
    int ix;
    { ieee_float_shape_type gf_u; gf_u.value = x; ix = (int)gf_u.word; }
    ix &= 0x7FFFFFFF;
    return (int)((u32)(0x7F800000 - ix) >> 31);
}
