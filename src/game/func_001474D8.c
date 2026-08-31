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

extern void func_00157510(int arg0, int arg1, int arg2);
extern int func_0015BBA0(int arg0, int arg1);
extern void func_00172030(int arg0, int arg1, int arg2);
extern void func_00172270(int arg0);
extern void func_00139EB8(int arg0);

void func_001474D8(void) {
    if (D_001ED3C8.ptr->field_0x14 != 0) {
        D_001ED3C8.ptr->field_0xe = D_001ED3C8.ptr->field_0x14;
        D_001ED3C8.ptr->field_0x14 = 0;
        func_00157510(0, 0x24, 0x10);
    } else if (func_0015BBA0(0, 0x24) == 0) {
        if (D_001ED3C8.ptr->field_0x1a == 1) {
            func_00172030(0, 0x200, 0);
            func_00172270(0);
        }
        func_00139EB8(D_001ED3D8);
    }
}
