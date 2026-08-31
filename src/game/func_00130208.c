struct Actor_00130208 {
    long field_0x0;
    unsigned char pad_0x8[0x2C];
    int field_0x34;
    int field_0x38;
};

extern struct Actor_00130208 *func_00136AE8(void);

void func_00130208(short arg0) {
    struct Actor_00130208 *actor = func_00136AE8();
    long flags = actor->field_0x0;

    actor->field_0x38 = arg0;
    actor->field_0x34 = 0;
    actor->field_0x0 = flags | 0x800000000L;
}
