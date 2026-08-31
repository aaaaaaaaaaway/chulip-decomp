struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED994;
extern struct S8_int D_001ED998;
extern struct S8_int D_001ED99C;
extern int D_001ED9A0;
extern struct S8_int D_001ED9A4;
extern struct S8_int D_001ED9A8;
extern struct S8_int D_001ED9AC;
extern struct S8_int D_001ED9B0;

void func_00181DF0(void) {
    D_001ED9A4.a = D_001ED9AC.a;
    D_001ED9A8.a = D_001ED9B0.a;
    D_001ED99C.a = D_001ED994.a;
    D_001ED9A0 = D_001ED998.a;
}
