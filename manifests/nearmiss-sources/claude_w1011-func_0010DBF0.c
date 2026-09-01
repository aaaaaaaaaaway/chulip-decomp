extern int D_001ED150;
extern int D_001ED154;

extern int func_00151A00(int size);
extern void func_00112F40(void (*fn)(void));
extern void func_00112EB0(void (*fn)(void), int a, int b);
extern void func_0010E290(void);

void func_0010DBF0(void) {
    int i;

    D_001ED150 = func_00151A00(0x3330);
    D_001ED154 = 1;
    for (i = 0; i < 8; i++) {
        *(int *)(D_001ED150 + i * 0x660 + 0x30) = 0;
    }
    func_00112F40(func_0010E290);
    func_00112EB0(func_0010E290, 0, 0);
}
