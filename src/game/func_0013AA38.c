typedef union {
    short h;
    unsigned short uh;
    unsigned char b;
} ActorHalf;

struct Actor001ED3C8 {
    unsigned char pad_0x0[0xE];
    short field_0xE;
    unsigned char pad_0x10[4];
    ActorHalf field_0x14;
    ActorHalf field_0x16;
    ActorHalf field_0x18;
    ActorHalf field_0x1A;
};

extern int D_001ED3D8;

extern int func_00136B80(int id);
extern void func_00139EB8(int state);
struct ActorSlot001ED3C8 {
    struct Actor001ED3C8 *actor;
    int field_0x4;
};

extern struct ActorSlot001ED3C8 D_001ED3C8;

extern float D_00205060[];

extern void func_00101A00(float *p);
extern void func_00138C80(int id);

void func_0013AA38(void) {
    struct Actor001ED3C8 *actor;
    struct Actor001ED3C8 *target;
    int remaining;

    if (func_00136B80(0xF) != 0) {
        return;
    }
    actor = D_001ED3C8.actor;
    remaining = actor->field_0x1A.uh - 1;
    actor->field_0x1A.uh = remaining;
    if ((short)remaining > 0) {
        target = D_001ED3C8.actor;
        D_00205060[0] = (float)target->field_0x14.h / 10.0f;
        D_00205060[2] = (float)target->field_0x18.h / 10.0f;
        D_00205060[1] = (float)target->field_0x16.h / 10.0f;
        func_00101A00(D_00205060);
        return;
    }
    func_00138C80(0xF);
    func_00139EB8(D_001ED3D8);
}
