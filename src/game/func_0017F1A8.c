struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED970;
extern struct S8_int D_001ED974;

int func_0017E330();

int func_0017F1A8(void) {
    return func_0017E330(D_001ED970.a, D_001ED974.a, 0);
}
