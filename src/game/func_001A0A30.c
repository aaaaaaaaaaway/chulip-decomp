extern void func_00198850(int *value);
extern void func_00198840(int *value);

int func_001A0A30(void) {
    int saved;
    int probe;

    func_00198850(&saved);
    probe = (saved & 0xFFFF1FFF) | 0x2000;
    func_00198840(&probe);
    func_00198850(&probe);
    func_00198840(&saved);
    return (((unsigned int)probe >> 13) & 7) == 0;
}
