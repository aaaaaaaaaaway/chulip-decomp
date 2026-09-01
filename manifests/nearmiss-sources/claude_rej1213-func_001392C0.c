struct Vec4_00205070 { float x; float y; float z; float w; };

extern struct Vec4_00205070 D_00205070[];

void func_001392C0(unsigned char index) {
    float *slot = (float *)&D_00205070[index];

    slot[0] = -1.0f;
    slot[1] = -1.0f;
    slot[2] = -1.0f;
    slot[3] = -1.0f;
}
