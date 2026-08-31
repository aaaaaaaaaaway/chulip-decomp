struct S8_int { int a; char pad[4]; };

extern int D_001ED188;
extern int D_001ED18C;
extern struct S8_int D_001ED190;
void func_001114F8();

int func_00112F40();
int func_00151CA8();

int func_001114C0(void) {
    D_001ED190.a = 1;
    D_001ED18C = 0;
    func_00112F40(func_001114F8);
    return func_00151CA8(D_001ED188);
}
