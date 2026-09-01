struct S001638B0 {
    char pad00[0x1A];
    short field1A;
    short field1C;
    short field1E;
};

extern int D_001ED844;

extern struct S001638B0 *D_001ED700;

short func_0012DED8();

short func_0012F9E8();

int func_001638A8(void) {
    return D_001ED844;
}

void func_001638B0(void) {
    D_001ED700->field1A = func_0012DED8(9, 0);
    D_001ED700->field1C = func_0012DED8(7, 0);
    D_001ED700->field1E = func_0012F9E8();
}
