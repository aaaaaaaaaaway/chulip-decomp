struct Quad_00135BD8 { unsigned char data[0x10]; };

extern struct Quad_00135BD8 D_001FF1A0[];

extern void func_0018A680(struct Quad_00135BD8 *dst, struct Quad_00135BD8 *src);

void func_00135BD8(unsigned int group, unsigned int slot, struct Quad_00135BD8 *src) {
    if (group < 4 && slot < 4) {
        struct Quad_00135BD8 *dst =
            (struct Quad_00135BD8 *)((unsigned char *)D_001FF1A0 + group * 0xC0 + slot * 0x40);

        func_0018A680(&dst[1], &src[1]);
        func_0018A680(&dst[0], &src[0]);
        func_0018A680(&dst[2], &src[2]);
    }
}
