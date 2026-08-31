struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED0C0;
extern int D_001ED0C4;
extern struct S8_int D_001ED0C8;
void func_001081E0();

int func_00112F40();
int func_00151CA8();

void func_001081A0(void) {
    D_001ED0C8.a = 1;
    D_001ED0C4 = 0;
    func_00112F40(func_001081E0);
    func_00151CA8(D_001ED0C0.a);
    D_001ED0C0.a = 0;
}
