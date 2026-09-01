extern void func_001880F0(char *entry);
extern int func_001874A8(char *arg);

int func_00187828(char *base, int flags) {
    int index;
    int result;

    index = flags & 1;
    func_001880F0(base + index * 0x28);
    if (index != 0) {
        result = func_001874A8(base + 0x140);
    } else {
        result = func_001874A8(base + 0x50);
    }
    return result;
}
