struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED994;
extern struct S8_int D_001ED998;
extern struct S8_int D_001ED9AC;
extern int D_001ED9B0;

int func_00181DF0();

int func_00181DB8(int arg0, int arg1) {
    D_001ED994.a = arg0;
    D_001ED998.a = arg1;
    D_001ED9AC.a = 0;
    D_001ED9B0 = 0;
    return func_00181DF0();
}
