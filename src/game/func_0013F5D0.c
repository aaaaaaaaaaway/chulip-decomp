struct Ctx_0013F5D0 {
    unsigned char pad_0x0[0x14];
    unsigned short field_0x14;
    unsigned short field_0x16;
};

extern struct Ctx_0013F5D0 *D_001ED3C8;
extern int D_001ED3D8;

extern int func_00136B80(int arg0);
extern int func_0017EAD0(unsigned short arg0, unsigned short arg1);
extern void func_00139EB8(int arg0);

void func_0013F5D0(void) {
    if (func_00136B80(0x1A) != 0) {
        func_00139EB8(D_001ED3D8);
        return;
    }
    if (func_0017EAD0(D_001ED3C8->field_0x14, D_001ED3C8->field_0x16) == -1) {
        func_00139EB8(D_001ED3D8);
    }
}
