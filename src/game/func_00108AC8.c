typedef struct { int a; int b; } Pair;

extern Pair D_001ED0CC;
extern Pair D_001ED0D0;

void func_00108C28(void);
int func_00151A00(int size);
void func_00112EB0(void (*handler)(void), int a, int b);

void func_00108AC8(void) {
    D_001ED0CC.a = func_00151A00(0x60);
    func_00112EB0(func_00108C28, 0, 0);
    D_001ED0D0.a = 1;
}
