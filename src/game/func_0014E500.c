struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED420;
void func_0014E338();

int func_00112EB0();
int func_00112F40();

int func_0014E500(void) {
    D_001ED420.a = 1;
    func_00112F40(func_0014E338);
    return func_00112EB0(func_0014E338, 0, 0);
}
