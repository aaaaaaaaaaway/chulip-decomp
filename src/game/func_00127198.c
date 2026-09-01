extern short D_001ED2C0;
extern short D_001ED2C4;

void func_00127198(short arg0, short arg1) {
    D_001ED2C4 = arg0;
    if (D_001ED2C0 > 0) {
        D_001ED2C0 = arg1;
    } else {
        D_001ED2C0 = -arg1;
    }
}
