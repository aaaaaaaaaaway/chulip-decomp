struct S_0012F570 { unsigned short field_0x0; unsigned char pad[0x2A2]; };

extern struct S_0012F570 D_001A5718[];

unsigned short func_0012F570(unsigned char index) {
    return D_001A5718[index].field_0x0;
}
