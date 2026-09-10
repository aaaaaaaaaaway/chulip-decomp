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
extern int func_00133628(int handle, int value, void *out);

void func_00158A00(unsigned short index, unsigned char value, void *out) {
    Entry *entry = D_002ABA40 + index;

    if (entry->owner != 0) {
        func_00133628(entry->owner->handle, value, out);
    }
}
