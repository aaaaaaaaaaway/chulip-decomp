/* Effect emitter unit 0x00106DB0-0x00106E48, the D_001ED0A8 pointer block.
 * Same eight-byte-object model as 0x00105E90.
 */
struct Ptr8 { char *pointer; char pad[4]; };
struct Int8 { int value; char pad[4]; };

extern struct Ptr8 D_001ED0A8;
extern int D_001ED0AC;
extern struct Int8 D_001ED0B0;

void func_00106E48();
int func_00112F40();
int func_00151CA8();

void func_00106DB0(int arg0) {
    D_001ED0B0.value = arg0;
}

void func_00106DB8(int index, int mode) {
    *(int *)(D_001ED0A8.pointer + index * 0x1940 + 8) = 1;
    if (mode != 0) {
        if (mode == 1) {
            *(int *)(D_001ED0A8.pointer + index * 0x1940 + 0x10) = mode;
        }
    } else {
        *(int *)(D_001ED0A8.pointer + index * 0x1940 + 0x10) = -1;
    }
}

void func_00106E08(void) {
    D_001ED0B0.value = 1;
    D_001ED0AC = 0;
    func_00112F40(func_00106E48);
    func_00151CA8(D_001ED0A8.pointer);
    D_001ED0A8.pointer = 0;
}
