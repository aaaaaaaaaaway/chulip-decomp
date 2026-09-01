struct Slot_001ED300 { unsigned char pad_0x0[0x1C]; unsigned char field_0x1C; unsigned char pad_0x1D[3]; };
struct Score_001A6998 {
    unsigned char pad_0x0[0x54];
    unsigned short field_0x54;
    unsigned short field_0x56;
    unsigned char pad_0x58[4];
    int field_0x5C;
    int field_0x60;
    unsigned char field_0x64;
    unsigned char field_0x65;
    unsigned short field_0x66;
};

extern struct Slot_001ED300 *D_001ED300;
extern struct Score_001A6998 D_001A6998;

void func_0012E5E8(void) {
    D_001A6998.field_0x54 = D_001ED300->field_0x1C;
    D_001A6998.field_0x56 = D_001ED300->field_0x1C;
    D_001A6998.field_0x5C = 0x64;
    D_001A6998.field_0x60 = 0x12C;
    D_001A6998.field_0x64 = 0;
    D_001A6998.field_0x66 = 0;
    D_001A6998.field_0x65 = 0;
}
