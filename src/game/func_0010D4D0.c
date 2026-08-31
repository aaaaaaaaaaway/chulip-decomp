struct S8_int { int a; char pad[4]; };

extern int D_001ED144;
extern int D_001ED148;
extern struct S8_int D_001ED14C;
void func_0010D528();

int func_00112F40();
int func_00151CA8();

int func_0010D4D0(void) {
    D_001ED14C.a = 1;
    D_001ED148 = 0;
    func_00112F40(func_0010D528);
    return func_00151CA8(D_001ED144);
}
