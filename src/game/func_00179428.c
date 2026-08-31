extern int *D_001ED880;

void func_0017CA50();

void func_00179428(int flags, int index) {
    int *entry;

    entry = (int *)((char *)D_001ED880 + index * 44);
    func_0017CA50((flags | 268435456), entry[0], entry[1], entry[2], 0, entry[4]);
}
