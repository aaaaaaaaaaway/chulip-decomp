/* object_flags: -Wa,-G4 */
struct S_0012E570 { unsigned char pad_0x0[0x16]; unsigned short field_0x16; unsigned char pad_0x18[0xC]; };

struct Table_0012E570 { struct S_0012E570 *entries; int unused; };

extern struct Table_0012E570 D_001ED320;

void func_0012E570(unsigned char index, int unused, unsigned char bits) {
    if (bits == 0) {
        return;
    }
    D_001ED320.entries[index].field_0x16 = D_001ED320.entries[index].field_0x16 | bits;
}
