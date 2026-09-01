struct Score_001A6998 {
    unsigned char pad_0x0[0x68];
    unsigned char slots_a[0x16];
    unsigned char slots_b[0x20];
};

extern struct Score_001A6998 D_001A6998;

extern void func_001923F4(unsigned char *destination, int value, int size);

void func_0012E250(unsigned short kind, short value) {
    int i;

    switch (kind) {
    case 0xC:
        if (value == -1) {
            func_001923F4(D_001A6998.slots_b, 0xFF, 0x20);
        } else {
            for (i = 0; i < 0x20; i++) {
                if (D_001A6998.slots_b[i] == 0xFF) {
                    break;
                }
                if (D_001A6998.slots_b[i] == value) {
                    break;
                }
            }
            D_001A6998.slots_b[i] = value;
        }
        break;
    case 0xB:
        if (value == -1) {
            func_001923F4(D_001A6998.slots_a, 0xFF, 0x16);
        } else {
            for (i = 0; i < 0x16; i++) {
                if (D_001A6998.slots_a[i] == 0xFF) {
                    break;
                }
                if (D_001A6998.slots_a[i] == value) {
                    break;
                }
            }
            D_001A6998.slots_a[i] = value;
        }
        break;
    }
}
