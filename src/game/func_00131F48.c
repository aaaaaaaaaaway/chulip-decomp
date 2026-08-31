struct DrawList_002D81C0 { int field_0x0; unsigned char *cursor; int field_0x8; int field_0xc; };

struct Request_00131F48 { unsigned char pad_0x0[0xC]; int field_0xc; };

extern struct DrawList_002D81C0 D_002D81C0;

extern void func_00161298(unsigned char *dst, int value);

void func_00131F48(struct Request_00131F48 *request) {
    func_00161298(D_002D81C0.cursor, request->field_0xc);
    D_002D81C0.cursor = D_002D81C0.cursor + 0x10;
}
