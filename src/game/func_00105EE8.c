struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED090;
extern int D_001ED094;
extern struct S8_int D_001ED098;
void func_00105F28();

int func_00112F40();
int func_00151CA8();

void func_00105EE8(void) {
    D_001ED098.a = 1;
    D_001ED094 = 0;
    func_00112F40(func_00105F28);
    func_00151CA8(D_001ED090.a);
    D_001ED090.a = 0;
}
