void func_00188FD8(unsigned int *reg) {
    if (*(volatile unsigned int *)0x1000F520 == 0) {
        *(volatile unsigned int *)0x1000F590 = 0x1000;
    }
    *reg = *reg & 0xFFFFFEFF;
    *(volatile unsigned int *)0x1000F590 = 0;
}
