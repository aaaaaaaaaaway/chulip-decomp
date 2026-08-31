struct Actor_0012FCC0 {
    unsigned char pad_0x0[0x8];
    int field_0x8;
    unsigned char pad_0xc[0x46];
    unsigned char field_0x52;
};

extern struct Actor_0012FCC0 *func_00136AE8(void);

int func_0012FCC0(void) {
    struct Actor_0012FCC0 *actor = func_00136AE8();
    int result = 0;

    if (actor->field_0x8 >= 0x1C20 && actor->field_0x8 < 0x7788) {
        result = actor->field_0x52 != 0xFF;
    }
    return result;
}
