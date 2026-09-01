struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED264;

void func_00125618();

int func_00112F40();

int func_00151CA8();

void func_001255D8(int arg0, int arg1) {
    ((int *)((arg0 << 6) + D_001ED264.a))[0] = arg1;
}

int func_001255F0(void) {
    func_00112F40(func_00125618);
    return func_00151CA8(D_001ED264.a);
}
