typedef struct { int f0, f4, f8, fC, f10, f14, f18, f1C; } Entry;

extern Entry D_001FA0E8[];
extern int D_001EC8C4;

void func_00117A48(void) {
    Entry *entry = D_001FA0E8;
    int value = 0;
    int i = 7;

    do {
        entry->f10 = value;
        entry->f0 = 0;
        entry->f4 = 0;
        entry->f8 = 0;
        entry->fC = 0;
        entry->f18 = 0;
        entry->f1C = 0;
        entry->f14 = 0;
        value += 0x5A;
        entry++;
    } while (--i >= 0);
    D_001EC8C4 = 0;
}
