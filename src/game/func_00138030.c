struct Ctx_00138030 {
    long field_0x0;
    unsigned char pad_0x8[0x3E];
    unsigned char field_0x46;
    unsigned char field_0x47;
    unsigned char pad_0x48[5];
    unsigned char field_0x4D;
    unsigned char field_0x4E;
};

extern struct Ctx_00138030 *func_00136AE8(void);
extern void func_00138070(void);

void func_00138030(void) {
    volatile long scratch;
    struct Ctx_00138030 *ctx;

    ctx = func_00136AE8();
    scratch = 0;
    ctx->field_0x0 = 0;
    ctx->field_0x46 = 0xFF;
    ctx->field_0x47 = 0xFF;
    ctx->field_0x4D = 0xFF;
    ctx->field_0x4E = 0xFF;
    func_00138070();
}
