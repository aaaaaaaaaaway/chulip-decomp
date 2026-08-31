struct Quad_00136A90 { unsigned char data[0x10]; };

extern struct Quad_00136A90 D_001A77B0[];
extern struct Quad_00136A90 D_001A7D30[];

extern void func_0018A680(struct Quad_00136A90 *dst, struct Quad_00136A90 *src);

void func_00136A90(struct Quad_00136A90 *src) {
    func_0018A680(&D_001A77B0[0], &src[0]);
    func_0018A680(&D_001A77B0[1], &src[1]);
    func_0018A680(&D_001A7D30[0], &src[2]);
}
