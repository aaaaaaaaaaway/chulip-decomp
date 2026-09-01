struct S001710D0 {
    char pad[0x9E];
    unsigned short count;
};

extern struct S001710D0 *D_001ED7E0;
extern float D_001ED824;

int func_001710D0(void) {
    if ((float)D_001ED7E0->count > D_001ED824) {
        return (int)D_001ED824 + 1;
    }
    return 0;
}
