struct Entry_00138C80 {
    int field_0x0;
    unsigned char pad_0x4[0xC];
    int field_0x10;
    unsigned char pad_0x14[0x10];
};

extern struct Entry_00138C80 D_00203C20[];

void func_00138C80(int key) {
    int offset;

    for (offset = 0; offset < 0x1440; offset += 0x24) {
        struct Entry_00138C80 *entry = (struct Entry_00138C80 *)((unsigned char *)D_00203C20 + offset);

        if (entry->field_0x0 == key) {
            entry->field_0x10 = entry->field_0x10 & ~1;
        }
    }
}
