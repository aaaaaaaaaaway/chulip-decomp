struct Rec_001ED2E0 {
    unsigned char field_0x00[0x15];
    unsigned char field_0x15;
    unsigned char field_0x16;
    unsigned char field_0x17;
    unsigned char field_0x18;
    unsigned char field_0x19;
    short field_0x1A;
    unsigned char field_0x1C;
    unsigned char field_0x1D;
    short field_0x1E;
    short field_0x20;
    short field_0x22;
    unsigned char field_0x24;
    unsigned char field_0x25;
    short field_0x26;
    unsigned char field_0x28[0x8];
};

extern struct Rec_001ED2E0 *D_001ED2E0;
extern int func_0015DE90(void *destination, void *source);

int func_0012D548(unsigned char index, unsigned char field, void *buffer) {
    switch (field) {
    case 0:
        if (buffer != 0) {
            func_0015DE90(buffer, &D_001ED2E0[index]);
        }
        break;
    case 1:
        return D_001ED2E0[index].field_0x15;
    case 2:
        return D_001ED2E0[index].field_0x16;
    case 5:
        return D_001ED2E0[index].field_0x1A;
    case 3:
        return D_001ED2E0[index].field_0x17;
    case 4:
        return D_001ED2E0[index].field_0x18;
    case 6:
        return D_001ED2E0[index].field_0x1C;
    case 7:
        return D_001ED2E0[index].field_0x1E;
    case 8:
        return D_001ED2E0[index].field_0x20;
    case 9:
        return D_001ED2E0[index].field_0x22;
    case 10:
        return D_001ED2E0[index].field_0x24;
    case 11:
        return D_001ED2E0[index].field_0x25;
    case 13:
        return D_001ED2E0[index].field_0x26;
    case 12:
        break;
    }
    return 0;
}
