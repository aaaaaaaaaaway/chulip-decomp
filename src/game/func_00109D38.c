struct S8_int { int a; char pad[4]; };

extern int D_001ED0EC;
extern int D_001ED0F0;
extern struct S8_int D_001ED0F4;
void func_00109D70();

int func_00112F40();
int func_00151CA8();

int func_00109D38(void) {
    D_001ED0F4.a = 1;
    D_001ED0F0 = 0;
    func_00112F40(func_00109D70);
    return func_00151CA8(D_001ED0EC);
}
