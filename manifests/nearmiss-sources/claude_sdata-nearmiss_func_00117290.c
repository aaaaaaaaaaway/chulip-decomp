typedef struct Entry {
    int first;
    int second;
} Entry;

char D_001EC8C0 __attribute__((section(".sdata"))) = 0;

extern Entry D_001F9DD0[];
extern signed char D_001ED1DF;
extern int D_001ED1E4;
extern int D_001ED1E8;

void func_00117290(unsigned char on, short *source) {
    int i;
    int value;

    if (on) {
        for (i = 0; i < 99; i++) {
            D_001F9DD0[i].first = 0;
            D_001F9DD0[i].second = 0;
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
