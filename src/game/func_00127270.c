/* object_flags: -Wa,-G4 */

extern unsigned char D_001EC8D4;
extern short D_001ED29A;
extern short D_001ED29C;

void func_00127270(short x, short y) {
    if (x == 0) {
        D_001EC8D4 = 1;
    } else {
        D_001ED29A = x;
        D_001ED29C = y;
        D_001EC8D4 = 0;
    }
}
