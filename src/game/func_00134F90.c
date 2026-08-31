/* object_flags: -Wa,-G4 */
struct Pair_001ED368 { int field_0x0; int field_0x4; };

extern int D_001ED364;
extern struct Pair_001ED368 D_001ED368;

extern void func_00112F40(void (*callback)(void));
extern void func_00112EB0(void (*callback)(void), int arg1, int arg2);
extern void func_001352A0(void);
extern void func_00134E68(void);
extern void func_00135440(void);
extern void func_001357C8(void);
extern void func_00135020(void);

void func_00134F90(void) {
    D_001ED364 = 0;
    D_001ED368.field_0x0 = -1;
    D_001ED368.field_0x4 = -1;
    func_00112F40(func_00135440);
    func_00112F40(func_001357C8);
    func_001352A0();
    func_00134E68();
    func_00112F40(func_00135020);
    func_00112EB0(func_00135020, 0, 0);
}
