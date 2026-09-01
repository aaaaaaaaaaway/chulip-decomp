extern int D_001ED0D4;
extern int D_001ED0D8;
extern int D_001ED0DC;

extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_001091E0(void);

void func_00108F30(int count) {
    int i;

    D_001ED0D4 = func_00151A00(count * 0x70);
    D_001ED0DC = 1;
    D_001ED0D8 = count;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x70 + D_001ED0D4) = 0;
    }
    func_00112EB0(func_001091E0, count, 0);
}
