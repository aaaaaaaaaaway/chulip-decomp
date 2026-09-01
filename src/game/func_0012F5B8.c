struct Rec_001ED2F0 {
    unsigned char field_0x0;
    unsigned char field_0x1;
    unsigned short field_0x2;
    unsigned short field_0x4;
    unsigned short field_0x6;
    int field_0x8;
};

extern struct Rec_001ED2F0 *D_001ED2F0;

int func_0012F5B8(unsigned short index, unsigned char field) {
    switch (field) {
    case 2:
        return D_001ED2F0[index].field_0x0;
    case 3:
        return D_001ED2F0[index].field_0x8;
    case 0:
        return D_001ED2F0[index].field_0x2;
    case 5:
        return D_001ED2F0[index].field_0x4;
    case 6:
        return D_001ED2F0[index].field_0x6;
    case 1:
    case 4:
        break;
    }
    return 0;
}
