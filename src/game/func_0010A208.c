struct S8_int { int a; char pad[4]; };

extern int D_001ED0F8;
extern int D_001ED0FC;
extern struct S8_int D_001ED100;
void func_0010A240();

int func_00112F40();
int func_00151CA8();

int func_0010A208(void) {
    D_001ED100.a = 1;
    D_001ED0FC = 0;
    func_00112F40(func_0010A240);
    return func_00151CA8(D_001ED0F8);
}
