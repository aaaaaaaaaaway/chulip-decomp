/* object_flags: -Wa,-G4 */
struct Header_001A6998 {
    unsigned char pad_0x0[0x54];
    unsigned short field_0x54;
    unsigned short field_0x56;
    unsigned char pad_0x58[0x4];
    int field_0x5c;
    int field_0x60;
    unsigned char field_0x64;
    unsigned char field_0x65;
    unsigned short field_0x66;
};

struct Source_001ED300 { unsigned char *data; int unused; };

extern struct Header_001A6998 D_001A6998;
extern struct Source_001ED300 D_001ED300;

void func_0012E5E8(void) {
    D_001A6998.field_0x54 = D_001ED300.data[0x1C];
    D_001A6998.field_0x5c = 0x64;
    D_001A6998.field_0x56 = D_001ED300.data[0x1C];
    D_001A6998.field_0x60 = 0x12C;
    D_001A6998.field_0x65 = 0;
    D_001A6998.field_0x64 = 0;
    D_001A6998.field_0x66 = 0;
}
