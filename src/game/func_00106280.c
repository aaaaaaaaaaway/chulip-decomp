extern int D_001ED09C;
extern int D_001ED0A0;
extern int D_001ED0A4;

extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_001065B0(void);

void func_00106280(int count) {
    int i;

    D_001ED09C = func_00151A00(count * 0x80);
    D_001ED0A4 = 1;
    D_001ED0A0 = count;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x80 + D_001ED09C) = 0;
    }
    func_00112EB0(func_001065B0, count, 0);
}
