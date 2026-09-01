extern int D_001ED164;
extern int D_001ED168;
extern int D_001EC898;
extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int a, int b);
extern void func_0010F940(void);
extern void func_00112F40(void (*fn)(void));
extern void func_00151CA8(int ptr);

void func_0010F008(int count) {
    int i;
    D_001ED168 = count;
    D_001ED164 = func_00151A00(count * 0xC30);
    D_001EC898 = 1;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0xC30 + D_001ED164) = 0;
    }
    func_00112EB0(func_0010F940, 0, 0);
}

void func_0010F088(void) {
    int i;
    for (i = 0; i < D_001ED168; i++) {
        *(int *)(i * 0xC30 + D_001ED164) = 0;
    }
    func_00112F40(func_0010F940);
    func_00151CA8(D_001ED164);
}
