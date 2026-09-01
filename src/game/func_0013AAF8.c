struct Actor001ED3C8 {
    unsigned char pad_0x0[0xE];
    short field_0xE;
    unsigned char pad_0x10[4];
    union { short h; unsigned short uh; unsigned char b; } field_0x14;
    short field_0x16;
    short field_0x18;
    short field_0x1A;
};

struct ActorSlot001ED3C8 {
    struct Actor001ED3C8 *actor;
    int field_0x4;
};

extern struct ActorSlot001ED3C8 D_001ED3C8;
extern int D_001ED3D8;

extern int func_00136B80(int id);
extern void func_00139EB8(int state);

struct Slot00205070 { float f0; float f1; float f2; float f3; };
extern struct Slot00205070 D_00205070[];

extern void func_00101A68(struct Slot00205070 *p);
extern void func_00103B38(void);
extern void func_001392C0(int id);

void func_0013AAF8(void) {
    struct Actor001ED3C8 *actor;
    struct Actor001ED3C8 *target;
    unsigned short remaining;

    if (func_00136B80(0xF) != 0) {
        return;
    }
    actor = D_001ED3C8.actor;
    remaining = actor->field_0x1A;
    if ((remaining & 0x4000) != 0) {
        actor->field_0x1A = remaining & 0xBFFF;
        D_001ED3C8.actor->field_0xE = 1;
        return;
    }
    actor->field_0x1A = remaining - 1;
    if ((short)remaining > 0) {
        target = D_001ED3C8.actor;
        func_00101A68(D_00205070 + target->field_0x14.h);
        return;
    }
    if (D_001ED3C8.actor->field_0x16 != 0) {
        func_00103B38();
    }
    func_001392C0(D_001ED3C8.actor->field_0x14.b);
    func_00139EB8(D_001ED3D8);
}
