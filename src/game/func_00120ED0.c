/* object_flags: -Wa,-G4 */
struct Slot_001ED250 { int *pointer; int unused; };

extern struct Slot_001ED250 D_001ED250;

extern void func_00120F20(void);
extern void func_00120C68(void);

void func_00120ED0(int mode) {
    if (mode == -1) {
    } else if (mode == 1) {
        func_00120F20();
        func_00120C68();
    }
    D_001ED250.pointer[1] = mode;
}
