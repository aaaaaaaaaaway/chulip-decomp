struct Record00203C20 {
    int field_0x0;
    unsigned char pad_0x4[0xC];
    int field_0x10;
    unsigned short field_0x14;
    unsigned short field_0x16;
    unsigned short field_0x18;
    unsigned short field_0x1A;
    unsigned char pad_0x1C[8];
};

extern struct Record00203C20 D_00203C20[];

void func_001386E8(int index, short *values) {
    if (values[0] != -1) {
        (D_00203C20 + index)->field_0x14 = values[0];
    }
    if (values[1] != -1) {
        (D_00203C20 + index)->field_0x16 = values[1];
    }
    if (values[2] != -1) {
        (D_00203C20 + index)->field_0x18 = values[2];
    }
    if (values[3] != -1) {
        (D_00203C20 + index)->field_0x1A = values[3];
    }
    (D_00203C20 + index)->field_0x10 &= ~2;
}
