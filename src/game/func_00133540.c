struct Owner_00133540 { unsigned char pad_0x0[0x4]; unsigned char *slots; };

void func_00133540(struct Owner_00133540 *owner, const float *src, unsigned char index) {
    float *dst = (float *)(owner->slots + index * 0x40);

    if (src[0] != -1.0f) {
        dst[4] = src[0];
    }
    if (src[1] != -1.0f) {
        dst[5] = src[1];
    }
    if (src[2] != -1.0f) {
        dst[6] = src[2];
    }
}
