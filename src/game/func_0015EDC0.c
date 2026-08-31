typedef struct {
    int a;
    int b;
} Pair;

extern int D_001ED4B4;
extern Pair D_001ED4B8;
extern void func_0015EE20(void);
extern void func_00112EB0(void (*entry)(void), int arg1, int arg2);

void func_0015EDC0(int arg0) {
    D_001ED4B8.b = -1;
    D_001ED4B8.a = 10;
    D_001ED4B4 = 0;
    func_00112EB0(func_0015EE20, 0, arg0);
}
