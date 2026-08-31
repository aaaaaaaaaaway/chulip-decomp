struct S8_int { int a; char pad[4]; };

extern struct S8_int D_001ED9D4;
extern struct S8_int D_001ED9D8;
extern struct S8_int D_001ED9DC;
extern int D_001ED9E0;

int func_00112EB0();
int func_00112F40();

void func_00184228();
int func_001841A0(void) {
    D_001ED9D4.a = 0;
    D_001ED9D8.a = 0;
    D_001ED9DC.a = 0;
    D_001ED9E0 = 0;
    func_00112F40(func_00184228);
    return func_00112EB0(func_00184228, 0, 0);
}

void func_001841F8(int arg0, int arg1) {
    D_001ED9D4.a = arg0;
    D_001ED9D8.a = arg1;
    D_001ED9E0 = 1;
}
