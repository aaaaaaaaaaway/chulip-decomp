struct S8_int { int a; char pad[4]; };

extern int D_001ED138;
extern int D_001ED13C;
extern struct S8_int D_001ED140;
void func_0010CA70();

int func_00112F40();
int func_00151CA8();

int func_0010CA38(void) {
    D_001ED140.a = 1;
    D_001ED13C = 0;
    func_00112F40(func_0010CA70);
    return func_00151CA8(D_001ED138);
}
