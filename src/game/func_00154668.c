typedef struct {
    unsigned char pad[0x20];
    volatile long long low : 8;
    volatile long long value : 32;
    volatile long long high : 24;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

int func_00154668(unsigned short index) {
    Entry *entry = D_002ABA40 + index;

    return (entry->value & 1) << 5;
}
