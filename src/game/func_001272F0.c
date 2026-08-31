struct Entry_001272F0 { unsigned char pad_0x0[0xC]; char field_0xc; char field_0xd; };

extern struct Entry_001272F0 *func_001263D8(unsigned short id);

void func_001272F0(unsigned short id, char a, char b) {
    struct Entry_001272F0 *entry = func_001263D8(id);

    if (entry != 0) {
        entry->field_0xc = a;
        entry->field_0xd = b;
    }
}
