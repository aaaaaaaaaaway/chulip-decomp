typedef union { short h; unsigned short uh; unsigned char b; } ActorHalf;

struct Actor001ED3C8 {
    unsigned char pad_0x0[0xE];
    short field_0xE;
    unsigned char pad_0x10[4];
    ActorHalf field_0x14;
    ActorHalf field_0x16;
    ActorHalf field_0x18;
    ActorHalf field_0x1A;
};

struct ActorSlot001ED3C8 {
    struct Actor001ED3C8 *actor;
    int field_0x4;
};

extern struct ActorSlot001ED3C8 D_001ED3C8;
extern int D_001ED3D8;
extern float D_00205060[];

extern int func_00138CC8(int id, short *buf, int count);
extern void func_00155FE0(unsigned short id, float *p);
extern void func_00139EB8(int state);

void func_0013F4E0(void) {
    short local[8];
    unsigned short remaining;

    D_00205060[0] = 0.0f;
    D_00205060[1] = (float)D_001ED3C8.actor->field_0x18.h / 100.0f;
    D_00205060[2] = 0.0f;
    local[1] = D_001ED3C8.actor->field_0x16.h;
    if (func_00138CC8(0x3D, local, 2) != -1) {
        func_00139EB8(D_001ED3D8);
        return;
    }
    remaining = D_001ED3C8.actor->field_0x14.uh;
    D_001ED3C8.actor->field_0x14.uh = remaining - 1;
    if ((short)remaining > 0) {
        func_00155FE0(D_001ED3C8.actor->field_0x16.uh, D_00205060);
        return;
    }
    func_00139EB8(D_001ED3D8);
}
