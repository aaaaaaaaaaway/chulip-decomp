struct Entry_00138E08 {
    int field_0x0;
    unsigned char pad_0x4[0x10];
    short field_0x14[8];
};

extern struct Entry_00138E08 D_00203C20[];

short func_00138E08(int key, unsigned short slot) {
    int i;

    for (i = 0; i < 144; i++) {
        if (D_00203C20[i].field_0x0 == key) {
            return D_00203C20[i].field_0x14[slot];
        }
    }
    return -1;
}
