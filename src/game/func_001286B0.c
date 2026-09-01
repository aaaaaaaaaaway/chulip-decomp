typedef struct {
    long unk00;
    unsigned char pad08[0x3E];
    unsigned char unk46;
    unsigned char unk47;
    unsigned char pad48[2];
    unsigned char unk4A;
    unsigned char unk4B;
} GameState;

extern GameState *func_00136AE8(void);
extern void func_0017CCF0(void);
extern void func_00178470(void);
extern void func_0017C908(int);
extern void func_0010BC88(void);
extern void func_001163B8(int, int);
extern void func_001172F0(int, int);
extern void func_0017E6C8(int, int);
extern void func_0017DBD0(int, int);
extern void func_0012E738(int);
extern void func_0012E630(int);
extern void func_00112F98(void);
extern void func_0015B578(int);
extern void func_0015A0A0(void);
extern void func_0014B5C0(void);
extern void func_0011EA40(void);
extern void func_0017EFE0(void);
extern void func_0017E5C0(void);
extern void func_00163A58(void);
extern void func_001639D8(void);
extern void func_00138070(void);
extern void func_0015E418(int);
extern void func_0011FAD8(int, int);
extern void func_00117538(void);
extern void func_00198A20(int);
extern void func_001159E0(void);
extern void func_00113388(void);
extern void func_00117568(void);

void func_001286B0(void) {
    GameState *state;

    state = func_00136AE8();
    func_0017CCF0();
    state->unk00 &= ~0x400000;
    func_00178470();
    func_0017C908(0x13);
    func_0017C908(0x11);
    func_0017C908(0x10);
    func_0010BC88();
    func_001163B8(0, 0);
    func_001172F0(0, 0);
    if (state->unk4A == 0x63) {
        func_0017E6C8(0x1B, 0x41);
        func_0017E6C8(0x1C, 0x41);
        func_0017E6C8(0x19, 0x41);
        func_0017E6C8(0x1A, 0x41);
        func_0017DBD0(0, 3);
        func_0017DBD0(0xA, 3);
        func_0017DBD0(9, 3);
        func_0017DBD0(5, 3);
    }
    func_0012E738(0);
    func_0012E630(0);
    func_00112F98();
    if (state->unk47 != 0xFF) {
        func_0015B578(state->unk47);
        state->unk47 = 0xFF;
        state->unk46 = 0xFF;
    }
    func_0015A0A0();
    func_0014B5C0();
    func_0011EA40();
    func_0017EFE0();
    func_0017E5C0();
    func_00163A58();
    func_001639D8();
    func_00138070();
    func_0015E418(1);
    func_0017E6C8(0xF, 0x41);
    func_0017E6C8(0x10, 0x41);
    func_0017E6C8(0xD, 0x41);
    func_0017E6C8(0xE, 0x41);
    func_0017E6C8(0x11, 0x41);
    func_0017E6C8(0x12, 0x41);
    func_0017E6C8(4, 0x41);
    func_0011FAD8(-1, -1);
    func_00117538();
    func_00198A20(0);
    if (state->unk4B == 0x63) {
        func_0017E6C8(0, 0x41);
        func_0017E6C8(0xA, 0x41);
        func_0017E6C8(9, 0x41);
        func_0017E6C8(5, 0x41);
        func_0017DBD0(0x1B, 3);
        func_0017DBD0(0x1C, 3);
        func_0017DBD0(0x19, 3);
        func_0017DBD0(0x1A, 3);
    }
    func_001159E0();
    func_00113388();
    func_00117568();
}
