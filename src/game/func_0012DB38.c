struct Rec_001ED320 {
    unsigned char field_0x00[0x15];
    unsigned char field_0x15;
    unsigned short field_0x16;
    unsigned char field_0x18;
    unsigned char field_0x19;
    unsigned char field_0x1A;
    unsigned char field_0x1B;
    unsigned char field_0x1C;
    unsigned char field_0x1D;
    unsigned short field_0x1E;
    unsigned short field_0x20;
    unsigned short field_0x22;
};

extern struct Rec_001ED320 *D_001ED320;

void func_0012DB38(unsigned char index, unsigned short field, short value) {
    switch (field) {
    case 1:
        D_001ED320[index].field_0x16 = value;
        break;
    case 2:
        D_001ED320[index].field_0x19 = value;
        break;
    case 3:
        D_001ED320[index].field_0x1A = value;
        break;
    case 4:
        D_001ED320[index].field_0x18 = value;
        break;
    case 5:
        D_001ED320[index].field_0x15 = value;
        break;
    case 6:
        D_001ED320[index].field_0x1B = value;
        break;
    case 7:
        D_001ED320[index].field_0x1C = value;
        break;
    case 10:
        D_001ED320[index].field_0x20 = value;
        break;
    case 9:
        D_001ED320[index].field_0x1E = value;
        break;
    case 11:
        D_001ED320[index].field_0x22 = value;
        break;
    case 0:
    case 8:
        break;
    }
}
