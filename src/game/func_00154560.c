typedef struct {
    unsigned char pad[0x20];
    union {
        long flags;
        struct {
            int pad;
            void *owner;
        } s;
    } u;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

int func_00154560(unsigned short index) {
    Entry *entry;
    int bit;

    if (index == 0xFFFF) {
        return 0;
    }
    entry = D_002ABA40 + index;
    if (entry->u.s.owner != 0) {
        bit = (int)(entry->u.flags << 14 >> 32) & 1;
        if (bit == 1) {
            return 1;
        }
    }
    return 0;
}
