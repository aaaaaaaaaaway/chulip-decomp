char D_001EC8C0 __attribute__((section(".sdata"))) = 0;
extern unsigned char D_001ED1DF;
extern int D_001ED1E4;
extern int D_001ED1E8;
extern int D_001F9DD0[];

void func_00117290(unsigned char enable, short *source) {
    int i;
    int *slot;
    int value;

    if (enable != 0) {
        slot = D_001F9DD0;
        for (i = 0x62; i >= 0; i--) {
            slot[0] = 0;
            slot[1] = 0;
            slot += 2;
        }
        value = *source;
        D_001ED1E4 = value;
        if (value != 0) {
            D_001ED1DF = 1;
        }
    } else {
        D_001ED1DF = 0;
    }
    D_001EC8C0 = 0;
    D_001ED1E8 = 0;
}
