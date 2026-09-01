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

extern void func_00101928(float x, float y);
extern void func_00101AF8(void);
extern void func_00103B38(void);

void func_0013A6A0(void) {
    struct Actor001ED3C8 *actor;
    struct Actor001ED3C8 *target;
    unsigned short remaining;

    actor = D_001ED3C8;
    remaining = actor->field_0x18;
    actor->field_0x18 = remaining - 1;
    if ((short)remaining > 0) {
        target = D_001ED3C8;
        func_00101928((float)target->field_0x14.h / 100.0f, (float)target->field_0x16 / 100.0f);
        func_00101AF8();
        return;
    }
    if (D_001ED3C8->field_0x1A != 0) {
        func_00103B38();
    }
    func_00139EB8(D_001ED3D8);
}
