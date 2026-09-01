struct DrawList_002D81B0 { int field_0x0; unsigned char *cursor; int field_0x8; int field_0xc; int field_0x10; };

extern struct DrawList_002D81B0 D_002D81B0;
extern int D_001EC950;

extern void func_00161590(unsigned char *p, int mode);
extern void func_00161460(unsigned char *p, int mode);
extern void func_001614E0(unsigned char *p, int a, int b);

void func_00131230(void) {
    unsigned char *p;

    p = D_002D81B0.cursor;
    D_001EC950 = (int)p;
    func_00161590(p, 2);
    func_00161460(p, 2);
    func_001614E0(p, 3, 2);
    p += 0x10;
    *(long *)p = 0x1000000000008001L;
    p += 8;
    *(long *)p = 0xE;
    p += 8;
    *(long *)p = 0x30000L;
    p += 8;
    *(long *)p = 0x47;
    p += 0x8;
    func_00161590(p, 0);
    p += 0x10;
    D_002D81B0.cursor = p;
}
