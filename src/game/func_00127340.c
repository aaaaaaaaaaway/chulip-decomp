struct Entry_00127340 { unsigned char pad_0x0[0xE]; char field_0xe; };

struct Item_001FC450 { unsigned char pad_0x0[0x14]; int field_0x14; };

extern struct Item_001FC450 D_001FC450[];

extern struct Entry_00127340 *func_001263D8(unsigned short id);
extern int func_001266D8(unsigned short id);

void func_00127340(unsigned short id, char value) {
    struct Entry_00127340 *entry = func_001263D8(id);

    if (entry != 0) {
        entry->field_0xe = value;
    }
    if (func_001266D8(id) != -1) {
        D_001FC450[func_001266D8(id)].field_0x14 = value;
    }
}
