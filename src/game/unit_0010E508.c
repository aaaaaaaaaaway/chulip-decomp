extern int D_001ED158;
extern int D_001ED15C;
extern int D_001EC894;
extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int a, int b);
extern void func_0010EAC0(void);
extern void func_00112F40(void (*fn)(void));
extern void func_00151CA8(int ptr);

void func_0010E508(int count) {
    int i;
    D_001ED15C = count;
    D_001ED158 = func_00151A00(count * 0x630);
    D_001EC894 = 1;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x630 + D_001ED158) = 0;
    }
    func_00112EB0(func_0010EAC0, 0, 0);
}

void func_0010E588(void) {
    int i;
    for (i = 0; i < D_001ED15C; i++) {
        *(int *)(i * 0x630 + D_001ED158) = 0;
    }
    func_00112F40(func_0010EAC0);
    if (D_001ED158 != 0) {
        func_00151CA8(D_001ED158);
    }
    D_001ED158 = 0;
}
