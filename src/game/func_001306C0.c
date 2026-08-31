struct Actor_001306C0 { unsigned char pad_0x0[0x41]; unsigned char field_0x41; };

struct DrawList_002D81C0 { int field_0x0; unsigned char *cursor; int field_0x8; int field_0xc; };

extern struct DrawList_002D81C0 D_002D81C0;

extern struct Actor_001306C0 *func_00136AE8(void);
extern void func_00130A68(void);
extern void func_0011E3B0(void);
extern void func_0014B5C8(void);
extern void func_001327E0(void);
extern void func_00198A20(int arg0);
extern void func_001612D8(struct DrawList_002D81C0 *list);
extern void func_0015EC38(void);
extern void func_00113138(void);

void func_001306C0(void) {
    struct Actor_001306C0 *actor = func_00136AE8();

    func_00130A68();
    func_0011E3B0();
    if (actor->field_0x41 == 1) {
        func_0014B5C8();
    }
    func_001327E0();
    func_00198A20(0);
    func_001612D8(&D_002D81C0);
    func_0015EC38();
    func_00113138();
}
