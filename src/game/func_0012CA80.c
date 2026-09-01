struct Entity_001ED310 { unsigned char pad_0x0[0x62]; unsigned short field_0x62; unsigned char pad_0x64[8]; int field_0x6C; unsigned char pad_0x70[0x10]; };
struct Score_001A6998 { unsigned char pad_0x0[0x5C]; int field_0x5C; };
struct Rec_001A5008 { unsigned char count; unsigned char limit; unsigned char entries[0x100]; };
struct List_001FDB00 { unsigned char count; unsigned char limit; unsigned char entries[0x200]; };

extern struct Entity_001ED310 *D_001ED310;
extern struct Score_001A6998 D_001A6998;
extern struct Rec_001A5008 D_001A5008[];
extern struct List_001FDB00 D_001FDB00;
extern int D_001EC8F0;

void func_0012CA80(unsigned short slot, unsigned short value) {
    int i;

    if (D_001A5008[slot].count >= D_001A5008[slot].limit) {
        return;
    }
    for (i = 0; i < D_001A5008[slot].count; i++) {
        if (D_001A5008[slot].entries[i] == value) {
            return;
        }
    }
    D_001A5008[slot].entries[D_001A5008[slot].count] = value;
    D_001A5008[slot].count = D_001A5008[slot].count + 1;
}
