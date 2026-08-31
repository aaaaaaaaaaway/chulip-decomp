/* object_flags: -Wa,-G4 */
struct Entry_0012D878 { unsigned char pad_0x0[0x1A]; unsigned short field_0x1a; unsigned char pad_0x1c[0x14]; };

struct Table_001ED2E0 { struct Entry_0012D878 *entries; int unused; };

extern struct Table_001ED2E0 D_001ED2E0;

void func_0012D878(unsigned char index, unsigned char op, short mask) {
    if (op == 5) {
        if (mask & 0x8000) {
            D_001ED2E0.entries[index].field_0x1a = D_001ED2E0.entries[index].field_0x1a & mask;
        } else {
            D_001ED2E0.entries[index].field_0x1a = D_001ED2E0.entries[index].field_0x1a | mask;
        }
    }
}
