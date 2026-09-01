struct S00171058 {
    char pad[0xA2];
    unsigned short count;
};

struct E00171058 {
    char pad0[4];
    unsigned int flags;
    char pad8[0xB8];
};

extern struct S00171058 *D_001ED7E0;
extern struct E00171058 *D_001ED6C0;
extern float D_001ED824;

int func_00171058(int index) {
    if ((float)D_001ED7E0->count > D_001ED824) {
        D_001ED6C0[index].flags |= 0x20000000;
        return (int)D_001ED824 + 1;
    }
    return 0;
}
