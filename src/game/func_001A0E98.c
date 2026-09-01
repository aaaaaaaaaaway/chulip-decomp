extern void *D_001E66A8[];
extern char D_001A1580[];
extern void func_00198450(int index, char *handler);
extern void func_00198460(int index, char *handler);

void *func_001A0E98(int index, void *handler) {
    void *previous;
    if ((unsigned int)(index - 1) >= 0xD) {
        return (void *)0xFFFFFFFF;
    }
    previous = D_001E66A8[index];
    D_001E66A8[index] = handler;
    if ((unsigned int)(index - 1) < 3) {
        func_00198450(index, D_001A1580);
        return previous;
    }
    func_00198460(index, D_001A1580);
    return previous;
}
