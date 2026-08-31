struct S8_int { int a; char pad[4]; };

extern int D_001ED198;
extern struct S8_int D_001ED19C;
void func_00112208();

int func_00112F40();
int func_00151CA8();

void func_001121C0(void) {
    D_001ED198 = -1;
    func_00112F40(func_00112208);
    if (D_001ED19C.a != 0) {
        func_00151CA8(D_001ED19C.a);
    }
    D_001ED19C.a = 0;
}
