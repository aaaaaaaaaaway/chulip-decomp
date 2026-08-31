struct Vec4_001368D0 { float x; float y; float z; float w; };

extern struct Vec4_001368D0 D_001A7830[];

extern void func_0018A680(struct Vec4_001368D0 *dst, struct Vec4_001368D0 *src);

void func_001368D0(unsigned char index, struct Vec4_001368D0 *a, struct Vec4_001368D0 *b) {
    struct Vec4_001368D0 *base = &D_001A7830[index * 4];

    func_0018A680(base, a);
    func_0018A680(&D_001A7830[index * 4 + 1], b);
    base[0].w = 1.0f;
    base[1].w = 1.0f;
}
