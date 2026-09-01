struct S8_int { int a; char pad[4]; };

extern int D_001ED10C;

extern int D_001ED104;

extern int D_001ED108;

void func_0010AB90();

int func_00112F40();

int func_00151CA8();

void func_0010AB50(int arg0) {
    D_001ED10C = arg0;
}

int func_0010AB58(void) {
    D_001ED10C = 1;
    D_001ED108 = 0;
    func_00112F40(func_0010AB90);
    return func_00151CA8(D_001ED104);
}
