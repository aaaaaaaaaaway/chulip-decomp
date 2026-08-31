struct S8_int { int a; char pad[4]; };

extern int D_001ED3F0;
extern struct S8_int D_001ED3F4;

int func_001724E8();
int func_00172628();

void func_0014D1E0(void) {
    D_001ED3F0 = 0;
    func_001724E8(0);
    func_00172628(0);
    D_001ED3F4.a = 0;
}
