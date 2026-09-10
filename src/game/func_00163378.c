extern int D_001ED594;
extern int D_001ED598;
extern int D_001ED59C;
extern int D_001ED5A0;
extern float D_001ED5A4;

void func_00163408(void);
void func_00112F40(void (*fn)(void));
void func_00112EB0(void (*fn)(void), int a, int b);

void func_00163378(int a, int b) {
    D_001ED59C = 1;
    D_001ED598 = 0xFFFF0;
    D_001ED594 = a;
    D_001ED5A0 = b;
    D_001ED5A4 = (float)(0x190 / (a * b));
    func_00112F40(func_00163408);
    func_00112EB0(func_00163408, 0, 0);
}
