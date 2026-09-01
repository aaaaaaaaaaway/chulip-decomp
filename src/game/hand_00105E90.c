/* Effect emitter unit 0x00105E90-0x00105F28.
 * D_001ED090 is an eight-byte object: the bundled Ps2EeAs expands its
 * small-data pseudo GP-relative in a branch delay slot and as the two
 * instruction absolute macro everywhere else, which is why retail shows
 * both addressing modes for one symbol inside one object.
 */
struct Ptr8 { char *pointer; char pad[4]; };
struct Int8 { int value; char pad[4]; };

extern struct Ptr8 D_001ED090;
extern int D_001ED094;
extern struct Int8 D_001ED098;

void func_00105F28();
int func_00112F40();
int func_00151CA8();

void func_00105E90(int arg0) {
    D_001ED098.value = arg0;
}

void func_00105E98(int index, int mode) {
    *(int *)(D_001ED090.pointer + index * 0x2B0 + 0x14) = 1;
    if (mode != 0) {
        if (mode == 1) {
            *(int *)(D_001ED090.pointer + index * 0x2B0 + 8) = mode;
        }
    } else {
        *(int *)(D_001ED090.pointer + index * 0x2B0 + 8) = -1;
    }
}

void func_00105EE8(void) {
    D_001ED098.value = 1;
    D_001ED094 = 0;
    func_00112F40(func_00105F28);
    func_00151CA8(D_001ED090.pointer);
    D_001ED090.pointer = 0;
}
