extern int D_001ED0C0;
extern int D_001ED0C4;
extern int D_001ED0C8;
void func_001081E0();

int func_00112F40();
int func_00151CA8();

void func_001081A0(void) {
    D_001ED0C8 = 1;
    D_001ED0C4 = 0;
    func_00112F40(func_001081E0);
    func_00151CA8(D_001ED0C0);
    D_001ED0C0 = 0;
}
