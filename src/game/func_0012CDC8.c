struct Actor_001ED310 {
    unsigned char field_0x00[0x20];
    unsigned char field_0x20[0x40];
    unsigned char field_0x60;
    unsigned char field_0x61;
    unsigned short field_0x62;
    unsigned short field_0x64;
    unsigned short field_0x66;
    unsigned short field_0x68;
    unsigned short field_0x6A;
    int field_0x6C;
    unsigned char field_0x70[0x8];
    short field_0x78;
    short field_0x7A;
    int field_0x7C;
};

extern struct Actor_001ED310 *D_001ED310;

void func_0012CDC8(int index, unsigned char field, int value) {
    switch (field) {
    case 8:
        (D_001ED310 + index)->field_0x68 = value;
        break;
    case 7:
        (D_001ED310 + index)->field_0x66 = value;
        break;
    case 9:
        (D_001ED310 + index)->field_0x6C = value;
        break;
    case 11:
        (D_001ED310 + index)->field_0x78 = value;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 10:
        break;
    }
}
