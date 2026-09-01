extern int D_001ED1A0;
extern int D_001ED1A4;
extern int D_001ED1A8;

extern int func_00151A00(int size);
extern void func_00112F40(void (*fn)(void));
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_00112AE8(void);

void func_00112728(int count) {
    D_001ED1A0 = count;
    D_001ED1A4 = -1;
    D_001ED1A8 = func_00151A00(count * 0x60);
    func_00112F40(func_00112AE8);
    func_00112EB0(func_00112AE8, count, 0);
}
