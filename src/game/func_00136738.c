struct Vec16_00136738 { int field_0x0; int field_0x4; int field_0x8; int field_0xC; };
struct Ctx_00136738 { unsigned char pad_0x0[0x41]; unsigned char field_0x41; unsigned char pad_0x42[6]; };

extern struct Ctx_00136738 *func_00136AE8(void);
extern void func_001618A0(struct Vec16_00136738 *dst, const unsigned char *src);
extern void func_001362C8(struct Vec16_00136738 *value);
extern void func_00136340(struct Vec16_00136738 *value);
extern void func_001362F0(struct Vec16_00136738 *value);
extern void func_00128378(struct Vec16_00136738 *dst, struct Vec16_00136738 *a, struct Vec16_00136738 *b);
extern void func_0014D7A8(struct Vec16_00136738 *value);

void func_00136738(const unsigned char *src) {
    struct Vec16_00136738 position;
    struct Vec16_00136738 rotation;
    struct Vec16_00136738 scale;
    struct Ctx_00136738 *ctx;

    ctx = func_00136AE8();
    func_001618A0(&position, src);
    func_001618A0(&rotation, src + 0x20);
    func_001618A0(&scale, src + 0x10);
    func_001362C8(&position);
    func_00136340(&rotation);
    func_001362F0(&scale);
    if (ctx->field_0x41 == 1) {
        func_00128378(&position, &position, &rotation);
        func_0014D7A8(&position);
    }
}
