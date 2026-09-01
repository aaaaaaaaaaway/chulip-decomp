extern int D_001ED9D4;
extern int D_001ED9D8;
extern int D_001ED9DC;
extern int D_001ED9E0;

int func_00112EB0();
int func_00112F40();

void func_00184228();
int func_001841A0(void) {
    D_001ED9D4 = 0;
    D_001ED9D8 = 0;
    D_001ED9DC = 0;
    D_001ED9E0 = 0;
    func_00112F40(func_00184228);
    return func_00112EB0(func_00184228, 0, 0);
}

void func_001841F8(int arg0, int arg1) {
    D_001ED9D4 = arg0;
    D_001ED9D8 = arg1;
    D_001ED9E0 = 1;
}
