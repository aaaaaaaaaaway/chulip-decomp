struct Vec4_00205070 {
    float x;
    float y;
    float z;
    float w;
};
extern struct Vec4_00205070 D_00205070[];
void func_001392C0(unsigned char index) {
    struct Vec4_00205070 *temp;
    ((float *) (&D_00205070[index]))[0] = -1.0f;
    temp = &D_00205070[index];
    ((float *) temp)[1] = -1.0f;
    ((float *) temp)[2] = -1.0f;
    ((float *) temp)[3] = -1.0f;
}
