typedef struct {
    int *handler;
    int *arg;
} Hook;

extern Hook D_002E3C80[];
extern int D_001E5B80[];
extern void func_0019C3E8(int arg);
extern void func_0019C4E8(void);
extern void func_001A0828(void);
extern void func_001A0870(void);
extern void func_0019C418(void);

int *func_0019C428(int *handler, int *arg) {
    int *previous;

    func_0019C3E8(0x1B);
    if (D_001E5B80[0] == 0) {
        func_0019C4E8();
    }
    func_001A0828();
    previous = D_002E3C80->handler;
    D_002E3C80->handler = handler;
    D_002E3C80->arg = arg;
    func_001A0870();
    func_0019C418();
    return previous;
}
