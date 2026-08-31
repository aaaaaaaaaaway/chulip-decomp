struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED34C;
extern int D_001ED350;
extern int D_001ED354;
void func_00134570();

int func_00112F40();
int func_00151CA8();

int func_00133F20(void) {
    D_001ED34C.a = 1;
    D_001ED350 = 0;
    func_00112F40(func_00134570);
    return func_00151CA8(D_001ED354);
}
