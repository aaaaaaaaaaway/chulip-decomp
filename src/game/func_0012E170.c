struct Score_001A6998 {
    unsigned char pad_0x0[0x68];
    unsigned char slot_0x68[0x16];
    unsigned char slot_0x7E[0x20];
};

extern struct Score_001A6998 D_001A6998;

short func_0012E170(unsigned short kind, unsigned char index) {
    int i;

    if (kind != 0xB) {
        if (kind != 0xC) {
            return 0xFF;
        }
        if (index == 0xFF) {
            for (i = 0; i < 0x20; i++) {
                if (D_001A6998.slot_0x7E[i] == 0xFF) {
                    break;
                }
            }
            return i;
        }
        return D_001A6998.slot_0x7E[index];
    }
    if (index == 0xFF) {
        for (i = 0; i < 0x16; i++) {
            if (D_001A6998.slot_0x68[i] == 0xFF) {
                break;
            }
        }
        return i;
    }
    return D_001A6998.slot_0x68[index];
}
