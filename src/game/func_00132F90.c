struct DrawList_002D81B0 { int field_0x0; unsigned char *cursor; int field_0x8; int field_0xc; int field_0x10; };

extern struct DrawList_002D81B0 D_002D81B0;

extern void func_00161590(unsigned char *p, int mode);
extern void func_00161460(unsigned char *p, int mode);
extern void func_001614E0(unsigned char *p, int a, int b);
extern void func_00161328(unsigned char *p, long *tag);
extern void func_00161338(unsigned char *p, int a, int b, int c, int d);

unsigned char *func_00132F90(int arg0) {
    long tag[2];
    unsigned char *p;

    p = D_002D81B0.cursor;
    tag[0] = 0x1000000000008001L;
    tag[1] = 0xE;
    func_00161590(p, 2);
    func_00161460(p, 2);
    func_001614E0(p, 3, 2);
    func_00161328(p + 0x10, tag);
    func_00161338(p + 0x20, 0, 0x1A, 0, arg0);
    D_002D81B0.cursor = p + 0x30;
    return p;
}
