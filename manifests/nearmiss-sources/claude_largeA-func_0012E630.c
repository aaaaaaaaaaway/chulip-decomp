typedef struct {
    long unk00;
    unsigned char pad08[0x24];
    int unk2C;
    unsigned char pad30[0x11];
    unsigned char unk41;
    unsigned char pad42;
    unsigned char unk43;
    unsigned char pad44[3];
    unsigned char unk47;
    unsigned char pad48[4];
    unsigned char unk4C;
    unsigned char pad4D[3];
} GameState;

extern GameState *func_00136AE8(void);
extern void func_001734C0(int, int);
extern void func_0014B9A0(int, int);
extern void func_00158EB0(int);
extern void func_00105530(int, int);
extern void func_001733A8(int, int);
extern void func_00105878(int);

void func_0012E630(unsigned char mode) {
    GameState *state;

    state = func_00136AE8();
    if (state->unk41 == mode) {
        return;
    }
    state->unk43 = mode;
    switch (mode) {
    case 1:
        if (state->unk47 != 0xFF) {
            func_001734C0(6, -1);
            func_0014B9A0(state->unk47, 0);
        }
        func_00158EB0(0);
        func_00105530(state->unk4C, 0);
        func_001733A8(2, 0);
        state->unk00 &= ~0x20000;
        break;
    case 2:
        break;
    case 3:
        func_00105878(state->unk47);
        func_001733A8(2, 1);
        func_001734C0(6, state->unk47);
        state->unk00 &= ~0x20000;
        break;
    case 4:
        state->unk2C = 0;
        break;
    }
}
