typedef struct Item {
    unsigned char pad[0x20];
    float v[3];
    float f2C;
} Item;

typedef struct Node {
    unsigned char pad[0x10];
    Item *item;
} Node;

typedef union Slot {
    long flags;
    struct { int lo; Node *owner; } p;
} Slot;

typedef struct Entry {
    float f[4];
    unsigned char q10[0x10];
    Slot u;
    unsigned char pad28[0xC];
    unsigned short id;
    unsigned short slot;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];
unsigned short func_00155800(unsigned short id, unsigned short index) {
    Entry *e = D_002ABA40 + index;

    e->u.flags |= 4;
    if (e->u.p.owner != 0) {
        e->u.flags &= ~0x20;
    } else {
        e->u.flags |= 0x20;
    }
    (D_002ABA40 + index)->id = id;
    (D_002ABA40 + index)->u.flags &= ~0x10;
    return index;
}
