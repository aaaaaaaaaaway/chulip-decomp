struct S8_int { int a; char pad[4]; };

extern int D_001ED1A4;
extern struct S8_int D_001ED1A8;
void func_00112AE8();

int func_00112F40();
int func_00151CA8();

void func_00112AA0(void) {
    D_001ED1A4 = -1;
    func_00112F40(func_00112AE8);
    if (D_001ED1A8.a != 0) {
        func_00151CA8(D_001ED1A8.a);
    }
    D_001ED1A8.a = 0;
}
