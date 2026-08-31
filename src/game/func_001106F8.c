extern int D_001ED17C;
extern int D_001ED180;
extern int D_001ED184;

void func_00110D70(void);
int func_00151A00(int size);
void func_00112EB0(void (*handler)(void), int a, int b);

void func_001106F8(int count) {
    D_001ED17C = func_00151A00(count * 0x1320);
    D_001ED180 = count;
    D_001ED184 = 1;
    func_00112EB0(func_00110D70, count, 0);
}
