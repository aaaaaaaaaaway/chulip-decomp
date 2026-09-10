/* Install the file-I/O notification callback while interrupts are disabled,
 * returning the previous callback. The argument is stored before publishing
 * the new handler. */
typedef void (*HookHandler)(void *arg);

typedef struct {
    HookHandler handler;
    void *arg;
} Hook;

extern Hook D_002E3C80[];
extern int D_001E5B80[];
extern int func_0019C3E8(int arg);
extern void func_0019C4E8(void);
extern void func_001A0828(void);
extern void func_001A0870(void);
extern void func_0019C418(void);

HookHandler func_0019C428(HookHandler handler, void *arg) {
    HookHandler previous;
    Hook *hook = D_002E3C80;

    func_0019C3E8(0x1B);
    if (D_001E5B80[0] == 0) {
        func_0019C4E8();
    }
    func_001A0828();
    previous = hook->handler;
    hook->arg = arg;
    hook->handler = handler;
    func_001A0870();
    func_0019C418();
    return previous;
}
