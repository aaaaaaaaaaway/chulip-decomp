/* object_flags: -Wa,-G4 */
struct Header_001A6998 {
    unsigned char pad_0x0[0x64];
    unsigned char field_0x64;
    unsigned char pad_0x65;
    unsigned short field_0x66;
};

struct Table_001ED300 { unsigned char *data; int unused; };

extern struct Header_001A6998 D_001A6998;
extern struct Table_001ED300 D_001ED300;

short func_0012F9E8(void) {
    return D_001ED300.data[D_001A6998.field_0x64 * 0x20 + 0x3D] - D_001A6998.field_0x66;
}
