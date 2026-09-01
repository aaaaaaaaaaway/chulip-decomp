extern unsigned short D_001ED088;
extern int D_001ED08C;

void func_00105878(void) {
    int i;
    int off;
    unsigned short *p;
    unsigned short v;

    i = 0;
    if (D_001ED088 != 0) {
        off = 0;
        do {
            *(unsigned short *)(off + D_001ED08C) &= 0x7FFF;
            p = (unsigned short *)(off + D_001ED08C);
            v = *p;
            if (v & 0x400) {
                if (v & 0x800) { *p = v | 0x8000; } else { *p = v & 0x7FFF; }
            } else {
                if (v & 0x200) { *p = v | 0x8000; } else { *p = v & 0x7FFF; }
            }
            i++;
            off += 0x2C;
        } while (i < D_001ED088);
    }
}
