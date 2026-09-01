struct Entity_001ED310 { unsigned char pad_0x0[0x62]; unsigned short field_0x62; unsigned char pad_0x64[8]; int field_0x6C; unsigned char pad_0x70[0x10]; };
struct Score_001A6998 { unsigned char pad_0x0[0x5C]; int field_0x5C; };
struct Rec_001A5008 { unsigned char count; unsigned char limit; unsigned char entries[0x100]; };
struct List_001FDB00 { unsigned char count; unsigned char limit; unsigned char entries[0x200]; };

extern struct Entity_001ED310 *D_001ED310;
extern struct Score_001A6998 D_001A6998;
extern struct Rec_001A5008 D_001A5008[];
extern struct List_001FDB00 D_001FDB00;
extern int D_001EC8F0;

extern int func_0012FBF0(int entry);

int func_0012C548(unsigned short slot, unsigned short index) {
    unsigned char entry;

    entry = D_001A5008[slot].entries[index];
    if ((unsigned int)D_001A6998.field_0x5C < (unsigned int)D_001ED310[entry].field_0x6C) {
        return 1;
    }
    if (D_001FDB00.count + 1 >= D_001FDB00.limit) {
        return 0xFF;
    }
    if ((D_001ED310[entry].field_0x62 & 0x10) != 0) {
        if (func_0012FBF0(entry) != 0) {
            return 2;
        }
    }
    D_001A6998.field_0x5C = D_001A6998.field_0x5C - D_001ED310[entry].field_0x6C;
    return 0;
}
