struct Actor {
    char pad_0x0[0x14];
    unsigned short counter;
};

struct ActorRef {
    struct Actor *actor;
    int pad_0x4;
};

extern struct ActorRef D_001ED3C8;
extern int D_001ED3D8;

extern long *func_00136AE8(void);
extern void func_00139EB8(int arg);

void func_00144028(void) {
    long *flags;
    unsigned short count;

    flags = func_00136AE8();
    count = D_001ED3C8.actor->counter;
    D_001ED3C8.actor->counter = count - 1;
    if ((short)count > 0) {
        *flags |= 1;
    } else {
        func_00139EB8(D_001ED3D8);
    }
}
