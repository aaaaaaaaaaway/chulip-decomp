struct Ctx {
    char pad_0x0[0x14];
    short field_0x14;
    unsigned short field_0x16;
    short field_0x18;
    short field_0x1a;
};

struct CtxRef { struct Ctx *ptr; int pad; };

extern struct CtxRef D_001ED3C8;

extern int D_001ED3D8;
extern char D_00205060[];

extern int func_00172DD8(unsigned short arg0, int arg1);
extern void func_00172CC8(unsigned short arg0, int arg1, int arg2);
extern int func_00170ED0(unsigned short arg0);
extern int func_00158868(int arg0, char *arg1);
extern void func_00173DB0(unsigned short arg0, char *arg1);
extern int func_0015BBA0(int arg0, int arg1);
extern void func_00157510(int arg0, int arg1, int arg2);
extern void func_00139EB8(int arg0);

void func_0014A818(void) {
    int amount;

    switch (D_001ED3C8.ptr->field_0x14) {
    case 0:
        amount = (func_00172DD8(D_001ED3C8.ptr->field_0x16, 0x1A) * 100 +
                  D_001ED3C8.ptr->field_0x18) / 100;
        func_00172CC8(D_001ED3C8.ptr->field_0x16, 0x1A, amount);
        if (D_001ED3C8.ptr->field_0x1a-- <= 0) {
            D_001ED3C8.ptr->field_0x14 = 100;
        }
        if (func_00170ED0(D_001ED3C8.ptr->field_0x16) != 0) {
            func_00158868(0, D_00205060);
            func_00173DB0(D_001ED3C8.ptr->field_0x16, D_00205060);
        }
        break;
    case 10:
        if (func_0015BBA0(0, 6) == 0) {
            func_00157510(0, 1, 0x81);
            D_001ED3C8.ptr->field_0x14 = 100;
        }
        break;
    case 100:
        func_00139EB8(D_001ED3D8);
        break;
    }
}
