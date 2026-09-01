typedef struct {
    unsigned int flags;
    unsigned int flags2;
    char pad08[0xB8];
} Ent001720B0;

extern Ent001720B0 *D_001ED6C0;

unsigned short func_00173148();

void func_001720B0(unsigned short id, unsigned int bits, unsigned char set) {
    unsigned short index;

    index = func_00173148(id);
    if (set != 0) {
        D_001ED6C0[index].flags2 |= bits;
    } else {
        D_001ED6C0[index].flags2 &= ~bits;
    }
}
