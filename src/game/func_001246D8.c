/* object_flags: -Wa,-G4 */
struct Slot_001ED268 { void *pointer; int unused; };

extern struct Slot_001ED268 D_001ED268;

extern void *func_00151A00(int size);
extern void func_00112F40(void (*callback)(void));
extern void func_00112EB0(void (*callback)(void), int arg1, int arg2);
extern void func_00124AF8(void);

void func_001246D8(void) {
    D_001ED268.pointer = func_00151A00(0x480);
    func_00112F40(func_00124AF8);
    func_00112EB0(func_00124AF8, 0, 0);
}
