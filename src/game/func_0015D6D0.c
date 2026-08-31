typedef struct {
    unsigned char pad[0x24];
    void *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];
extern void func_00101020(void *owner);

int func_0015D6D0(void) {
    unsigned short index;

    for (index = 0x1C0; index < 0x3A0; index++) {
        Entry *entry = D_002ABA40 + index;

        if (entry->owner != 0) {
            func_00101020(entry->owner);
        }
    }
    return -1;
}
