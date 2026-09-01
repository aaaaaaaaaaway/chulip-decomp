struct Ctx {
    char pad_0x0[0x14];
    short field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1a;
};

struct CtxRef { struct Ctx *ptr; int pad; };

extern struct CtxRef D_001ED3C8;
extern char D_00205060[];

extern int func_0017C450(int arg0, int arg1);
extern int func_0015BBA0(unsigned short arg0, short arg1);
extern int func_00158868(unsigned short arg0, char *arg1);
extern void func_00179470(int arg0, int arg1, char *arg2);
extern void func_00179360(int arg0, int arg1, int arg2);

void func_0014A950(void) {
    if (func_0017C450(0, 0) != 0) {
        if (func_0015BBA0(D_001ED3C8.ptr->field_0x16, D_001ED3C8.ptr->field_0x18) != 0) {
            if (D_001ED3C8.ptr->field_0x1a != 0) {
                func_00158868(D_001ED3C8.ptr->field_0x16, D_00205060);
                func_00179470(D_001ED3C8.ptr->field_0x16 + 0x10, D_001ED3C8.ptr->field_0x14, D_00205060);
            } else {
                func_00179360(0x1000, D_001ED3C8.ptr->field_0x14, 0x7F);
            }
        }
    }
}
