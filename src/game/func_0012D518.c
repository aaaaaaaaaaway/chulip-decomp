/* object_flags: -Wa,-G4 */
struct S_0012D518 { unsigned char pad_0x0[0x2C]; int field_0x2c; };

struct Table_0012D518 { struct S_0012D518 *entries; int unused; };

extern struct Table_0012D518 D_001ED2E0;

void func_0012D518(unsigned char index, int *out) {
    if (out != 0) {
        *out = D_001ED2E0.entries[index].field_0x2c;
    }
}
