/* object_flags: -Wa,-G4 */
struct Target_001ED298 { short field_0x0; short field_0x2; short field_0x4; short field_0x6; };

extern unsigned char D_001EC8D4;
extern struct Target_001ED298 D_001ED298;

void func_00127270(short x, short y) {
    if (x == 0) {
        D_001EC8D4 = 1;
    } else {
        D_001ED298.field_0x2 = x;
        D_001ED298.field_0x4 = y;
        D_001EC8D4 = 0;
    }
}
