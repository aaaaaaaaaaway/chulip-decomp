struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED35C;
extern struct S8_int D_001ED360;
void func_00134EC8();

int func_00112EB0();
int func_00112F40();

int func_00134E68(void) {
    D_001ED360.a = 0;
    D_001ED35C.a = 0;
    func_00112F40(func_00134EC8);
    return func_00112EB0(func_00134EC8, 0, 0);
}
