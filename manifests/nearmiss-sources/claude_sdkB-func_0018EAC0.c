typedef unsigned int u32;
typedef union { float value; u32 word; } ieee_float_shape_type;

float func_0018EAC0(float x, float y) {
    u32 ix, iy;
    { ieee_float_shape_type gf_u; gf_u.value = x; ix = gf_u.word; }
    { ieee_float_shape_type gf_u; gf_u.value = y; iy = gf_u.word; }
    { ieee_float_shape_type sf_u; sf_u.word = (ix & 0x7FFFFFFF) | (iy & 0x80000000); x = sf_u.value; }
    return x;
}
