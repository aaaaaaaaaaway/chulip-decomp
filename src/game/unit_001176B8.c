extern int D_001FA1E8[];
void func_00117810(void);
void func_00112F40(void (*handler)(void));
void func_00112EB0(void (*handler)(void), int a, int b);
extern int D_001FA1F0[];

void func_001176B8(int a, int b) {
    D_001FA1E8[2] = a;
    D_001FA1E8[4] = b;
    D_001FA1E8[3] = 0;
    func_00112F40(func_00117810);
    func_00112EB0(func_00117810, 0, 0);
}

void func_00117708(void) {
    D_001FA1F0[0] = -1;
    func_00112F40(func_00117810);
}
