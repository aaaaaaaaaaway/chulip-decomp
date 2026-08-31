extern int *D_001ED880;

void func_0017CA50();

void func_00179618(int flags, int index) {
    int *entry;

    entry = (int *)((char *)D_001ED880 + index * 44);
    func_0017CA50((flags | 536870912), entry[0], entry[1], entry[2], 0, 64);
}
