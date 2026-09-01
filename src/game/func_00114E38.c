typedef struct { int a; int b; } Pair;

extern int D_001ED1C0[];
extern Pair D_001ED1BC;
extern Pair D_001ED1C4;
extern int D_001EC8B8;

int func_0017E840(int size, int flags);

void func_00114E38(int value) {
    if (D_001ED1C0[0] == 0) {
        D_001ED1BC.b = func_0017E840(0x1C000, 0);
    }
    D_001EC8B8 = value;
    D_001ED1C4.a = value;
}
