extern unsigned short D_002AAF00[];

void func_0015A188(unsigned short value) {
    unsigned short *base = D_002AAF00;
    unsigned short *slot = base;
    int i;

    for (i = 0; i < 0x1E1; i++) {
        if (*slot == 0xFFFF) {
            break;
        }
        slot++;
    }
    base[i] = value;
    base[i + 1] = 0xFFFF;
}
