struct Quad_00136458 { unsigned char data[0x10]; };

extern struct Quad_00136458 D_001FF3E0[];

extern void func_0018A680(void *dst, struct Quad_00136458 *src);

void func_00136458(unsigned char index, void *a, void *b) {
    func_0018A680(a, &D_001FF3E0[index * 4]);
    func_0018A680(b, &D_001FF3E0[index * 4 + 1]);
}
