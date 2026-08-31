struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED1F4;
void func_00118C70();

int func_00112F40();
int func_00151CA8();

int func_001185D0(void) {
    func_00151CA8(D_001ED1F4.a);
    return func_00112F40(func_00118C70);
}
