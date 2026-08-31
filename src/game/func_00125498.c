/* object_flags: -Wa,-G4 */
struct Slot_001ED264 { void *pointer; int unused; };

extern struct Slot_001ED264 D_001ED264;

extern void *func_00151A00(int size);
extern void func_00112F40(void (*callback)(void));
extern void func_00112EB0(void (*callback)(void), int arg1, int arg2);
extern void func_00125618(void);

void func_00125498(int count) {
    D_001ED264.pointer = func_00151A00(count * 0x40);
    func_00112F40(func_00125618);
    func_00112EB0(func_00125618, count, 0);
}
