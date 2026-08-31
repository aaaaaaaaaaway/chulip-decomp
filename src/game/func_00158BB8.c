typedef struct {
    unsigned char pad[0x20];
    long flags;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_00158BB8(unsigned short index, unsigned char value) {
    Entry *entry = D_002ABA40 + index;
    long flags = entry->flags;
    int bit = (int)(flags >> 2) & 1;

    if (bit == 1) {
        entry->flags = (flags & -2) | (value & 1);
    }
}
