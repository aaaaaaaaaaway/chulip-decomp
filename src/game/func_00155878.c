typedef struct Quad { unsigned char b[0x10]; } Quad;
typedef struct Item { Quad q00; Quad q10; float x, y, z; } Item;
typedef struct Node { unsigned char pad[0x10]; Item *item; } Node;
typedef union Slot { long flags; struct { int lo; Node *owner; } p; } Slot;
typedef struct Entry {
    Quad quads[2];
    Slot u;
    unsigned char pad28[0xE];
    unsigned short id;
    unsigned char tail[0x8];
} Entry;

extern Entry D_002ABA40[];
extern Quad D_001A8BC0;

void func_0018A680(void *dst, void *src);

int func_00155878(unsigned short index) {
    Entry *entry = D_002ABA40 + index;
    Node *owner = entry->u.p.owner;
    long flags;

    if (owner != 0) {
        func_0018A680(&owner->item->q10, &D_001A8BC0);
    }
    flags = entry->u.flags;
    flags &= -0x11;
    flags &= -0x5;
    flags &= -0x2;
    entry->u.flags = flags;
    func_0018A680(&D_002ABA40[index].quads[1], &D_001A8BC0);
    func_0018A680(&(D_002ABA40 + index)->quads[0], &D_001A8BC0);
    return 0;
}
