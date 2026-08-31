struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED11C;
extern int D_001ED120;
extern struct S8_int D_001ED124;
void func_0010BCC8();

int func_00112F40();
int func_00151CA8();

void func_0010BC88(void) {
    D_001ED124.a = 1;
    D_001ED120 = 0;
    func_00112F40(func_0010BCC8);
    func_00151CA8(D_001ED11C.a);
    D_001ED11C.a = 0;
}
