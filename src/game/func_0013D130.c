struct Actor_0013D130 {
    unsigned char pad_0x0[0x14];
    short field_0x14;
    unsigned short field_0x16;
    unsigned char pad_0x18[2];
    short field_0x1a;
};

struct State_0013D130 {
    long flags;
};

struct ActorSlot_0013D130 {
    struct Actor_0013D130 *actor;
    int field_0x4;
};

extern struct ActorSlot_0013D130 D_001ED3C8;
extern int D_001ED3D8;

extern struct State_0013D130 *func_00136AE8(void);
extern void func_00157510(int a, int b, int c);
extern void func_00179360(int a, int b, int c);
extern void func_001722B0(void);
extern void func_00172168(int a, int b);
extern void func_001723A0(void);
extern int func_0015BBA0(int a, int b);
extern void func_00139EB8(int a);

void func_0013D130(void) {
    struct State_0013D130 *state;
    struct Actor_0013D130 *actor;
    unsigned short remaining;
    long flags;
    int next;

    state = func_00136AE8();
    actor = D_001ED3C8.actor;
    switch (actor->field_0x14) {
    case 0:
        func_00157510(0, 6, ((int)(state->flags >> 20) & 1) << 7);
        func_00179360(0x1000, 0, 0x7F);
        func_001722B0();
        func_00172168(0x1000000, 1);
        D_001ED3C8.actor->field_0x14 = 1;
        D_001ED3C8.actor->field_0x16 = 0;
        D_001ED3C8.actor->field_0x1a = 0;
        return;
    case 1:
        next = actor->field_0x16 + 1;
        actor->field_0x16 = next;
        if ((short)next == 0x1F) {
            func_001723A0();
        }
        if (func_0015BBA0(0, 6) != 0) {
            remaining = D_001ED3C8.actor->field_0x16;
            D_001ED3C8.actor->field_0x16 = remaining + 1;
            if ((short)remaining < 0x78) {
                return;
            }
        }
        func_001723A0();
        func_00172168(0x1000000, 0);
        flags = state->flags & -0x101;
        state->flags = flags;
        if (((int)(flags >> 7) & 1) == 0) {
            func_00157510(0, 1, 0x81);
        }
        func_00139EB8(D_001ED3D8);
        return;
    }
}
