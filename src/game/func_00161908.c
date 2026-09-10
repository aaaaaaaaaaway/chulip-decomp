struct Pair16 {
    unsigned short lo;
    unsigned short hi;
};

struct PairTable {
    struct Pair16 entry[4];
};

extern struct PairTable D_001E9CB0;

int func_00161908(unsigned char *state) {
    struct PairTable table;
    int result;
    int i;

    table = D_001E9CB0;
    result = 0;
    for (i = 2; i < 4; i++) {
        unsigned char value = state[i];
        if (value >= 0xFF) {
            result |= table.entry[i].lo;
        } else if (value < 2) {
            result |= table.entry[i].hi;
        }
    }
    return result;
}
