struct S00171160 {
    char pad[0xA0];
    unsigned short count;
};

extern struct S00171160 *D_001ED7E0;
extern float D_001ED824;

int func_00171160(void) {
    if ((float)D_001ED7E0->count > D_001ED824) {
        return (int)D_001ED824;
    }
    return 0;
}
