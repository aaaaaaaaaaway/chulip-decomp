struct Entry_00138988 {
    int field_0x0;
    unsigned char pad_0x4[0xC];
    int field_0x10;
    unsigned char pad_0x14[0x10];
};

extern struct Entry_00138988 D_00203C20[];

extern void func_00139EB8(int index);

void func_00138988(int key) {
    struct Entry_00138988 *entry = D_00203C20;
    int i;

    for (i = 0; i < 144; i++) {
        if (entry->field_0x0 == key) {
            entry->field_0x10 = entry->field_0x10 | 2;
            func_00139EB8(i);
        }
        entry = entry + 1;
    }
}
