struct S8_int { int a; char pad[4]; };

extern int D_001ED330;

extern int D_001ED32C;

int func_00151CA8();

int func_00129040(void) {
    return D_001ED330;
}

int func_00129048(void) {
    func_00151CA8(D_001ED330);
    return func_00151CA8(D_001ED32C);
}
