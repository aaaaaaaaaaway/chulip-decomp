struct ThreadParam_00137FD0 {
    int status;
    void *entry;
    void *stack;
    int stackSize;
    void *gpReg;
    int priority;
    unsigned char pad_0x18[0x18];
};

extern int D_001F4870;

extern int func_001985A0(struct ThreadParam_00137FD0 *param);
extern void func_001985C0(int id, void *arg);

int func_00137FD0(void *entry, void *stack, int stackSize, int priority, void *arg) {
    struct ThreadParam_00137FD0 param;
    int id;

    param.entry = entry;
    param.stack = stack;
    param.stackSize = stackSize;
    param.priority = priority;
    param.gpReg = &D_001F4870;
    id = func_001985A0(&param);
    func_001985C0(id, arg);
    return id;
}
