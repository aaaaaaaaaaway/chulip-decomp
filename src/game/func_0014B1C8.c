struct Ctx {
    char pad_0x0[0x14];
    short field_0x14;
    unsigned short field_0x16;
    unsigned short field_0x18;
};

struct CtxRef { struct Ctx *ptr; int pad; };

extern struct CtxRef D_001ED3C8;
extern char D_00205060[];

extern void func_00158868(unsigned short arg0, char *arg1);
extern float func_00154720(int arg0);
extern void func_00156B00(unsigned short arg0, float arg1, int arg2);
extern void func_00172C38(unsigned short arg0, char *arg1);
extern int func_00154398(unsigned short arg0);
extern void func_00158BB8(unsigned short arg0, int arg1);

void func_0014B1C8(void) {
    float value;

    if (D_001ED3C8.ptr->field_0x14 == 0) {
        func_00158868(0, D_00205060);
        value = func_00154720(0);
        func_00156B00(D_001ED3C8.ptr->field_0x16, value, 1);
        func_00172C38(D_001ED3C8.ptr->field_0x16, D_00205060);
        if (func_00154398(D_001ED3C8.ptr->field_0x18) != 0) {
            func_00158BB8(D_001ED3C8.ptr->field_0x16, 1);
        } else {
            func_00158BB8(D_001ED3C8.ptr->field_0x16, 0);
        }
    }
}
