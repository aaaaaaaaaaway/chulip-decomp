struct List_001FDB00 { unsigned char count; unsigned char limit; unsigned char entries[0x200]; };
struct Entity_001ED310 { unsigned char pad_0x0[0x62]; unsigned short field_0x62; unsigned char pad_0x64[8]; int field_0x6C; unsigned char pad_0x70[0x10]; };
struct Score_001A6998 { unsigned char pad_0x0[0x5C]; int field_0x5C; };

extern struct List_001FDB00 D_001FDB00;
extern int D_001ED310;
extern struct Score_001A6998 D_001A6998;

int func_0012C630(int unused, unsigned short index) {
    struct Entity_001ED310 *entity;
    unsigned int total;

    entity = (struct Entity_001ED310 *)(D_001FDB00.entries[index] * 0x80 + D_001ED310);
    if ((entity->field_0x62 & 4) != 0) {
        return 1;
    }
    total = D_001A6998.field_0x5C + entity->field_0x6C;
    if (total > 0x7FFF) {
        D_001A6998.field_0x5C = 0x7FFF;
    } else {
        D_001A6998.field_0x5C = total;
    }
    return 0;
}
