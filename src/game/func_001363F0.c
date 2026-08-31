struct Quad_001363F0 { unsigned char data[0x10]; };

extern struct Quad_001363F0 D_001FF3E0[];
extern struct Quad_001363F0 D_001A7830[];

extern void func_0018A680(struct Quad_001363F0 *dst, struct Quad_001363F0 *src);

void func_001363F0(unsigned char index) {
    func_0018A680(&D_001FF3E0[index * 4], &D_001A7830[index * 4]);
    func_0018A680(&D_001FF3E0[index * 4 + 1], &D_001A7830[index * 4 + 1]);
}
