struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED42C;
extern struct S8_int D_001ED430;
extern int D_001ED434;

void func_0014FF10(int arg0, int arg1, int arg2) {
    D_001ED42C.a = arg0;
    D_001ED430.a = arg1;
    D_001ED434 = arg2;
}
