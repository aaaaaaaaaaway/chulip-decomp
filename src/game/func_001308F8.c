struct DrawList_002D81B0 {
    int field_0x0;
    unsigned char *cursor;
    int field_0x8;
    int field_0xc;
    int field_0x10;
};
struct DrawList_002D81C0 {
    int field_0x0;
    unsigned char *cursor;
    int field_0x8;
    int field_0xc;
};

extern struct DrawList_002D81B0 D_002D81B0;
extern struct DrawList_002D81C0 D_002D81C0;

extern int func_001916A8(int a, int b);
extern void *func_001923F4(unsigned char *p, int a, int b);
extern void func_00198A20(int a);

void func_001308F8(void) {
    int a;
    int b;

    D_002D81C0.field_0x8 = 0x1C0;
    a = func_001916A8(0x80, 0x1C00);
    a = (a & 0xFFFFFFF) | 0x20000000;
    D_002D81C0.field_0x0 = a;
    D_002D81C0.cursor = (unsigned char *)a;
    D_002D81B0.field_0x8 = 0x194B0;
    b = func_001916A8(0x80, 0x194B00);
    b = b & 0xFFFFFFF;
    D_002D81B0.field_0x0 = b | 0x20000000;
    D_002D81B0.cursor = (unsigned char *)(b | 0x20000000);
    func_001923F4(D_002D81C0.cursor, 0, D_002D81C0.field_0x8);
    func_001923F4(D_002D81B0.cursor, 0, D_002D81B0.field_0x8);
    func_00198A20(0);
}
