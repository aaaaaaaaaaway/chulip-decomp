extern int D_001ED11C;
extern int D_001ED120;
extern int D_001ED124;

extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_0010BCC8(void);

void func_0010BA18(int count) {
    int i;

    D_001ED11C = func_00151A00(count * 0x70);
    D_001ED124 = 1;
    D_001ED120 = count;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x70 + D_001ED11C) = 0;
    }
    func_00112EB0(func_0010BCC8, count, 0);
}
