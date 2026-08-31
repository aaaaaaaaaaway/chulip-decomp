struct Vec4_001391E8 { float x; float y; float z; float w; };

extern struct Vec4_001391E8 D_00205070[];

unsigned char func_001391E8(void) {
    unsigned char i = 0;

    while (i < 8) {
        struct Vec4_001391E8 *slot = &D_00205070[i];

        if (slot->x == -1.0f && slot->y == -1.0f && slot->z == -1.0f) {
            return i;
        }
        i = i + 1;
    }
    return 0xFF;
}
