extern int D_001EC8C8;
extern int D_001EC8C4;

int func_00112EB0();
int func_00112F40();
int func_00117A48();

void func_001177A8();
int func_00117738(int arg0) {
    D_001EC8C8 = arg0;
    if (arg0 == 2) {
        func_00117A48();
    }
    func_00112F40(func_001177A8);
    return func_00112EB0(func_001177A8, 0, 0);
}

void func_00117788(void) {
    if (D_001EC8C8 == 2) {
        D_001EC8C4 = (D_001EC8C4 + 1);
    }
}
