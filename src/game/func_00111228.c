extern int D_001ED188;
extern int D_001ED18C;
extern int D_001ED190;

void func_001114F8(void);
int func_00151A00(int size);
void func_00112EB0(void (*handler)(void), int a, int b);

void func_00111228(int count) {
    D_001ED188 = func_00151A00(count * 0x990);
    D_001ED18C = count;
    D_001ED190 = 1;
    func_00112EB0(func_001114F8, count, 0);
}
