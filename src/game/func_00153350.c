extern int D_001ED460;
extern int D_001ED464;
extern int D_001ED468;
extern int D_001ED46C;

void func_00152970(void);
void func_00112F40(void (*fn)(void));
void func_00112EB0(void (*fn)(void), int a, int b);

void func_00153350(int value) {
    D_001ED468 = value;
    D_001ED460 = 1;
    D_001ED464 = 0x14;
    D_001ED46C = 0;
    func_00112F40(func_00152970);
    func_00112EB0(func_00152970, 0, 0);
}
