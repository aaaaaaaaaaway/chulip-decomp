typedef struct Slot {
    unsigned char pad[0x21];
    unsigned char state;
    unsigned char tail[0x1E];
} Slot;

typedef struct {
    unsigned char pad[0x20];
    volatile long long low : 6;
    volatile long long value : 32;
    volatile long long high : 26;
    unsigned char pad28[0xE];
    unsigned short slot;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];
extern Slot D_002BDA40[];

unsigned char *func_001545B8(unsigned short index) {
    int flag = (D_002ABA40 + index)->value & 1;

    if (flag) {
        return &(D_002BDA40 + (D_002ABA40 + index)->slot)->state;
    }
    return 0;
}
