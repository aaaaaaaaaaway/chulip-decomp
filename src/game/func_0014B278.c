struct Ctx {
    char pad_0x0[0x14];
    short field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1a;
};

struct CtxRef { struct Ctx *ptr; int pad; };

struct Params { short field_0x0; short field_0x2; short field_0x4; short field_0x6; };

extern struct CtxRef D_001ED3C8;
extern struct Params D_001ED3D0;
extern char D_00205210[];
extern char D_00205310[];
extern char D_001E9568[];
extern char D_001E95A0[];
extern char D_001E95D8[];

extern void func_0015ED68(int arg0, int arg1, int arg2);
extern int func_001923F4(char *dst, int fill, int size);
extern void func_00192660();
extern void func_001735A8(char *arg0, char *arg1);
extern unsigned int func_00192A54(char *arg0);
extern int func_00138468(int arg0, int arg1, int arg2, struct Params *arg3);

void func_0014B278(void) {
    unsigned int width;

    switch (D_001ED3C8.ptr->field_0x14) {
    case 0:
        func_0015ED68(0x80, 0x80, 0x80);
        func_001923F4(D_00205310, 0, 0x100);
        if (D_001ED3C8.ptr->field_0x1a != 0) {
            func_00192660(D_00205310, D_001E9568, D_001ED3C8.ptr->field_0x16);
        } else {
            func_00192660(D_00205310, D_001E95A0, D_001ED3C8.ptr->field_0x16);
        }
        func_001735A8(D_00205310, D_00205210);
        width = func_00192A54(D_00205210);
        D_001ED3D0.field_0x2 = 2;
        D_001ED3D0.field_0x6 = (0x2D - width) / 2;
        D_001ED3D0.field_0x4 = 0xD2;
        D_001ED3D0.field_0x0 = 0;
        func_00138468(0x30, 0, 1, &D_001ED3D0);
        D_001ED3C8.ptr->field_0x14 = D_001ED3C8.ptr->field_0x14 + 1;
        break;
    case 1:
        break;
    case 10:
        func_0015ED68(0x80, 0x80, 0x80);
        func_001923F4(D_00205310, 0, 0x100);
        func_00192660(D_00205310, D_001E95D8, D_001ED3C8.ptr->field_0x16);
        func_001735A8(D_00205310, D_00205210);
        width = func_00192A54(D_00205210);
        D_001ED3D0.field_0x2 = 2;
        D_001ED3D0.field_0x6 = (0x2D - width) / 2;
        D_001ED3D0.field_0x4 = 0xD2;
        D_001ED3D0.field_0x0 = 0;
        func_00138468(0x30, 0, 1, &D_001ED3D0);
        D_001ED3C8.ptr->field_0x14 = D_001ED3C8.ptr->field_0x14 + 1;
        break;
    }
}
