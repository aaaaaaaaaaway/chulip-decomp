typedef struct {
    char pad0[0x20];
    int f20;
    char pad1[0xC];
    int f30;
    char pad2[0xC];
    char *f40;
    char pad3[8];
    int f4C;
} Ctx;

extern char *D_002D81B0[];

int func_00181EA8();
void func_001614F8(char *p, Ctx *ctx, int a, int b);
void func_00161350(char *p, int a);
void func_00161448(char *p, int a, int b);
void func_00161430(char *p, int a);
void func_00161590(char *p, int a);
char *func_00179C80(Ctx *ctx, char *q, int b, int c);

char *func_00179B50(Ctx *ctx, int b, int c) {
    int i;
    char *q;
    char *base;
    char *p;

    q = ctx->f40;
    ctx->f20 = func_00181EA8();
    ctx->f30 = 0;
    q += 0x10;
    base = D_002D81B0[1];
    func_001614F8(base, ctx, 8, 8);
    p = base + 0x10;
    func_00161350(p, 0);
    func_00161448(p, 2, 0);
    func_00161430(p, 3);
    p = base + 0x20;
    D_002D81B0[1] = p;
    for (i = 0; i < ctx->f4C; i++) {
        q = func_00179C80(ctx, q, b, c);
    }
    p = D_002D81B0[1];
    func_00161590(p, 0);
    p += 0x10;
    D_002D81B0[1] = p;
    return base;
}
