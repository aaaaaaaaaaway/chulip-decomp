typedef struct { float x; float y; float z; float w; } Vec4;

struct Ctx {
    char pad_0x0[0x8];
    short field_0x8;
    char pad_0xa[0x2];
    short field_0xc;
    char pad_0xe[0x6];
    short field_0x14;
    char pad_0x16[0x2];
    unsigned short field_0x18;
    short field_0x1a;
};

struct State {
    long flags;
};

extern struct Ctx *D_001ED3C8;
#define CTX (*((struct Ctx *volatile *)&D_001ED3C8))
struct Params {
    short field_0x0;
    short field_0x2;
    short field_0x4;
    short field_0x6;
};

extern struct Params D_001ED3D0;
extern int D_001ED3D8;
extern float D_00205060[4];

extern struct State *func_00136AE8(void);
extern void func_00128A50(unsigned char enable);
extern int func_00138468(int arg0, int arg1, int arg2, struct Params *arg3);
extern int func_00138CC8(int arg0, struct Params *arg1, int arg2);
extern void func_00138E58(int arg0, struct Params *arg1, int arg2);
extern void func_00139EB8(int arg0);
extern void func_00156BC8(unsigned short index, Vec4 *value);
extern void func_00157510(int arg0, int arg1, int arg2);
extern int func_00158868(unsigned short index, Vec4 *out);
extern void func_00158BB8(unsigned short index, int arg1);
extern int func_0015BBA0(int arg0, int arg1);
extern void func_0015C9E8(unsigned short arg0, unsigned short arg1, unsigned short arg2);
extern unsigned char func_0015CA60(unsigned short arg0, unsigned char arg1);
extern void func_0015D0E0(unsigned short index, unsigned short arg1, Vec4 *v);
extern void func_0015D758(unsigned short index, float value, int arg2);
extern void func_00172030(unsigned short arg0, int arg1, int arg2);
extern void func_00172168(int arg0, int arg1);
extern void func_00172918(unsigned short arg0, int arg1);
extern void func_001733A8(int arg0, int arg1);
extern int func_00173CB0(void);
extern void func_00179360(int arg0, int arg1, int arg2);

void func_001429A8(void) {
    Vec4 from;
    Vec4 to;
    struct State *st;
    float steps;
    int bit;
    int id;
    unsigned char handle;

    st = func_00136AE8();
    switch (D_001ED3C8->field_0x14) {
    case 0:
        st->flags |= 0x100;
        func_00158BB8(CTX->field_0x18, 1);
        func_0015D758(D_001ED3C8->field_0x18, 0.0f, 0);
        func_0015D758(D_001ED3C8->field_0x18, 0.1f, 1);
        D_001ED3D0.field_0x0 = 0;
        D_001ED3D0.field_0x2 = D_001ED3C8->field_0x18;
        D_001ED3D0.field_0x4 = 100;
        D_001ED3D0.field_0x6 = 20;
        func_00138468(0x40, 0, 1, &D_001ED3D0);
        id = func_00173CB0();
        D_001ED3C8->field_0x1a = id;
        if ((short)id == -1) {
            CTX->field_0x8 = 3;
            CTX->field_0x14 = 1;
        } else {
            func_00172030(CTX->field_0x1a, 0x400000, 1);
            func_00172168(0x800000, 1);
            D_001ED3C8->field_0x8 = 3;
            CTX->field_0x14 = 10;
        }
        break;

    case 1:
        func_00157510(0, 8, 0);
        D_001ED3D0.field_0x0 = 6;
        func_00138468(0x12, 8, 2, &D_001ED3D0);
        D_001ED3C8->field_0x14++;
        break;

    case 2:
        if (func_0015BBA0(0, 8) != 0) {
            break;
        }
        D_001ED3C8->field_0x1a = 0x3C;
        CTX->field_0x14++;
        break;

    case 3:
        if (D_001ED3C8->field_0x1a > 0) {
            D_001ED3C8->field_0x1a--;
        }
        if (D_001ED3C8->field_0x1a != 0) {
            break;
        }
        D_001ED3D0.field_0x0 = 0;
        D_001ED3D0.field_0x2 = D_001ED3C8->field_0x18;
        D_001ED3D0.field_0x4 = 10;
        D_001ED3D0.field_0x6 = 20;
        func_00138468(0x40, 0, 1, &D_001ED3D0);
        func_00157510(0, 8, 0x10);
        D_001ED3C8->field_0xc = 20;
        CTX->field_0x14++;
        break;

    case 4:
        if (func_0015BBA0(0, 8) == 0) {
            func_00158BB8(D_001ED3C8->field_0x18, 0);
            func_0015D758(D_001ED3C8->field_0x18, 0.0f, 0);
            func_0015D758(D_001ED3C8->field_0x18, 1.0f, 1);
            func_00157510(0, 10, 0x10);
            func_00179360(0x1000, 0x26, 0x7F);
            D_001ED3C8->field_0x14++;
        }
        if (D_001ED3C8->field_0xc == -1) {
            return;
        }
        D_001ED3C8->field_0xc--;
        if (D_001ED3C8->field_0xc != -1) {
            break;
        }
        func_00158BB8(CTX->field_0x18, 0);
        func_0015D758(D_001ED3C8->field_0x18, 0.0f, 0);
        func_0015D758(D_001ED3C8->field_0x18, 1.0f, 1);
        return;

    case 5:
        if (func_0015BBA0(0, 10) != 0) {
            return;
        }
        func_001733A8(0x4000, 0);
        bit = (int)(st->flags >> 27) & 1;
        if (bit == 1) {
            func_00128A50(0);
            st->flags = st->flags & ~0x08000000;
        }
        goto clear;

    case 10:
        func_00172918(D_001ED3C8->field_0x1a, 1);
        func_00157510(0, 8, 0);
        D_001ED3D0.field_0x0 = 6;
        func_00138468(0x12, 8, 2, &D_001ED3D0);
        func_00172168(0x800000, 0);
        D_001ED3C8->field_0x14++;
        break;

    case 11:
        if (func_0015BBA0(0, 8) != 0) {
            break;
        }
        func_0015D758(D_001ED3C8->field_0x18, 0.0f, 0);
        func_0015D758(D_001ED3C8->field_0x18, 1.0f, 1);
        func_001733A8(0x4000, 0);
        st->flags = st->flags & -0x101;
        goto restart;

    case 40:
        D_001ED3D0.field_0x0 = 0;
        D_001ED3D0.field_0x2 = D_001ED3C8->field_0x18;
        D_001ED3D0.field_0x4 = 10;
        D_001ED3D0.field_0x6 = 10;
        func_00138468(0x40, 0, 1, &D_001ED3D0);
        D_001ED3C8->field_0x1a = 10;
        CTX->field_0x14++;
        break;

    case 41:
        {
            unsigned short remaining;

            remaining = D_001ED3C8->field_0x1a;
            D_001ED3C8->field_0x1a = remaining - 1;
            if ((short)remaining > 0) {
                break;
            }
        }
        func_00158BB8(CTX->field_0x18, 0);
        func_0015D758(D_001ED3C8->field_0x18, 0.0f, 0);
        func_0015D758(D_001ED3C8->field_0x18, 1.0f, 1);
        func_001733A8(0x4000, 0);
        D_001ED3C8->field_0x14++;
        return;

    case 42:
        func_00158BB8(D_001ED3C8->field_0x18, 0);
        goto finish;

    case 43:
        func_00158BB8(D_001ED3C8->field_0x18, 0);
        func_0015D758(D_001ED3C8->field_0x18, 0.0f, 0);
        func_0015D758(D_001ED3C8->field_0x18, 1.0f, 1);
        func_001733A8(0x4000, 0);
        D_001ED3D0.field_0x2 = D_001ED3C8->field_0x18;
        func_00138E58(0x40, &D_001ED3D0, 2);
        func_00172030(D_001ED3C8->field_0x1a, 0x400000, 0);
        goto finish;

    case 50:
        func_0015D758(D_001ED3C8->field_0x18, 0.0f, 0);
        func_0015D758(D_001ED3C8->field_0x18, 0.1f, 1);
        D_001ED3D0.field_0x0 = 0;
        D_001ED3D0.field_0x2 = D_001ED3C8->field_0x18;
        D_001ED3D0.field_0x4 = 100;
        D_001ED3D0.field_0x6 = 20;
        func_00138468(0x40, 0, 1, &D_001ED3D0);
        D_001ED3C8->field_0x14++;
        break;

    case 51:
        {
            unsigned short remaining;

            remaining = D_001ED3C8->field_0x1a;
            D_001ED3C8->field_0x1a = remaining - 1;
            if ((short)remaining > 0) {
                break;
            }
        }
        CTX->field_0x14++;
        break;

    case 60:
        func_0015D758(D_001ED3C8->field_0x18, 0.0f, 0);
        func_0015D758(D_001ED3C8->field_0x18, 1.0f, 1);
        D_001ED3C8->field_0x1a = 20;
        CTX->field_0x14++;
        break;

    case 61:
        {
            unsigned short remaining;

            remaining = D_001ED3C8->field_0x1a;
            D_001ED3C8->field_0x1a = remaining - 1;
            if ((short)remaining > 0) {
                break;
            }
        }
        CTX->field_0x14++;
        break;

    case 52:
    case 62:
        func_00158BB8(D_001ED3C8->field_0x18, 0);
restart:
        func_00139EB8(D_001ED3D8);
        break;

    case 80:
        func_00157510(0, 8, 0);
        D_001ED3C8->field_0x14++;
        break;

    case 81:
        if (func_0015BBA0(0, 8) != 0) {
            break;
        }
        D_001ED3C8->field_0x14++;
        break;

    case 82:
        func_00158BB8(D_001ED3C8->field_0x18, 0);
        func_001733A8(0x4000, 0);
clear:
        st->flags = st->flags & -0x101;
finish:
        func_00139EB8(D_001ED3D8);
        return;

    case 90:
        func_00158868(D_001ED3C8->field_0x18, &from);
        func_00158BB8(D_001ED3C8->field_0x18, 1);
        handle = func_0015CA60(0, 1);
        func_0015C9E8(0, handle, D_001ED3C8->field_0x18);
        D_00205060[0] = 50.0f;
        D_00205060[1] = -10.0f;
        D_00205060[2] = 50.0f;
        D_00205060[3] = 1.0f;
        func_0015D0E0(D_001ED3C8->field_0x18, 0, (Vec4 *)D_00205060);
        func_00158868(D_001ED3C8->field_0x18, &to);
        D_001ED3D0.field_0x0 = D_001ED3C8->field_0x18;
        D_001ED3D0.field_0x2 = 0x10;
        steps = 16.0f;
        D_001ED3D0.field_0x4 = (to.x - from.x) * 100.0f / steps;
        D_001ED3D0.field_0x6 = (to.z - from.z) * 100.0f / steps;
        if (D_001ED3D0.field_0x4 != 0 || D_001ED3D0.field_0x6 != 0) {
            func_00138468(0x1E, 0, 1, &D_001ED3D0);
        }
        func_00156BC8(D_001ED3C8->field_0x18, &from);
        D_001ED3C8->field_0xc = 0x10;
        CTX->field_0x14++;
        return;

    case 91:
        D_001ED3D0.field_0x0 = D_001ED3C8->field_0x18;
        if (D_001ED3C8->field_0xc > 0) {
            D_001ED3C8->field_0xc--;
        }
        if (CTX->field_0xc != 0) {
            return;
        }
        if (func_00138CC8(0x1E, &D_001ED3D0, 1) != -1) {
            return;
        }
        D_001ED3C8->field_0x1a = 0;
        CTX->field_0x14 = 3;
        return;

    case 95:
        func_00157510(0, 8, 0);
        D_001ED3C8->field_0x14++;
        break;

    case 96:
        if (func_0015BBA0(0, 8) != 0) {
            break;
        }
        D_001ED3C8->field_0x14 = 0x5A;
        break;

    case 100:
        return;
    }

    func_00158BB8(D_001ED3C8->field_0x18, 1);
    handle = func_0015CA60(0, 1);
    func_0015C9E8(0, handle, D_001ED3C8->field_0x18);
    D_00205060[0] = 50.0f;
    D_00205060[1] = -10.0f;
    D_00205060[2] = 50.0f;
    D_00205060[3] = 1.0f;
    func_0015D0E0(D_001ED3C8->field_0x18, 0, (Vec4 *)D_00205060);
}
