struct Quad_00136868 { unsigned char data[0x10]; };

extern void func_001618A0(struct Quad_00136868 *dst, struct Quad_00136868 *src);
extern void func_001368D0(unsigned char index, struct Quad_00136868 *a, struct Quad_00136868 *b);

void func_00136868(unsigned char index, struct Quad_00136868 *src) {
    struct Quad_00136868 a;
    struct Quad_00136868 b;

    if (index != 0xFF) {
        func_001618A0(&a, &src[0]);
        func_001618A0(&b, &src[1]);
        func_001368D0(index, &a, &b);
    }
}
