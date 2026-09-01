struct Rec_001ED2E0 {
    unsigned char field_0x00[0x15];
    unsigned char field_0x15;
    unsigned char field_0x16;
    unsigned char field_0x17;
    unsigned char field_0x18;
    unsigned char field_0x19;
    unsigned short field_0x1A;
    unsigned char field_0x1C;
    unsigned char field_0x1D;
    unsigned short field_0x1E;
    unsigned short field_0x20;
    unsigned short field_0x22;
    unsigned char field_0x24;
    unsigned char field_0x25;
    unsigned short field_0x26;
    unsigned char field_0x28[0x8];
};

extern struct Rec_001ED2E0 *D_001ED2E0;

void func_0012D708(unsigned char index, unsigned char field, short value) {
    switch (field) {
    case 1:
        D_001ED2E0[index].field_0x15 = value;
        break;
    case 2:
        D_001ED2E0[index].field_0x16 = value;
        break;
    case 5:
        D_001ED2E0[index].field_0x1A = value;
        break;
    case 3:
        D_001ED2E0[index].field_0x17 = value;
        break;
    case 4:
        D_001ED2E0[index].field_0x18 = value;
        break;
    case 6:
        D_001ED2E0[index].field_0x1C = value;
        break;
    case 7:
        D_001ED2E0[index].field_0x1E = value;
        break;
    case 8:
        D_001ED2E0[index].field_0x20 = value;
        break;
    case 9:
        D_001ED2E0[index].field_0x22 = value;
        break;
    case 10:
        D_001ED2E0[index].field_0x24 = value;
        break;
    case 13:
        D_001ED2E0[index].field_0x26 = value;
        break;
    case 11:
    case 12:
        break;
    }
}
