/* object_flags: -Wa,-G4 */
struct Item_001FC450 {
    int field_0x0;
    short field_0x4;
    short field_0x6;
    short field_0x8;
    short field_0xa;
    int field_0xc;
    short field_0x10;
    short field_0x12;
    int field_0x14;
};

extern struct Item_001FC450 D_001FC450[];
extern int D_001ED270;

void func_00126440(void) {
    int i;

    D_001ED270 = 0;
    for (i = 0; i < 100; i++) {
        D_001FC450[i].field_0x0 = 0;
        D_001FC450[i].field_0x14 = 0;
        D_001FC450[i].field_0x10 = 0;
        D_001FC450[i].field_0x12 = 0;
        D_001FC450[i].field_0x4 = 0;
        D_001FC450[i].field_0x6 = 0;
        D_001FC450[i].field_0x8 = 0;
        D_001FC450[i].field_0xa = 0;
        D_001FC450[i].field_0xc = 0;
    }
}
