typedef struct {
    char pad0[0x50];
    int f50;
} Ctx;

typedef struct {
    int f00;
    int f04;
    int f08;
    int f0C;
    char pad[0x20];
} Node;

extern char *D_002D81B0[];
extern char D_001E15C0[];

void *func_0017A438(Ctx *ctx, int flag, int a);
void func_00161600(char *p, int a);
void func_00161870(char *p, void *a, int b);
void func_00181DF0(void);
Node *func_00179DC0(Node *e, int last);

Node *func_00179C80(Ctx *ctx, Node *q, int flag, int unused) {
    int i;
    int n;
    char *p;
    void *tex;
    int arg;
    int cond;
    int last;

    n = q->f04;
    arg = q->f08;
    cond = q->f0C;
    p = D_002D81B0[1];
    q++;
    if (flag != 0) {
        if (cond != 0) {
            tex = func_0017A438(ctx, flag, arg);
            if (tex != 0) {
                func_00161600(p, 0);
                p += 0x10;
                func_00161870(p, D_001E15C0, 1);
                p += 0x10;
                func_00161870(p, tex, 1);
                p += 0x10;
            }
        }
    }
    ctx->f50 = ctx->f50 + n;
    func_00181DF0();
    for (i = 0; i < n; i++) {
        D_002D81B0[1] = p;
        if (i == n - 1) {
            last = 1;
        } else {
            last = 0;
        }
        q = func_00179DC0(q, last);
        p = D_002D81B0[1];
    }
    D_002D81B0[1] = p;
    return q;
}
