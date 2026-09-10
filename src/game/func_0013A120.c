struct Ctx_001ED3C8 {
    unsigned char field_0x0[0x8];
    short field_0x8;
    unsigned char field_0xA[0xA];
    short field_0x14;
};

union CtxRef_001ED3C8 {
    struct Ctx_001ED3C8 *ctx;
};

struct Session {
    long flags;
    unsigned char field_0x8[0x39];
    unsigned char field_0x41;
    unsigned char field_0x42[0x10];
    unsigned char field_0x52;
};

extern union CtxRef_001ED3C8 D_001ED3C8;

extern struct Session *func_00136AE8(void);
extern int func_0012FCC0(void);
extern void func_0017C658(int a, int b);
extern int func_0017C450(int mode, int *out);
extern int func_00173428(int arg);
extern int func_0012FCA8(int arg);
extern int func_0017CC10(int arg);
extern void func_0017CC88(int arg);
extern void func_0017CCF0(void);

void func_0013A120(void) {
    struct Session *session;
    long flags;
    int bit;
    int ready;

    session = func_00136AE8();
    switch (D_001ED3C8.ctx->field_0x14) {
    case 0:
        if (session->field_0x52 == 0xFF) {
            break;
        }
        flags = session->flags;
        bit = (int)(flags >> 22) & 1;
        if (bit == 1) {
            if (func_0012FCC0() != 0) {
                break;
            }
            func_0017C658(0, 0x1E0);
            D_001ED3C8.ctx->field_0x8 = 0x1E0;
            D_001ED3C8.ctx->field_0x14 = 0x14;
            break;
        }
        if ((flags & 0x406) != 0) {
            break;
        }
        if (session->field_0x41 != 1) {
            break;
        }
        if (func_0012FCC0() == 0) {
            break;
        }
        if ((func_00173428(0) & 2) != 0) {
            break;
        }
        D_001ED3C8.ctx->field_0x14 = 0x1E;
        break;
    case 10:
        func_0017C450(0, &ready);
        if (ready == 0) {
            break;
        }
        if ((session->flags & 0x486) != 0) {
            break;
        }
        func_0017CC10(func_0012FCA8(session->field_0x52));
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 11:
        func_0017C450(0, &ready);
        if (ready != 0 && (session->flags & 0x486) == 0) {
            func_0017C658(0x3FFF, 0xF0);
            func_0017CC88(1);
            session->flags = session->flags | 0x400000;
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        if (session->field_0x41 != 1) {
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        if (func_0012FCC0() == 0) {
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        if ((func_00173428(0) & 2) == 0) {
            break;
        }
        D_001ED3C8.ctx->field_0x14 = 0;
        break;
    case 20:
        func_0017C450(0, &ready);
        if (ready == 0) {
            break;
        }
        if ((session->flags & 0x406) != 0) {
            break;
        }
        func_0017CCF0();
        session->flags = session->flags & ~0x400000;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 21:
        func_0017C450(0, &ready);
        if (ready == 0) {
            break;
        }
        if (((int)(session->flags >> 7) & 1) != 0) {
            break;
        }
        D_001ED3C8.ctx->field_0x14 = 0;
        break;
    case 30:
        func_0017C450(0, &ready);
        if (ready == 0) {
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        if (session->field_0x52 == 0xFF) {
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        if ((session->flags & 0x486) != 0) {
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        D_001ED3C8.ctx->field_0x14 = 0x64;
        break;
    case 31:
        func_0017C450(0, &ready);
        if (ready == 0) {
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        if (func_0012FCC0() == 0) {
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        if ((session->flags & 0x406) != 0) {
            D_001ED3C8.ctx->field_0x14 = 0;
            break;
        }
        func_0017C658(0x3FFF, 0xA);
        func_0017CC10(func_0012FCA8(session->field_0x52));
        D_001ED3C8.ctx->field_0x8 = 6;
        D_001ED3C8.ctx->field_0x14 = 0xB;
        break;
    case 40:
        func_0017C450(0, &ready);
        if (ready == 0) {
            break;
        }
        if ((session->flags & 0x406) != 0) {
            break;
        }
        func_0017C658(0, 0x78);
        D_001ED3C8.ctx->field_0x8 = 0x78;
        D_001ED3C8.ctx->field_0x14 = 0x14;
        break;
    case 50:
        func_0017C450(0, &ready);
        if (ready == 0) {
            break;
        }
        if ((session->flags & 0x406) != 0) {
            break;
        }
        func_0017C658(0, 0x28);
        D_001ED3C8.ctx->field_0x8 = 0x28;
        D_001ED3C8.ctx->field_0x14 = 0x14;
        break;
    case 100:
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        flags = session->flags;
        bit = (int)(flags >> 2) & 1;
        if (bit == 1) {
            break;
        }
        bit = (int)(flags >> 1) & 1;
        if (bit == 1) {
            break;
        }
        bit = (int)(flags >> 10) & 1;
        if (bit == 1) {
            break;
        }
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        func_0017CCF0();
        session->flags = session->flags & ~0x400000;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 101:
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        flags = session->flags;
        bit = (int)(flags >> 2) & 1;
        if (bit == 1) {
            break;
        }
        bit = (int)(flags >> 1) & 1;
        if (bit == 1) {
            break;
        }
        bit = (int)(flags >> 10) & 1;
        if (bit == 1) {
            break;
        }
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        func_0017CC10(func_0012FCA8(session->field_0x52));
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 102:
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        flags = session->flags;
        bit = (int)(flags >> 2) & 1;
        if (bit == 1) {
            break;
        }
        bit = (int)(flags >> 1) & 1;
        if (bit == 1) {
            break;
        }
        bit = (int)(flags >> 10) & 1;
        if (bit == 1) {
            break;
        }
        func_0017CC88(1);
        session->flags = session->flags | 0x400000;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 103:
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        flags = session->flags;
        bit = (int)(flags >> 2) & 1;
        if (bit == 1) {
            break;
        }
        bit = (int)(flags >> 1) & 1;
        if (bit == 1) {
            break;
        }
        bit = (int)(flags >> 10) & 1;
        if (bit == 1) {
            break;
        }
        func_0017C658(0x3FFF, 0xF0);
        D_001ED3C8.ctx->field_0x14 = 0;
        break;
    }
}
