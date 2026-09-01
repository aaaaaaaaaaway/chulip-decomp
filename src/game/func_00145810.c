struct Ctx {
    char pad_0x0[0x14];
    short field_0x14;
    unsigned short field_0x16;
};

extern struct Ctx *D_001ED3C8;
extern int D_001ED3D8;

extern int func_0015BBA0(unsigned short arg0, int arg1);
extern void func_00157510(unsigned short arg0, int arg1, int arg2);
extern int func_00161FE0(int arg0, int arg1);
extern void func_00139EB8(int arg0);

void func_00145810(void) {
    switch (D_001ED3C8->field_0x14) {
    case 0:
        func_00157510(D_001ED3C8->field_0x16, 0x1A, 0);
        D_001ED3C8->field_0x14 = D_001ED3C8->field_0x14 + 1;
        break;
    case 1:
        if (func_0015BBA0(D_001ED3C8->field_0x16, 0x1A) == 0 &&
            func_0015BBA0(D_001ED3C8->field_0x16, 0x1C) == 0) {
            func_00157510(D_001ED3C8->field_0x16, 0x1C, 1);
        }
        if (func_00161FE0(0, 1) != 0) {
            func_00157510(D_001ED3C8->field_0x16, 0x1B, 0);
            D_001ED3C8->field_0x14 = D_001ED3C8->field_0x14 + 1;
        }
        break;
    case 2:
        if (func_0015BBA0(D_001ED3C8->field_0x16, 0x1B) == 0) {
            func_00157510(D_001ED3C8->field_0x16, 1, 1);
            func_00139EB8(D_001ED3D8);
        }
        break;
    }
}
