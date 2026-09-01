extern int D_001ED170;
extern int D_001ED174;
extern int D_001EC89C;
extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int a, int b);
extern void func_001103F0(void);
extern void func_00112F40(void (*fn)(void));
extern void func_00151CA8(int ptr);

void func_0010FF08(int count) {
    int i;
    D_001ED174 = count;
    D_001ED170 = func_00151A00(count * 0x810);
    D_001EC89C = 1;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x810 + D_001ED170) = 0;
    }
    func_00112EB0(func_001103F0, 0, 0);
}

void func_0010FF88(void) {
    int i;
    for (i = 0; i < D_001ED174; i++) {
        *(int *)(i * 0x810 + D_001ED170) = 0;
    }
    func_00112F40(func_001103F0);
    func_00151CA8(D_001ED170);
}
