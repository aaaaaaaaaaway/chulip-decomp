struct S8_int { int a; char pad[4]; };

extern int D_001ED118;

extern int D_001ED110;

extern int D_001ED114;

void func_0010B488();

int func_00112F40();

int func_00151CA8();

void func_0010B448(int arg0) {
    D_001ED118 = arg0;
}

int func_0010B450(void) {
    D_001ED118 = 1;
    D_001ED114 = 0;
    func_00112F40(func_0010B488);
    return func_00151CA8(D_001ED110);
}
