struct Actor {
    char pad_0x0[0x14];
    unsigned short field_0x14;
    unsigned short field_0x16;
    short field_0x18;
};

struct ActorRef {
    struct Actor *actor;
    int pad_0x4;
};

extern struct ActorRef D_001ED3C8;

extern long *func_00136AE8(void);

void func_0014AB28(void) {
    long *flags;
    struct Actor *actor;
    unsigned short timer;

    flags = func_00136AE8();
    actor = D_001ED3C8.actor;
    switch ((short)actor->field_0x14) {
    case 0:
        if (actor->field_0x18 != 0) {
            *flags &= ~(1L << 35);
        } else {
            *flags |= 1L << 35;
        }
        D_001ED3C8.actor->field_0x14 = D_001ED3C8.actor->field_0x14 + 1;
        break;
    case 1:
        timer = actor->field_0x16;
        actor->field_0x16 = timer - 1;
        if ((short)timer <= 0) {
            if (D_001ED3C8.actor->field_0x18 != 0) {
                *flags |= 1L << 35;
            } else {
                *flags &= ~(1L << 35);
            }
        }
        break;
    }
}
