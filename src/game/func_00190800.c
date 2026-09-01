extern void func_001907D8(void);
extern int func_00198690(void);
extern void func_00198520(int index, void (*handler)(void), int arg);
extern void func_001986C0(void);

void func_00190800(int id) {
    void (*handler)(void);
    int index;
    int arg;

    handler = func_001907D8;
    index = id & 0xFFFF;
    arg = func_00198690();
    func_00198520(index, handler, arg);
    func_001986C0();
}
