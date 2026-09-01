extern int D_001ED0E0;
extern int D_001ED0E4;
extern int D_001ED0E8;

extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_001097F8(void);

void func_00109418(int count) {
    int i;

    D_001ED0E0 = func_00151A00(count * 0x1F0);
    D_001ED0E8 = 1;
    D_001ED0E4 = count;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x1F0 + D_001ED0E0) = 0;
    }
    func_00112EB0(func_001097F8, count, 0);
}
