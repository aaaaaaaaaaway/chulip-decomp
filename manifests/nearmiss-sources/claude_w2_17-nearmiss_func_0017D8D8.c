extern unsigned int D_001ECF90;

unsigned int func_0017D8D8(unsigned int size, int mode, int flag) {
    unsigned int base;

    if (flag != 0) {
        if (mode == -1) {
            base = D_001ECF90 - size;
        } else if (mode == 1) {
            base = ((D_001ECF90 - size) >> 5) << 5;
        } else {
            return 0;
        }
        D_001ECF90 = base;
        base = D_001ECF90 > 0x1DBF ? D_001ECF90 : 0x1DC0;
    } else {
        base = ((0x1DC0 - size) >> 5) << 5;
    }
    return base;
}
