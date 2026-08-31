typedef struct { int a; int b; } Pair;

extern Pair D_001ED104;
extern int D_001ED108;
extern Pair D_001ED10C;

void func_0010AB90(void);
int func_00151A00(int size);
void func_00112F40(void (*handler)(void));
void func_00112EB0(void (*handler)(void), int a, int b);

void func_0010A9A8(void) {
    int one = 1;

    D_001ED104.a = func_00151A00(0x110);
    D_001ED108 = one;
    D_001ED10C.a = one;
    func_00112F40(func_0010AB90);
    func_00112EB0(func_0010AB90, one, 0);
}
