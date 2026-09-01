int func_00199E60(int c) {
    while ((*(volatile unsigned int *)0x1000F130 & 0x8000) != 0) {
    }
    *(unsigned char *)0x1000F180 = c;
    return c;
}
