struct DrawList_002D81B0 {
    int field_0x0;
    unsigned char *cursor;
    int field_0x8;
    int field_0xc;
    int field_0x10;
};

extern struct DrawList_002D81B0 D_002D81B0;
extern int D_001EC958;
/* Provisional single-source provider; original TU boundaries are unproved. */
unsigned char *D_001EC95C __attribute__((section(".sdata"))) = 0;

extern void func_00161590(unsigned char *p, int mode);
extern void func_00161460(unsigned char *p, int mode);
extern void func_001614E0(unsigned char *p, int a, int b);

void func_00130E68(void) {
    unsigned char *p;

    p = D_002D81B0.cursor;
    D_001EC958 = (int)p;
    func_00161590(p, 2);
    func_00161460(p, 2);
    func_001614E0(p, 3, 2);
    p += 0x10;
    *(long *)p = 0x1000000000008001L;
    p += 8;
    *(long *)p = 0xE;
    p += 8;
    D_001EC95C = p;
    *(long *)p = 0x8000008000L;
    p += 8;
    *(long *)p = 0x3B;
    p += 8;
    func_00161590(p, 0);
    p += 0x10;
    D_002D81B0.cursor = p;
}
