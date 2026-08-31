typedef struct {
    unsigned char pad[0x20];
    union {
        long flags;
        struct {
            int bits;
            void *owner;
        } fields;
    } state;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];
extern void *func_00155B08(unsigned short index);

void func_001549B0(unsigned short index) {
    void *owner = func_00155B08(index);
    Entry *entry = D_002ABA40 + index;

    entry->state.fields.owner = owner;
    if (owner != 0) {
        entry->state.flags |= 4;
    }
}
