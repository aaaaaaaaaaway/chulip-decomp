struct State_00139FA0 {
    unsigned char pad_0x0[8];
    unsigned int flags;
};

extern struct State_00139FA0 *func_00136AE8(void);
extern void func_00139348(void);

void func_00139FA0(void) {
    struct State_00139FA0 *state;

    state = func_00136AE8();
    if ((state->flags & 1) != 0) {
        if ((state->flags >= 7200.0f && state->flags < 13500.0f) ||
            (state->flags >= 28800.0f && state->flags < 34200.0f)) {
            func_00139348();
        }
    }
}
