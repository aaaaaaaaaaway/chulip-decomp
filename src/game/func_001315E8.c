extern int D_002D81B0[];
extern long *D_001EC954;

void func_00161590(long *p, int mode);
void func_00161460(long *p, int mode);
void func_001614E0(long *p, int a, int b);

void func_001315E8(void) {
    long *p;

    p = (long *)D_002D81B0[1];
    D_001EC954 = p;
    func_00161590(p, 7);
    func_00161460(p, 7);
    func_001614E0(p, 3, 7);
    p += 2;
    *p = 0x1000000000008001L;
    p++;
    *p = 0xEL;
    p++;
    *p = 0x32001L;
    p++;
    *p = 0x47L;
    p++;
    *p = 0x4022400000008001L;
    p++;
    *p = 0x4444L;
    p++;
    *p = 0x0000FFF079007000L;
    p++;
    *p = 0x0000FFF079009000L;
    p++;
    *p = 0xFFFFFFFF87007000L;
    p++;
    *p = 0xFFFFFFFF87009000L;
    p++;
    *p = 0x1000000000008001L;
    p++;
    *p = 0xEL;
    p++;
    *p = 0x30000L;
    p++;
    *p = 0x47L;
    p++;
    func_00161590(p, 0);
    p += 2;
    D_002D81B0[1] = (int)p;
}
