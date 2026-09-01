struct Profile_001A6998 {
    char field_0x00[0x54];
    unsigned short field_0x54;
    unsigned short field_0x56;
    unsigned short field_0x58;
    unsigned short field_0x5A;
    int field_0x5C;
    int field_0x60;
    unsigned char field_0x64;
    unsigned char field_0x65;
    unsigned short field_0x66;
};

extern struct Profile_001A6998 D_001A6998;

void func_0012E390(unsigned short field, int amount) {
    int total;

    switch (field) {
    case 1:
        total = D_001A6998.field_0x54 + amount;
        if (total < 0) {
            D_001A6998.field_0x54 = 0;
        } else {
            D_001A6998.field_0x54 = total;
        }
        break;
    case 2:
        if (D_001A6998.field_0x54 + amount < 0) {
            D_001A6998.field_0x56 = 0;
        } else {
            D_001A6998.field_0x56 = D_001A6998.field_0x56 + amount;
        }
        break;
    case 3:
        D_001A6998.field_0x58 = D_001A6998.field_0x58 + amount;
        break;
    case 4:
        D_001A6998.field_0x5A = D_001A6998.field_0x5A + amount;
        break;
    case 5:
        total = D_001A6998.field_0x5C + amount;
        if (0x7FFF < (unsigned int)total) {
            D_001A6998.field_0x5C = 0x7FFF;
        } else {
            D_001A6998.field_0x5C = total;
        }
        break;
    case 6:
        D_001A6998.field_0x60 = D_001A6998.field_0x60 + amount;
        break;
    case 7:
        D_001A6998.field_0x64 = D_001A6998.field_0x64 + amount;
        break;
    case 9:
        D_001A6998.field_0x66 = D_001A6998.field_0x66 + amount;
        break;
    case 0:
    case 8:
        break;
    }
}
