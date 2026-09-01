/* object_flags: -Wa,-G4 */
struct S_001205D0 { unsigned char pad_0x0[0xC]; float field_0xc; unsigned char pad_0x10[0x30]; };

struct Table_001205D0 { struct S_001205D0 *entries; int unused; };

extern struct Table_001205D0 D_001ED248;

void func_001205D0(int index, int value) {
    D_001ED248.entries[index].field_0xc = (float)value;
}
