extern int D_001ED0F8;
extern int D_001ED0FC;
extern int D_001ED100;

void func_0010A240(void);
int func_00151A00(int size);
void func_00112EB0(void (*handler)(void), int a, int b);

void func_00109FA0(void) {
    int one = 1;

    D_001ED0F8 = func_00151A00(0x1A0);
    D_001ED0FC = one;
    D_001ED100 = one;
    func_00112EB0(func_0010A240, one, 0);
}
