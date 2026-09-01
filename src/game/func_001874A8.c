extern char D_001EADF0[];
extern void func_00192508(char *message);

int func_001874A8(unsigned long *env) {
    unsigned int i = 0;

    while (*(volatile int *)0x1000A000 & 0x100) {
        if (i++ > 0x1000000) {
            func_00192508(D_001EADF0);
            return -1;
        }
    }
    *(volatile int *)0x1000A020 = (int)(*env & 0x7FFF) + 1;
    if (((unsigned int)env & 0x70000000) == 0x70000000) {
        *(volatile int *)0x1000A010 = ((unsigned int)env & 0xFFFFFFF) | 0x80000000;
    } else {
        *(volatile int *)0x1000A010 = (unsigned int)env & 0xFFFFFFF;
    }
    *(volatile int *)0x1000A000 = 0x101;
    return 0;
}
