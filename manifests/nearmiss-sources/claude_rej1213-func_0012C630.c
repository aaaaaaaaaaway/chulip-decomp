/* object_flags: -Wa,-G4 */
struct Record_0012C630 {
    unsigned char pad_0x0[0x62];
    unsigned short field_0x62;
    unsigned char pad_0x64[0x8];
    unsigned int field_0x6c;
    unsigned char pad_0x70[0x10];
};

struct Table_001ED310 { struct Record_0012C630 *records; int unused; };

struct Header_001A6998 { unsigned char pad_0x0[0x5C]; unsigned int field_0x5c; };

extern unsigned char D_001FDB00[];
extern struct Table_001ED310 D_001ED310;
extern struct Header_001A6998 D_001A6998;

int func_0012C630(int unused, unsigned short index) {
    unsigned char *slot = D_001FDB00 + index;
    struct Record_0012C630 *record = &D_001ED310.records[slot[2]];
    unsigned int total;

    if (record->field_0x62 & 4) {
        return 1;
    }
    total = D_001A6998.field_0x5c + record->field_0x6c;
    if (total > 0x7FFF) {
        D_001A6998.field_0x5c = 0x7FFF;
    } else {
        D_001A6998.field_0x5c = total;
    }
    return 0;
}
