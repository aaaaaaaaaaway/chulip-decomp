extern void *D_002DE900[];
extern int func_0018F5E8(int mode);
extern int func_001A0828(void);
extern int func_001A0870(void);

void *func_0018EB80(void *handler) {
    void *previous;

    if (func_0018F5E8(1) != 0) {
        return 0;
    }
    func_001A0828();
    previous = D_002DE900[0];
    D_002DE900[0] = handler;
    func_001A0870();
    return previous;
}
