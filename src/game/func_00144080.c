struct Ctx {
    char pad_0x0[0xE];
    unsigned short field_0xe;
    char pad_0x10[0x4];
    short field_0x14;
    unsigned short field_0x16;
    short field_0x18;
    short field_0x1a;
};

struct CtxRef { struct Ctx *ptr; int pad; };

extern struct CtxRef D_001ED3C8;
extern int D_001ED3D8;

extern void func_00158D18(unsigned short arg0, unsigned char arg1, int arg2);
extern void func_00139EB8(int arg0);

void func_00144080(void) {
    if (D_001ED3C8.ptr->field_0x14-- > 0) {
        D_001ED3C8.ptr->field_0x18 = D_001ED3C8.ptr->field_0x18 + D_001ED3C8.ptr->field_0x1a;
        func_00158D18(D_001ED3C8.ptr->field_0x16, D_001ED3C8.ptr->field_0x18 / 128, 1);
    } else {
        func_00139EB8(D_001ED3D8);
    }
}
