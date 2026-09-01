struct List_001FDB00 { unsigned char count; unsigned char limit; unsigned char entries[0x200]; };

extern struct List_001FDB00 D_001FDB00;
extern int D_001EC8F0;

void func_0012C728(unsigned short value) {
    int i;
    int j;

    if (D_001FDB00.count == 0) {
        return;
    }
    for (i = 0; i < D_001FDB00.count; i++) {
        if (D_001FDB00.entries[i] == value) {
            break;
        }
    }
    if (i < D_001FDB00.count) {
        for (j = i; j < D_001FDB00.count - 1; j++) {
            D_001FDB00.entries[j] = D_001FDB00.entries[j + 1];
        }
        D_001EC8F0 = 1;
        D_001FDB00.count = D_001FDB00.count - 1;
    }
}
