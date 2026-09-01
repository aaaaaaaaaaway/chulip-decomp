extern int D_001ED0EC;
extern int D_001ED0F0;
extern int D_001ED0F4;

extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_00109D70(void);

void func_00109AA8(int count) {
    int i;

    D_001ED0EC = func_00151A00(count * 0x70);
    D_001ED0F4 = 1;
    D_001ED0F0 = count;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x70 + D_001ED0EC) = 0;
    }
    func_00112EB0(func_00109D70, count, 0);
}
