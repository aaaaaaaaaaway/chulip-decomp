struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED09C;
extern int D_001ED0A0;
extern struct S8_int D_001ED0A4;
void func_001065B0();

int func_00112F40();
int func_00151CA8();

void func_00106570(void) {
    D_001ED0A4.a = 1;
    D_001ED0A0 = 0;
    func_00112F40(func_001065B0);
    func_00151CA8(D_001ED09C.a);
    D_001ED09C.a = 0;
}
