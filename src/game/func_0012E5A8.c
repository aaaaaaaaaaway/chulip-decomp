/* object_flags: -Wa,-G4 */
struct S_0012E5A8 { unsigned char pad_0x0[0x16]; unsigned short field_0x16; unsigned char pad_0x18[0xC]; };

struct Table_0012E5A8 { struct S_0012E5A8 *entries; int unused; };

extern struct Table_0012E5A8 D_001ED320;

int func_0012E5A8(unsigned char index, unsigned short mask) {
    return (D_001ED320.entries[index].field_0x16 & mask) != 0;
}
