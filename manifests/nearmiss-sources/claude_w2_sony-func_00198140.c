typedef struct Reent Reent;

extern void *func_00191B38(Reent *ptr, unsigned int size);
extern void *func_001923F4(void *dest, int value, unsigned int size);

void *func_00198140(Reent *ptr, unsigned int n, unsigned int size) {
    unsigned int *mem;
    unsigned int mzsz;
    unsigned int *mz;

    mem = (unsigned int *)func_00191B38(ptr, n * size);
    if (mem == 0) {
        return 0;
    }
    mzsz = (mem[-1] & 0xFFFFFFFCU) - 4;
    if (mzsz <= 36) {
        mz = mem;
        if (mzsz >= 20) {
            *mz++ = 0;
            *mz++ = 0;
            if (mzsz >= 28) {
                *mz++ = 0;
                *mz++ = 0;
                if (mzsz >= 36) {
                    *mz++ = 0;
                    *mz++ = 0;
                }
            }
        }
        *mz++ = 0;
        *mz++ = 0;
        *mz = 0;
    } else {
        func_001923F4(mem, 0, mzsz);
    }
    return mem;
}
