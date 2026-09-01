extern int D_001ED138;
extern int D_001ED13C;
extern int D_001ED140;

extern int func_00151A00(int size);
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_0010CA70(void);

void func_0010C730(int count) {
    int i;

    D_001ED138 = func_00151A00(count * 0x5D0);
    D_001ED140 = 1;
    D_001ED13C = count;
    for (i = 0; i < count; i++) {
        *(int *)(i * 0x5D0 + D_001ED138) = 0;
    }
    func_00112EB0(func_0010CA70, count, 0);
}
