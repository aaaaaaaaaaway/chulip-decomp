struct S00171118 {
    char pad[0x9C];
    unsigned short count;
};

extern struct S00171118 *D_001ED7E0;
extern float D_001ED824;

int func_00171118(void) {
    if ((float)D_001ED7E0->count > D_001ED824) {
        return (int)D_001ED824 + 1;
    }
    return 0;
}
