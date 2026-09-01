typedef struct Node { unsigned char pad[0x10]; void *item; } Node;
typedef union Slot {
    long flags;
    struct { int lo; Node *owner; } p;
} Slot;
typedef struct Entry {
    unsigned char pad[0x20];
    Slot u;
    unsigned char tail[0x18];
} Entry;
extern Entry D_002ABA40[];

void func_00158B40(unsigned short index, unsigned char value) {
    Entry *e;
    int z;
    if (index == 0xFFFF) return;
    e = D_002ABA40 + index;
    e->u.flags = (e->u.flags & -3) | ((long)(value & 1) << 1);
    if (index == 0) {
        z = (value == 0);
        D_002ABA40[0].u.flags = (D_002ABA40[0].u.flags & -2) | z;
        return;
    }
    if (value == 1) e->u.flags &= -2;
}
