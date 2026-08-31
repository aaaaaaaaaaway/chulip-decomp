/* object_flags: -Wa,-G4 */
struct Item_001FC450 { unsigned char pad_0x0[0xC]; int field_0xc; unsigned char pad_0x10[0x8]; };

struct Count_001ED270 { unsigned int value; int unused; };

extern struct Item_001FC450 D_001FC450[];
extern struct Count_001ED270 D_001ED270;

int func_001268B0(void) {
    int result = -1;
    int i;

    for (i = 0; i < D_001ED270.value; i++) {
        if (D_001FC450[i].field_0xc == 0) {
            result = i;
            break;
        }
    }
    return result;
}
