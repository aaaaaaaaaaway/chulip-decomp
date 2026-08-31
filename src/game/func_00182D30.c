typedef struct {
    int a;
    int b;
} Pair;

extern Pair D_001ED9C4;
extern Pair D_001ED9C8;
extern Pair D_001ED9D0;
extern int D_001ED9CC;
extern int D_002DC9D4[];
extern void func_00182EA8(void);
extern void func_00183120(void);
extern void func_00182E58(int arg);
extern void func_00112EB0(void (*entry)(int), int a, int b);

void func_00182D30(void) {
    D_001ED9D0.a = 0x168;
    D_002DC9D4[0] = 0;
    D_001ED9C4.a = 0;
    D_001ED9C8.a = 0;
    D_001ED9CC = 0;
    func_00182EA8();
    func_00183120();
    func_00112EB0(func_00182E58, 0, 0);
}
