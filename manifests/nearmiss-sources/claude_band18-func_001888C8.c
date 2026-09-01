void func_001888C8(unsigned int value) {
    (void)*(volatile unsigned int *)0x1000E060;
    if (value != 0xFFFFFFFF) {
        *(volatile unsigned int *)0x1000E060 = value;
    }
}
