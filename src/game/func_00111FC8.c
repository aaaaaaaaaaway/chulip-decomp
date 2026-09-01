extern int D_001ED194;
extern int D_001ED198;
extern int D_001ED19C;

extern int func_00151A00(int size);
extern void func_00112F40(void (*fn)(void));
extern void func_00112EB0(void (*fn)(void), int count, int arg);
extern void func_00112208(void);

void func_00111FC8(int count) {
    D_001ED194 = count;
    D_001ED198 = -1;
    D_001ED19C = func_00151A00(count * 0xC0);
    func_00112F40(func_00112208);
    func_00112EB0(func_00112208, count, 0);
}
