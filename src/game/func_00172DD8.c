struct Slot_001ED6C0 {
    short field_0x00;
    short field_0x02;
    short field_0x04;
    short field_0x06;
    unsigned char field_0x08[0x66];
    short field_0x6E;
    short field_0x70;
    unsigned char field_0x72[0x26];
    short field_0x98;
    short field_0x9A;
    short field_0x9C;
    short field_0x9E;
    short field_0xA0;
    short field_0xA2;
    short field_0xA4;
    unsigned char field_0xA6[0xF];
    unsigned char field_0xB5;
    unsigned char field_0xB6;
    unsigned char field_0xB7[0x9];
};

extern struct Slot_001ED6C0 *D_001ED6C0;
extern unsigned int func_00173148(unsigned short id);

int func_00172DD8(unsigned short id, unsigned char field) {
    unsigned int slot = func_00173148(id);

    if (slot == 0xFFFF) {
        return 0;
    }
    switch (field) {
    case 2:
        return D_001ED6C0[slot].field_0x70;
    case 3:
        return D_001ED6C0[slot].field_0xB6;
    case 1:
        return D_001ED6C0[slot].field_0x6E;
    case 22:
        return D_001ED6C0[slot].field_0xB5;
    case 17:
        return D_001ED6C0[slot].field_0x00;
    case 18:
        return D_001ED6C0[slot].field_0x02;
    case 19:
        return D_001ED6C0[slot].field_0x04;
    case 20:
        return D_001ED6C0[slot].field_0x06;
    case 25:
        return D_001ED6C0[slot].field_0x9A;
    case 26:
        return D_001ED6C0[slot].field_0xA2;
    case 27:
        return D_001ED6C0[slot].field_0xA4;
    case 28:
        return D_001ED6C0[slot].field_0x9C;
    case 29:
        return D_001ED6C0[slot].field_0xA0;
    case 30:
        return D_001ED6C0[slot].field_0x9E;
    case 21:
        return D_001ED6C0[slot].field_0x98;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 23:
    case 24:
        break;
    }
    return -1;
}
