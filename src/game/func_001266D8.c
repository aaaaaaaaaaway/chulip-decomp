/* object_flags: -Wa,-G4 */
struct Item_001FC450 {
    int field_0x0;
    unsigned char pad_0x4[0x8];
    int field_0xc;
    unsigned char pad_0x10[0x8];
};

struct Count_001ED270 { unsigned int value; int unused; };

extern struct Item_001FC450 D_001FC450[];
extern struct Count_001ED270 D_001ED270;

int func_001266D8(unsigned short key) {
    int result = -1;
    int i;

    for (i = 0; i < D_001ED270.value; i++) {
        if (D_001FC450[i].field_0x0 == key) {
            D_001FC450[i].field_0xc = 1;
            result = i;
        }
    }
    return result;
}
