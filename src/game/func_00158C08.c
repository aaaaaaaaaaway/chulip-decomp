typedef struct {
    unsigned char pad[0x20];
    long flags;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

extern void func_00158BB8(unsigned short index, unsigned char value);

void func_00158C08(unsigned short index, unsigned char value) {
    Entry *entry;

    func_00158BB8(index, value);
    entry = D_002ABA40 + index;
    entry->flags = (entry->flags & -0x80001) | ((long)(value & 1) << 19);
}
