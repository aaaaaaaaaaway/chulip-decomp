struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED970;
extern struct S8_int D_001ED974;

int func_0017E1A0();
int func_0017E330();
int func_001985E0();

int func_0017F1D8(void) {
    func_0017E1A0(D_001ED970.a, 0, D_001ED974.a);
    func_0017E330(D_001ED970.a, D_001ED974.a, 0);
    return func_001985E0();
}
