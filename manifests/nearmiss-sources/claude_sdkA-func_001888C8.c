#define D_CTRL (*(volatile unsigned int *)0x1000E060)

void func_001888C8(unsigned int value) {
    (void)D_CTRL;
    if (value != 0xFFFFFFFF) {
        D_CTRL = value;
    }
}
