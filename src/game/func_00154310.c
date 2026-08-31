typedef struct {
    unsigned char data[0x40];
} Record;

extern Record D_002BDA40[];
extern Record D_002D3240[];
extern int func_00128B00(Record *left, Record *right);

unsigned short func_00154310(unsigned short index) {
    unsigned short slot;

    for (slot = 0x2C0; slot < 0x438; slot++) {
        if (func_00128B00(&D_002BDA40[slot], &D_002D3240[index]) == 0) {
            return slot;
        }
    }
    return 0xFFFF;
}
