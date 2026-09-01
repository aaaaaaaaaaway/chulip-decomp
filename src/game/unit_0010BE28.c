extern int D_001ED128;
extern int D_001ED12C;
extern int D_001ED130;
extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int a, int b);
extern void func_0010C570(void);
extern void func_00112F40(void (*fn)(void));
extern void func_00151CA8(int ptr);

void func_0010BE28(int count) {
    int i;
    D_001ED12C = count;
    D_001ED128 = func_00151A00(count * 0x60);
    D_001ED130 = 1;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x60 + D_001ED128) = 0;
    }
    func_00112EB0(func_0010C570, 0, 0);
}

void func_0010BEA8(void) {
    int i;
    for (i = 0; i < D_001ED12C; i++) {
        *(int *)(i * 0x60 + D_001ED128) = 0;
    }
    func_00112F40(func_0010C570);
    func_00151CA8(D_001ED128);
}
