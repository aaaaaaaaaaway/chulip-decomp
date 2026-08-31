typedef struct Owner {
    unsigned char pad[0x10];
    int handle;
} Owner;

typedef struct {
    unsigned char pad[0x24];
    Owner *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];
extern void func_00133628(int handle, unsigned char value);

void func_00158A00(unsigned short index, unsigned char value) {
    Entry *entry = D_002ABA40 + index;

    if (entry->owner != 0) {
        func_00133628(entry->owner->handle, value);
    }
}
