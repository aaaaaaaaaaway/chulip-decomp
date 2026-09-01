extern int D_001ED150;
extern int D_001ED154;
int func_00151A00(int size);
void func_00112F40(void (*fn)(void));
void func_00112EB0(void (*fn)(void), int a, int b);
void func_0010E290(void);

void func_0010DBF0(void) {
    int i;
    int off;

    D_001ED150 = func_00151A00(0x3330);
    D_001ED154 = 1;
    off = 0;
    i = 7;
    do {
        *(int *)(D_001ED150 + off + 0x30) = 0;
        i--;
        off += 0x660;
    } while (i >= 0);
    func_00112F40(func_0010E290);
    func_00112EB0(func_0010E290, 0, 0);
}
