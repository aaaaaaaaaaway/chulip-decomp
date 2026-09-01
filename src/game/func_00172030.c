typedef struct {
    unsigned int flags;
    char pad04[0xBC];
} Ent00172030;

extern Ent00172030 *D_001ED6C0;

unsigned short func_00173148();

void func_00172030(unsigned short id, unsigned int bits, unsigned char set) {
    unsigned short index;

    index = func_00173148(id);
    if (set != 0) {
        D_001ED6C0[index].flags |= bits;
    } else {
        D_001ED6C0[index].flags &= ~bits;
    }
}
