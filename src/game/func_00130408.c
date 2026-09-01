struct State_00130408 {
    long flags;
    unsigned char pad_0x8[0x39];
    unsigned char field_0x41;
};

struct DrawList_002D81C0 { int field_0x0; unsigned char *cursor; int field_0x8; int field_0xc; };

extern struct DrawList_002D81C0 D_002D81C0;
struct Counter_001ED348 { int value; };

extern struct Counter_001ED348 D_001ED348;

extern struct State_00130408 *func_00136AE8(void);
extern void func_0015CBB0(void);
extern void func_00130A68(void);
extern void func_0012FF28(void);
extern void func_001327E0(void);
extern void func_00130250(void);
extern void func_00198A20(int a);
extern void func_001612D8(struct DrawList_002D81C0 *list);
extern void func_00187280(int a, int b);
extern void func_0014BCD8(void);
extern void func_0014B5C8(void);
extern void func_0014BA20(void);
extern void func_00132958(void);
extern void func_0011E3B0(void);
extern void func_00113138(void);
extern void func_00132C20(void);
extern void func_00132DC0(void);
extern void func_00132E60(void);
extern void func_0015EC38(void);
extern int func_00173428(int a);
extern void func_00132010(void);
extern void func_00131F00(void);
extern void func_00132B10(void);

void func_00130408(void) {
    struct State_00130408 *state;
    int alternate;
    int locked;
    unsigned char mode;
    long flags;

    state = func_00136AE8();
    alternate = (int)((unsigned long)state->flags >> 36) & 1;
    func_0015CBB0();
    func_00130A68();
    D_001ED348.value = 0;
    flags = state->flags;
    if (((int)(flags >> 32) & 1) == 0) {
        locked = (int)(flags >> 5) & 1;
        if (locked == 1) {
            return;
        }
        func_0012FF28();
        func_001327E0();
        func_00130250();
        func_00198A20(0);
        func_001612D8(&D_002D81C0);
        func_00187280(0, 0);
        return;
    }
    mode = state->field_0x41;
    if ((mode == 1) || (mode == 3)) {
        func_0012FF28();
        if (state->field_0x41 == 1) {
            func_0014BCD8();
            func_0014B5C8();
        } else {
            func_0014BA20();
        }
        if (alternate != 0) {
            func_00132958();
        } else {
            func_001327E0();
        }
        func_00198A20(0);
        func_001612D8(&D_002D81C0);
        func_00187280(0, 0);
        func_0011E3B0();
        func_00113138();
        func_00130A68();
        func_00132C20();
        if (alternate == 0) {
            func_00132DC0();
        } else {
            func_00132E60();
        }
        func_00130250();
        func_00198A20(0);
        func_001612D8(&D_002D81C0);
        func_00187280(0, 0);
        func_0015EC38();
    } else if (mode == 4) {
        if ((func_00173428(0) & 2) == 0) {
            func_0014BCD8();
            func_0014B5C8();
        } else {
            func_0014BA20();
        }
        func_0012FF28();
        func_00132010();
        func_00131F00();
        func_0011E3B0();
        func_00113138();
        func_00130A68();
        func_00130250();
        func_00198A20(0);
        func_001612D8(&D_002D81C0);
        func_0015EC38();
    } else if (mode == 2) {
        func_0012FF28();
        func_00132B10();
        func_00198A20(0);
        func_001612D8(&D_002D81C0);
        func_0011E3B0();
        func_0015EC38();
        func_00113138();
        func_00130250();
        func_00130A68();
        func_00132C20();
    }
}
