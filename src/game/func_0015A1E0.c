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
extern void func_0015A4E0(int index);

void func_0015A1E0(void) {
    Entry *entry = D_002ABA40;
    int index = 0;

    do {
        if (entry->state.fields.owner != 0) {
            int bit = (int)(entry->state.flags >> 2) & 1;

            if (bit == 0) {
                func_0015A4E0(index);
            }
        }
        index++;
        entry++;
    } while (index < 0x480);
}
