struct Ctx { char pad_0x0[0x14]; unsigned short field_0x14; short field_0x16; short field_0x18; };
struct CtxRef { struct Ctx *ptr; int pad; };
extern struct CtxRef D_001ED3C8;

extern void func_00156C90(int a, float b);
void func_0014AC08(void) {
    struct Ctx *ctx = D_001ED3C8.ptr;
    func_00156C90(ctx->field_0x14, (float)ctx->field_0x18);
}
