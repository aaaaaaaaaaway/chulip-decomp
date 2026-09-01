struct Rec_001ED320 {
    unsigned char field_0x00[0x15];
    unsigned char field_0x15;
    unsigned short field_0x16;
    unsigned char field_0x18;
    unsigned char field_0x19;
    unsigned char field_0x1A;
    unsigned char field_0x1B;
    unsigned char field_0x1C;
    unsigned char field_0x1D[0x7];
};

extern struct Rec_001ED320 *D_001ED320;

short func_0012DDD0(unsigned char index, unsigned short field, short value) {
    switch (field) {
    case 1:
        return D_001ED320[index].field_0x16 | value;
    case 2:
        return D_001ED320[index].field_0x19 + value;
    case 3:
        return D_001ED320[index].field_0x1A + value;
    case 5:
        return D_001ED320[index].field_0x15 + value;
    case 6:
        return D_001ED320[index].field_0x1B + value;
    case 7:
        return D_001ED320[index].field_0x1C + value;
    case 0:
    case 4:
        break;
    }
    return -1;
}
