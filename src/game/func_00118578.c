extern int D_001ED1F4;

void func_00118C70(void);
int func_00151A00(int size);
void func_00112F40(void (*handler)(void));
void func_00112EB0(void (*handler)(void), int a, int b);

void func_00118578(void) {
    D_001ED1F4 = func_00151A00(0x1A280);
    func_00112F40(func_00118C70);
    func_00112EB0(func_00118C70, 6, D_001ED1F4);
}
