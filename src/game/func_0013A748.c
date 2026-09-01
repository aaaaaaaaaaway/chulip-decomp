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

extern float D_00205060[];

extern void func_00101AD0(const float *value);

void func_0013A748(void) {
    struct Actor001ED3C8 *actor;
    struct Actor001ED3C8 *target;
    unsigned short remaining;

    if (func_00136B80(0xF) != 0) {
        return;
    }
    actor = D_001ED3C8;
    remaining = actor->field_0x1A;
    actor->field_0x1A = remaining - 1;
    if ((short)remaining > 0) {
        target = D_001ED3C8;
        D_00205060[0] = (float)target->field_0x14.h / 1000.0f;
        D_00205060[2] = (float)target->field_0x18 / 1000.0f;
        D_00205060[1] = (float)target->field_0x16 / 1000.0f;
        func_00101AD0(D_00205060);
        return;
    }
    func_00139EB8(D_001ED3D8);
}
