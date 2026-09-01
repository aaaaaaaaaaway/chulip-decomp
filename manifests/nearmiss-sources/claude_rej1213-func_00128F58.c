extern unsigned char D_001FDD30[];

unsigned char func_00128F58(unsigned char row) {
    unsigned char i = 0;

    while (D_001FDD30[row * 0x100 + i * 2] != 0x80) {
        if (i >= 0xFF) {
            break;
        }
        i = i + 1;
    }
    return i;
}
