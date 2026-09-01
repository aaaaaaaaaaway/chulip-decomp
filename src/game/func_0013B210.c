struct Actor001ED3C8 {
    unsigned char pad_0x0[0xE];
    short field_0xE;
    unsigned char pad_0x10[4];
    union { short h; unsigned char b; } field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1A;
};

extern struct Actor001ED3C8 *D_001ED3C8;
extern int D_001ED3D8;

extern int func_00136B80(int id);
extern void func_00139EB8(int state);

extern float D_00205060[];

extern int func_00154508(unsigned short id);
extern void func_00158868(unsigned short id, float *out);
extern void func_00179470(short a, short b, float *buffer);
extern void func_00179660(short a, short b, float *buffer, short c);

void func_0013B210(void) {
    struct Actor001ED3C8 *actor;
    struct Actor001ED3C8 *target;
    int ready;

    if (func_00154508((unsigned short)D_001ED3C8->field_0x16) != 0) {
        actor = D_001ED3C8;
        func_00158868((unsigned short)actor->field_0x16, D_00205060);
        target = D_001ED3C8;
        if (target->field_0x18 == 0) {
            func_00179470(target->field_0x16, target->field_0x14.h, D_00205060);
            return;
        }
        func_00179660(target->field_0x16, target->field_0x14.h, D_00205060, target->field_0x1A);
    }
}
