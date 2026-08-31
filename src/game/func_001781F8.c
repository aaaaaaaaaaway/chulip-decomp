struct TableRef { unsigned char *entries; char pad[4]; };
extern short D_001ECED0;
extern struct TableRef D_001ED7D0;

int func_001781F8(unsigned short key) {
    unsigned short i;

    for (i = 0; i < D_001ECED0; i++) {
        if (D_001ED7D0.entries[i * 4 + 1] == key) {
            return i;
        }
    }
    return 0xFFFF;
}
