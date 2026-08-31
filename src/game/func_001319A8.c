struct DrawList_002D81C0 { int field_0x0; unsigned char *cursor; int field_0x8; int field_0xc; };

extern struct DrawList_002D81C0 D_002D81C0;
extern int D_001EC96C;

extern void func_00161298(unsigned char *dst, int value);

void func_001319A8(void) {
    func_00161298(D_002D81C0.cursor, D_001EC96C);
    D_002D81C0.cursor = D_002D81C0.cursor + 0x10;
}
