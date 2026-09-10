struct Ctx_001ED3C8 {
    unsigned char field_0x0[0x8];
    short field_0x8;
    unsigned char field_0xA[0xA];
    short field_0x14;
    unsigned char field_0x16;
    unsigned char field_0x17;
    short field_0x18;
    short field_0x1A;
};

struct Session {
    long flags;
};

union CtxRef_001ED3C8 { struct Ctx_001ED3C8 *ctx; };
extern union CtxRef_001ED3C8 D_001ED3C8;
extern int D_001ED3D8;

extern struct Session *func_00136AE8(void);
extern int func_0017C450(int mode, int arg);
extern void func_0017CC88(int arg);
extern void func_0017CCF0(void);
extern int func_0012FCA8(int arg);
extern void func_0017CC10(int arg);
extern void func_0017C658(int arg, int value);
extern void func_00139EB8(int arg);

void func_00148CE0(void) {
    struct Session *session;
    long flags;
    int bit;

    session = func_00136AE8();
    if (func_0017C450(0, 0) == 0) {
        return;
    }
    switch (D_001ED3C8.ctx->field_0x14) {
    case 1:
        flags = session->flags;
        bit = (int)(flags >> 2) & 1;
        if (bit == 1) {
            return;
        }
        bit = (int)(flags >> 1) & 1;
        if (bit == 1) {
            return;
        }
        bit = (int)(flags >> 10) & 1;
        if (bit == 1) {
            return;
        }
        func_0017CC88(D_001ED3C8.ctx->field_0x18);
        func_00139EB8(D_001ED3D8);
        break;
    case 10:
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 11:
        func_0017CCF0();
        session->flags = session->flags & ~0x400000;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 12:
        func_0017CC10(func_0012FCA8(D_001ED3C8.ctx->field_0x16));
        D_001ED3C8.ctx->field_0x8 = 8;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 20:
        func_0017C658(0, D_001ED3C8.ctx->field_0x1A);
        D_001ED3C8.ctx->field_0x8 = D_001ED3C8.ctx->field_0x1A;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 21:
        func_0017CCF0();
        session->flags = session->flags & ~0x400000;
    case 13:
        func_00139EB8(D_001ED3D8);
        break;
    case 30:
        flags = session->flags;
        bit = (int)(flags >> 2) & 1;
        if (bit == 1) {
            return;
        }
        bit = (int)(flags >> 1) & 1;
        if (bit == 1) {
            return;
        }
        bit = (int)(flags >> 10) & 1;
        if (bit == 1) {
            return;
        }
        func_0017CCF0();
        session->flags = session->flags & ~0x400000;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 0:
    case 31:
        flags = session->flags;
        bit = (int)(flags >> 2) & 1;
        if (bit == 1) {
            return;
        }
        bit = (int)(flags >> 1) & 1;
        if (bit == 1) {
            return;
        }
        bit = (int)(flags >> 10) & 1;
        if (bit == 1) {
            return;
        }
        func_0017CC10(func_0012FCA8(D_001ED3C8.ctx->field_0x16));
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 32:
        flags = session->flags;
        bit = (int)(flags >> 2) & 1;
        if (bit == 1) {
            return;
        }
        bit = (int)(flags >> 1) & 1;
        if (bit == 1) {
            return;
        }
        bit = (int)(flags >> 10) & 1;
        if (bit == 1) {
            return;
        }
        func_0017C658(0x3FFF, 0);
        func_0017CC88(D_001ED3C8.ctx->field_0x18);
        func_00139EB8(D_001ED3D8);
        break;
    }
}
