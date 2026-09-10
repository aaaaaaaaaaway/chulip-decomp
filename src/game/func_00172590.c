/* Copy selected controller state bits into the current object's flags. */
extern unsigned long *func_00136AE8(void);
extern int D_001ED740;

void func_00172590(void) {
    unsigned long *object = func_00136AE8();
    unsigned short control = *(unsigned short *)D_001ED740;

    *object = (*object & ~(1UL << 7)) | ((unsigned long)(control & 1) << 7);
    *object = (*object & ~(1UL << 25)) | ((unsigned long)((control >> 12) & 1) << 25);
    *object = (*object & ~(1UL << 44)) | ((unsigned long)(((*(unsigned short *)(D_001ED740 + 2)) >> 3) & 1) << 44);
}
