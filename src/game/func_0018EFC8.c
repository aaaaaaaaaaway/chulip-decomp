extern int D_001E317C[];
extern void *D_002DE904[];
extern void *D_002DE908[];
extern void func_0018F078(void);
extern int func_001A0828(void);
extern int func_001A0870(void);

void *func_0018EFC8(void *handler, void *argument) {
    void *previous;
    if (D_001E317C[0] < 0) {
        func_0018F078();
    }
    func_001A0828();
    previous = D_002DE904[0];
    D_002DE908[0] = argument;
    D_002DE904[0] = handler;
    func_001A0870();
    return previous;
}
