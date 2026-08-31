extern void func_00133990(int arg0, int arg1, int *arg2);

void func_00133960(int arg0, int arg1) {
    int *entry = (int *)(arg0 * 0x14 + arg1);

    func_00133990(arg0, entry[0], entry + 1);
}
