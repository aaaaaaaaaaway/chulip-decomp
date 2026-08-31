/* object_flags: -Wa,-G4 */
struct State_001ED240 { int field_0x0; int field_0x4; };
struct Slot_001ED248 { void *pointer; int unused; };

extern struct State_001ED240 D_001ED240;
extern struct Slot_001ED248 D_001ED248;

extern void func_00112F40(void (*callback)(void));
extern void func_00112EB0(void (*callback)(void), int arg1, int arg2);
extern void func_001205F8(void);

void func_00120560(int arg0, void *arg1) {
    func_00112F40(func_001205F8);
    func_00112EB0(func_001205F8, 0, 0);
    D_001ED240.field_0x0 = arg0;
    D_001ED248.pointer = arg1;
    D_001ED240.field_0x4 = 1;
}
