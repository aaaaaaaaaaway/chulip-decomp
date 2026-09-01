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

struct Vec4_00205070 { float x; float y; float z; float w; };

extern struct Vec4_00205070 D_00205070[];

extern void func_00101748(float value);
extern void func_001392C0(unsigned char id);

void func_0013A930(void) {
    struct Actor001ED3C8 *actor;
    unsigned short remaining;

    if (func_00136B80(0xF) != 0) {
        return;
    }
    actor = D_001ED3C8;
    remaining = actor->field_0x16;
    actor->field_0x16 = remaining - 1;
    if ((short)remaining > 0) {
        func_00101748((D_00205070 + D_001ED3C8->field_0x14.h)->y);
        return;
    }
    func_001392C0(D_001ED3C8->field_0x14.b);
    func_00139EB8(D_001ED3D8);
}
