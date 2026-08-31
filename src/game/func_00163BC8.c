struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED700;
extern struct S8_int D_001ED740;

int func_001923F4();

int func_00163BC8(void) {
    func_001923F4(D_001ED700.a, 0, 512);
    return func_001923F4(D_001ED740.a, 0, 1024);
}
