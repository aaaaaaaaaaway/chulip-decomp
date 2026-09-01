extern int D_001ED144;
extern int D_001ED148;
extern int D_001ED14C;

extern int func_00151A00(int size);
extern void func_00112F40(void (*fn)(void));
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_0010D528(void);

void func_0010CEE8(int count) {
    int i;

    D_001ED144 = func_00151A00(count * 0x660);
    D_001ED14C = 1;
    D_001ED148 = count;
    for (i = 0; i < 32; i++) {
        *(int *)(i * 0x660 + D_001ED144) = 0;
    }
    func_00112F40(func_0010D528);
    func_00112EB0(func_0010D528, count, 0);
}
