extern int D_001ED110;
extern int D_001ED114;
extern int D_001ED118;

void func_0010B488(void);
int func_00151A00(int size);
void func_00112EB0(void (*handler)(void), int a, int b);

void func_0010B2E0(void) {
    int one = 1;

    D_001ED110 = func_00151A00(0x100);
    D_001ED114 = one;
    D_001ED118 = one;
    func_00112EB0(func_0010B488, one, 0);
}
