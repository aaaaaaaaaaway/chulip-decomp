struct S_0012F590 { unsigned short field_0x0; unsigned char field_0x2; unsigned char pad[0x2A1]; };

extern struct S_0012F590 D_001A5718[];

void func_0012F590(unsigned char index, unsigned short value, unsigned char flag) {
    D_001A5718[index].field_0x0 = value;
    D_001A5718[index].field_0x2 = flag;
}
