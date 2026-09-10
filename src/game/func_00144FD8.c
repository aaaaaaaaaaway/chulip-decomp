struct Ctx_001ED3C8 {
    unsigned char field_0x0[0x8];
    short field_0x8;
    unsigned char field_0xA[0x2];
    short field_0xC;
    unsigned char field_0xE[0x6];
    short field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1A;
};

struct Session {
    long flags;
};

union CtxRef { struct Ctx_001ED3C8 *ctx; };
extern union CtxRef D_001ED3C8;
extern int D_001ED3D8;
extern char D_001E8E78[];
extern char D_001E8E90[];
extern char D_001ECA00[];
extern char D_001ECA08[];

extern void func_00128A50(int arg);
extern void func_0017F340(void);
extern void func_0017F768(int arg);
extern int func_0017F730(void);
extern void func_00179360(int a, int b, int c);
extern void func_0017F5C8(int a, int b);
extern int func_0017F440(void);
extern int func_0017C908(int arg);
extern int func_0017C450(int a, int b);
extern int func_00192660(char *out, char *format, ...);
extern void func_00192940(char *dst, char *src);
extern void func_001926D0(char *dst, char *src);
extern int func_0017C830(int a, int b, char *c, char *d);
extern void func_00139EB8(int arg);
extern void func_00178470(void);
extern struct Session *func_00136AE8(void);
extern void func_0017CCF0(void);
extern void func_00173050(int a, int b);
extern int func_0017F7D8(void);

void func_00144FD8(void) {
    char text[0x20];
    char line[0x20];
    struct Session *session;

    switch (D_001ED3C8.ctx->field_0x14) {
    case 0:
        func_00128A50(1);
        func_0017F340();
        func_0017F768(0);
        D_001ED3C8.ctx->field_0x16 = 0;
        D_001ED3C8.ctx->field_0x18 = 0;
        D_001ED3C8.ctx->field_0x8 = 0xB4;
        D_001ED3C8.ctx->field_0xC = 0;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 1:
        if ((func_0017F730() & 0x16) == 0) {
            func_0017F768(1);
            break;
        }
        if ((func_0017F730() & 0x80) == 0) {
            break;
        }
        D_001ED3C8.ctx->field_0x16 = 0;
        D_001ED3C8.ctx->field_0x14 = 3;
        func_00179360(0x1000, 0, 0x80);
        break;
    case 2:
        if (func_0017F730() & 0x40) {
            break;
        }
        if (func_0017F730() & 0x20) {
            D_001ED3C8.ctx->field_0x14 = 4;
            break;
        }
        if ((func_0017F730() & 0xE) == 0) {
            if (D_001ED3C8.ctx->field_0x18 < D_001ED3C8.ctx->field_0x1A) {
                func_0017F768((unsigned char)(D_001ED3C8.ctx->field_0x18 + 1));
            }
            D_001ED3C8.ctx->field_0x18 = D_001ED3C8.ctx->field_0x18 + 1;
        }
        func_0017F5C8(D_001ED3C8.ctx->field_0x16++, 1);
        D_001ED3C8.ctx->field_0xC = D_001ED3C8.ctx->field_0xC + 1;
        D_001ED3C8.ctx->field_0x8 = 5;
        if (D_001ED3C8.ctx->field_0x16 == 0x3C) {
            D_001ED3C8.ctx->field_0x16 = 0;
            D_001ED3C8.ctx->field_0x14 = 3;
        }
        break;
    case 3:
        if (func_0017F730() & 0x40) {
            break;
        }
        if (func_0017F730() & 0x20) {
            D_001ED3C8.ctx->field_0x14 = 4;
            break;
        }
        if ((func_0017F730() & 0x16) == 0) {
            if (D_001ED3C8.ctx->field_0x18 < D_001ED3C8.ctx->field_0x1A) {
                func_0017F768((unsigned char)(D_001ED3C8.ctx->field_0x18 + 1));
            }
            D_001ED3C8.ctx->field_0x18 = D_001ED3C8.ctx->field_0x18 + 1;
        }
        func_0017F5C8(D_001ED3C8.ctx->field_0x16++, 0);
        D_001ED3C8.ctx->field_0xC = D_001ED3C8.ctx->field_0xC + 1;
        D_001ED3C8.ctx->field_0x8 = 5;
        if (D_001ED3C8.ctx->field_0x16 == 0x3C) {
            D_001ED3C8.ctx->field_0x16 = 0;
            D_001ED3C8.ctx->field_0x14 = 2;
        }
        break;
    case 4:
        func_0017F440();
        func_0017C908(0x12);
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 5:
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        func_00192660(text, D_001E8E78);
        func_00192940(line, text);
        func_001926D0(line, D_001ECA00);
        func_001926D0(text, D_001ECA08);
        func_0017C830(1, 2, text, line);
        func_00139EB8(D_001ED3D8);
        break;
    case 50:
        func_00178470();
        session = func_00136AE8();
        func_0017CCF0();
        session->flags = session->flags & ~0x400000;
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 51:
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        func_00173050(0xE, -1);
        func_0017C908(0x10);
        func_0017C908(0x12);
        D_001ED3C8.ctx->field_0x14 = D_001ED3C8.ctx->field_0x14 + 1;
        break;
    case 52:
        if (func_0017C450(0, 0) == 0) {
            break;
        }
        func_00192660(text, D_001E8E90, func_0017F7D8());
        func_00192940(line, text);
        func_001926D0(line, D_001ECA00);
        func_001926D0(text, D_001ECA08);
        func_0017C830(1, 2, text, line);
        D_001ED3C8.ctx->field_0x14 = 0;
        break;
    }
}
