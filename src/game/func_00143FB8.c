struct Ctx {
    char pad_0x0[0x14];
    short field_0x14;
    short field_0x16;
};

struct CtxRef { struct Ctx *ptr; int pad; };

extern struct CtxRef D_001ED3C8;
extern int D_001ED3D8;

extern void func_0017DBD0(int arg0, int arg1);
extern void func_00139EB8(int arg0);

void func_00143FB8(void) {
    struct Ctx *ctx = D_001ED3C8.ptr;

    switch (ctx->field_0x14) {
    case 0:
        ctx->field_0x14 = ctx->field_0x14 + 1;
        break;
    case 1:
        if (ctx->field_0x16-- <= 0) {
            func_0017DBD0(0x21, 9);
            func_00139EB8(D_001ED3D8);
        }
        break;
    }
}
