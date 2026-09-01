struct Actor001ED3C8 {
    unsigned char pad_0x0[0xE];
    short field_0xE;
    unsigned char pad_0x10[4];
    short field_0x14;
    unsigned short field_0x16;
    unsigned short field_0x18;
};

extern struct Actor001ED3C8 *volatile D_001ED3C8;
extern int D_001ED3D8;

extern int func_00136B80(int id);
extern void func_001016A0(float value);
extern void func_00139EB8(int state);

void func_0013A9B8(void) {
    struct Actor001ED3C8 *actor;
    unsigned short remaining;

    if (func_00136B80(0xF) != 0) {
        return;
    }
    actor = D_001ED3C8;
    remaining = actor->field_0x16;
    actor->field_0x16 = remaining - 1;
    if ((short)remaining > 0) {
        func_001016A0((float)D_001ED3C8->field_0x14 / 1000.0f);
        return;
    }
    func_00139EB8(D_001ED3D8);
}
