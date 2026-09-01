struct Actor001ED3C8 {
    unsigned char pad_0x0[0xE];
    short field_0xE;
    unsigned char pad_0x10[4];
    union { short h; unsigned char b; } field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1A;
};

extern struct Actor001ED3C8 *volatile D_001ED3C8;
extern int D_001ED3D8;

extern int func_00136B80(int id);
extern void func_00139EB8(int state);

extern void func_001016A0(float value);
extern void func_00101748(float value);

void func_0013A888(void) {
    struct Actor001ED3C8 *actor;
    unsigned short remaining;

    if (func_00136B80(0xF) != 0) {
        return;
    }
    actor = D_001ED3C8;
    remaining = actor->field_0x18;
    actor->field_0x18 = remaining - 1;
    if ((short)remaining > 0) {
        func_001016A0((float)D_001ED3C8->field_0x14.h / 1000.0f);
        func_00101748((float)D_001ED3C8->field_0x16 / 1000.0f);
        return;
    }
    func_00139EB8(D_001ED3D8);
}
