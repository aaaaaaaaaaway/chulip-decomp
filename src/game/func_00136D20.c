extern unsigned char D_2E53AC[];
extern void func_00100F40(void);

extern int func_001918A8(int size);
extern void func_001918D0(int handle);

int func_00136D20(void) {
    int available;

    available = 0x1FFEFF0 - ((int)D_2E53AC + (int)((unsigned char *)func_00100F40 + 0xC0));
    func_001918D0(func_001918A8(available));
    return available;
}
