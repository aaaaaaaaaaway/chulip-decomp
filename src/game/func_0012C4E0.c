struct List_001FDB00 { unsigned char count; unsigned char limit; unsigned char entries[0x200]; };

extern struct List_001FDB00 D_001FDB00;
extern int D_001EC8F0;

int func_0012C4E0(unsigned short index) {
    int i;

    for (i = index; i < D_001FDB00.limit - 1; i++) {
        D_001FDB00.entries[i] = D_001FDB00.entries[i + 1];
    }
    D_001EC8F0 = 1;
    D_001FDB00.count = D_001FDB00.count - 1;
    return 0;
}
