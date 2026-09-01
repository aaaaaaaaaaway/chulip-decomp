struct Slot_001ED6C0 {
    unsigned char field_0x00[0x9A];
    short field_0x9A;
    short field_0x9C;
    short field_0x9E;
    short field_0xA0;
    short field_0xA2;
    short field_0xA4;
    unsigned char field_0xA6[0x1A];
};

extern struct Slot_001ED6C0 *D_001ED6C0;
extern unsigned int func_00173148(unsigned short id);

void func_00172CC8(unsigned short id, unsigned char field, int value) {
    unsigned int slot = func_00173148(id);

    if (slot == 0xFFFF) {
        return;
    }
    switch (field) {
    case 0x19:
        D_001ED6C0[slot].field_0x9A = value;
        break;
    case 0x1A:
        D_001ED6C0[slot].field_0xA2 = value;
        break;
    case 0x1B:
        D_001ED6C0[slot].field_0xA4 = value;
        break;
    case 0x1C:
        D_001ED6C0[slot].field_0x9C = value;
        break;
    case 0x1D:
        D_001ED6C0[slot].field_0xA0 = value;
        break;
    case 0x1E:
        D_001ED6C0[slot].field_0x9E = value;
        break;
    }
}
