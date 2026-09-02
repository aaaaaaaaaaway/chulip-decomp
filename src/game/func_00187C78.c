extern char D_001EAF40[];
extern void func_00192508(char *message);

int func_00187C78(unsigned long *env, unsigned long *chain) {
    unsigned int i = 0;

    while (*(volatile int *)0x1000A000 & 0x100) {
        if (i++ > 0x1000000) {
            func_00192508(D_001EAF40);
            return -1;
        }
    }
    *(volatile int *)0x1000A020 = 6;
    if (((unsigned int)env & 0x70000000) == 0x70000000) {
        *(volatile int *)0x1000A010 = ((unsigned int)env & 0xFFFFFFF) | 0x80000000;
    } else {
        *(volatile int *)0x1000A010 = (unsigned int)env & 0xFFFFFFF;
    }
    *(volatile int *)0x1000A000 = 0x101;
    while (*(volatile int *)0x1000A000 & 0x100) {
        if (i++ > 0x1000000) {
            func_00192508(D_001EAF40);
            return -1;
        }
    }
    *(volatile int *)0x1000A020 = (int)(*(unsigned long *)((char *)env + 0x50) & 0x7FFF);
    if (((unsigned int)chain & 0x70000000) == 0x70000000) {
        *(volatile int *)0x1000A010 = ((unsigned int)chain & 0xFFFFFFF) | 0x80000000;
    } else {
        *(volatile int *)0x1000A010 = (unsigned int)chain & 0xFFFFFFF;
    }
    *(volatile int *)0x1000A000 = 0x101;
    return 0;
}
