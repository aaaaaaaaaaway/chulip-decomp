struct Rec_001ED320 {
    unsigned char field_0x00[0x15];
    unsigned char field_0x15;
    short field_0x16;
    unsigned char field_0x18;
    unsigned char field_0x19;
    unsigned char field_0x1A;
    unsigned char field_0x1B;
    unsigned char field_0x1C;
    unsigned char field_0x1D;
    short field_0x1E;
    short field_0x20;
    short field_0x22;
};

extern struct Rec_001ED320 *D_001ED320;
extern int func_00192940(void *destination, void *source);

int func_0012D998(unsigned char index, unsigned short field, void *buffer) {
    switch (field) {
    case 0:
        if (buffer != 0) {
            func_00192940(buffer, &D_001ED320[index]);
        }
        break;
    case 1:
        return D_001ED320[index].field_0x16;
    case 2:
        return D_001ED320[index].field_0x19;
    case 3:
        return D_001ED320[index].field_0x1A;
    case 4:
        return D_001ED320[index].field_0x18;
    case 5:
        return D_001ED320[index].field_0x15;
    case 6:
        return D_001ED320[index].field_0x1B;
    case 7:
        return D_001ED320[index].field_0x1C;
    case 8:
        return D_001ED320[index].field_0x1D;
    case 9:
        return D_001ED320[index].field_0x1E;
    case 10:
        return D_001ED320[index].field_0x20;
    case 11:
        return D_001ED320[index].field_0x22;
    }
    return -1;
}
