struct Quad_00136948 { unsigned char data[0x10]; };

extern struct Quad_00136948 D_001A7830[];

extern void func_0018A680(void *dst, struct Quad_00136948 *src);

void func_00136948(unsigned char index, void *a, void *b) {
    func_0018A680(a, &D_001A7830[index * 4]);
    func_0018A680(b, &D_001A7830[index * 4 + 1]);
}
