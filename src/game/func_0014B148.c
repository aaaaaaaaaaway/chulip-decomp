struct Ctx {
    char pad_0x0[0x14];
    short field_0x14;
    short field_0x16;
};

struct CtxRef { struct Ctx *ptr; int pad; };

extern struct CtxRef D_001ED3C8;
extern int D_001ED3D8;

extern int func_0015A370(short arg0, int arg1);
extern void func_00139EB8(int arg0);

void func_0014B148(void) {
    int value;

    switch (D_001ED3C8.ptr->field_0x14) {
    case 0:
        D_001ED3C8.ptr->field_0x16 = 0;
        D_001ED3C8.ptr->field_0x14 = D_001ED3C8.ptr->field_0x14 + 1;
        break;
    case 1:
        value = func_0015A370(D_001ED3C8.ptr->field_0x16, 8);
        D_001ED3C8.ptr->field_0x16 = value;
        if ((short)value == 0) {
            func_00139EB8(D_001ED3D8);
        }
        break;
    }
}
