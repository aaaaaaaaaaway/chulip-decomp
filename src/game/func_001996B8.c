typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; } ThreadParam;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; } SemaParam;

extern int D_001E5AE8[];
extern int D_002E05C0[];
extern int D_002E05C8[];
extern int D_002E01C0[];
extern int D_001F4870[];

extern void func_001995E0(void *arg);
extern int func_001987A0(SemaParam *param);
extern int func_001987B0(int sema);
extern int func_001985A0(ThreadParam *param);
extern int func_001985C0(int tid, void *arg);
extern int func_00198690(void);
extern int func_00198630(int tid, int prio);

int func_001996B8(void) {
    ThreadParam tp;
    SemaParam sp;

    if (D_001E5AE8[0] > 0) {
        return -1;
    }
    sp.f4 = 0xFF;
    sp.f8 = 0;
    D_002E05C0[0] = func_001987A0(&sp);
    if (D_002E05C0[0] < 0) {
        return -1;
    }
    tp.f4 = (int)func_001995E0;
    tp.f8 = (int)D_002E01C0;
    tp.fC = 0x400;
    tp.f10 = (int)D_001F4870;
    tp.f14 = 0;
    D_001E5AE8[0] = func_001985A0(&tp);
    if (D_001E5AE8[0] < 0) {
        func_001987B0(D_002E05C0[0]);
        return -1;
    }
    D_002E05C8[0] = 0;
    D_002E05C8[1] = 0;
    func_001985C0(D_001E5AE8[0], D_002E05C8);
    func_00198630(func_00198690(), 1);
    return D_001E5AE8[0];
}
