typedef struct {
    unsigned char pad[0x20];
    volatile long long low : 17;
    volatile long long value : 32;
    volatile long long high : 15;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

int func_00154638(unsigned short index) {
    Entry *entry = D_002ABA40 + index;
    int flag = entry->value & 1;

    return flag ? -1 : 0;
}
