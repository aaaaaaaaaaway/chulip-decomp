extern int D_001E66A0[];
extern void func_001A1340(void);
extern void func_00198450(int index, void (*handler)(void));

int func_001A0E38(int arg) {
    void (*handler)(void);

    handler = func_001A1340;
    D_001E66A0[0] = arg;
    func_00198450(1, handler);
    func_00198450(2, handler);
    func_00198450(3, handler);
    return arg;
}
