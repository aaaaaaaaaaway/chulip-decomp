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
    struct Entry_00138988 *entry_value;
    int i;
    for (i = 0; i < 144; i++) {
        entry_value = entry;
        if (entry->field_0x0 == key) {
            entry_value->field_0x10 = entry_value->field_0x10 | 2;
            func_00139EB8(i);
        }
        entry = entry + 1;
    }

    entry = entry + 1;
}
