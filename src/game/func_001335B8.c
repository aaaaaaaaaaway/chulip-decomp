struct Quad_001335B8 { unsigned char data[0x10]; };

struct Owner_001335B8 { unsigned char pad_0x0[0x8]; unsigned char *slots; };

extern void func_0018A680(struct Quad_001335B8 *dst, struct Quad_001335B8 *src);
extern void func_0018A3D0(void *dst, unsigned char *slot, struct Quad_001335B8 *src);

void func_001335B8(struct Owner_001335B8 *owner, int index, void *dst) {
    struct Quad_001335B8 quad;
    float value[4];
    unsigned char *slot = owner->slots + index * 0x90;

    value[0] = 1.0f;
    value[1] = 1.0f;
    value[2] = 1.0f;
    value[3] = 1.0f;
    func_0018A680(&quad, (struct Quad_001335B8 *)value);
    func_0018A3D0(dst, slot + 0x10, &quad);
}
