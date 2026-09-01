struct Actor001ED3C8 {
    unsigned char pad_0x0[0x14];
    union { short h; unsigned char b; } field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1A;
};

extern struct Actor001ED3C8 *volatile D_001ED3C8;
extern int D_001ED3D8;

extern int func_00136B80(int id);
extern void func_00139EB8(int state);

extern void func_00101748(float x);
extern void func_00101AF8(void);

void func_0013A800(void) {
    struct Actor001ED3C8 *actor;
    unsigned short remaining;

    if (func_00136B80(0xF) != 0) {
        return;
    }
    actor = D_001ED3C8;
    remaining = actor->field_0x16;
    actor->field_0x16 = remaining - 1;
    if ((short)remaining > 0) {
        func_00101748((float)D_001ED3C8->field_0x14.h / 1000.0f);
        func_00101AF8();
        return;
    }
    func_00139EB8(D_001ED3D8);
}
