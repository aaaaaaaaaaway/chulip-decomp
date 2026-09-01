void func_00188FD8(volatile unsigned int *reg) {
    unsigned int value;
    if (*(volatile unsigned int *)0x1000F520 == 0) {
        *(volatile unsigned int *)0x1000F590 = 0x1000;
    }
    value = *reg;
    *reg = value & 0xFFFFFEFFu;
    *(volatile unsigned int *)0x1000F590 = 0;
}
