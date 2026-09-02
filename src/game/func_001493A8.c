struct Ctx {
    char pad_0x0[0xC];
    short field_0xc;
    unsigned short field_0xe;
    char pad_0x10[0x4];
    short field_0x14;
    unsigned short field_0x16;
    unsigned short field_0x18;
    short field_0x1a;
};

typedef struct { float x; float y; float z; float w; } Vec4;
typedef struct { Vec4 a; Vec4 b; } Pair;
struct Anim { Vec4 a; Vec4 b; char pad_0x20[0x10]; };

extern struct Ctx *D_001ED3C8;
#define CTX (*((struct Ctx *volatile *)&D_001ED3C8))
extern int D_001ED3D8;

extern Vec4 D_001A7F20[];
extern Vec4 D_001A7F80[];

extern int func_00154638(unsigned short index);
extern int func_00158D60(unsigned short index, int arg1, int arg2);
extern unsigned char func_00158678(unsigned short index);
extern void func_001363F0(unsigned char index);
extern void func_00136458(unsigned char index, Vec4 *a, Vec4 *b);
extern void func_001368D0(unsigned char index, Vec4 *a, Vec4 *b);
extern struct Anim *func_001781D8(unsigned short index);
extern void func_00139EB8(int state);

void func_001493A8(void) {
    Pair out;
    Pair in;
    struct Ctx *ctx;
    short prev;
    float t;

    switch (D_001ED3C8->field_0x14) {
    case 0:
        if (func_00154638(D_001ED3C8->field_0x16) == 0) {
            D_001ED3C8->field_0xe = func_00158D60(D_001ED3C8->field_0x16, 1, 1);
        } else {
            D_001ED3C8->field_0xe = func_00158678(D_001ED3C8->field_0x16);
        }
        func_001363F0(D_001ED3C8->field_0xe);
        D_001ED3C8->field_0xc = 0;
        CTX->field_0x14++;
        break;

    case 1:
        prev = D_001ED3C8->field_0xc++;
        ctx = CTX;
        if (prev < ctx->field_0x1a) {
            func_00136458(ctx->field_0xe, &in.a, &in.b);
            t = 1.0f - (float)D_001ED3C8->field_0xc / (float)D_001ED3C8->field_0x1a;
            if (D_001ED3C8->field_0x18 & 0x1000) {
                short index = D_001ED3C8->field_0x18 & 0xEFFF;
                Vec4 *pa = D_001A7F20 + index;
                Vec4 *pb = D_001A7F80 + index;

                out.a.x = pa->x + (in.a.x - pa->x) * t;
                out.a.y = pa->y + (in.a.y - pa->y) * t;
                out.a.z = pa->z + (in.a.z - pa->z) * t;
                out.b.x = pb->x + (in.b.x - pb->x) * t;
                out.b.y = pb->y + (in.b.y - pb->y) * t;
                out.b.z = pb->z + (in.b.z - pb->z) * t;
            } else {
                struct Anim *p = func_001781D8(D_001ED3C8->field_0x18);

                out.a.x = p->a.x + (in.a.x - p->a.x) * t;
                out.a.y = p->a.y + (in.a.y - p->a.y) * t;
                out.a.z = p->a.z + (in.a.z - p->a.z) * t;
                out.b.x = p->b.x + (in.b.x - p->b.x) * t;
                out.b.y = p->b.y + (in.b.y - p->b.y) * t;
                out.b.z = p->b.z + (in.b.z - p->b.z) * t;
            }
            func_001368D0(D_001ED3C8->field_0xe, &out.a, &out.b);
        } else {
            ctx->field_0x14++;
        }
        break;

    case 2:
        func_00139EB8(D_001ED3D8);
        break;
    }
}
