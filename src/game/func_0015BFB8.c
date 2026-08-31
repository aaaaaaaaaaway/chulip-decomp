typedef struct Owner {
    unsigned char pad[0x4];
    int field;
} Owner;

typedef struct {
    unsigned char pad[0x24];
    Owner *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

int func_0015BFB8(unsigned short index) {
    Entry *entry = D_002ABA40 + index;

    if (entry->owner == 0) {
        return 0;
    }
    return entry->owner->field;
}
