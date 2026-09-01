typedef struct Quad { unsigned char b[0x10]; } Quad;
typedef union Vec { long long raw; float f[4]; } Vec;
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

void func_00155D08(unsigned short id, unsigned short index, int mode);
Node *func_00155AB0(unsigned short index);
void func_0018A680(void *dst, void *src);

unsigned short func_00155398(unsigned short index) {
    Entry *entry = D_002ABA40 + index;
    unsigned short id = index - 0x120;
    Item *item;
    Vec zero;

    zero.raw = 0;
    if (entry->u.p.owner == 0) {
        func_00155D08(id, index, 1);
        entry->id = id;
        entry->u.flags = (entry->u.flags | 4) & -2;
        entry->u.p.owner = func_00155AB0(index);
    }
    item = entry->u.p.owner->item;
    func_0018A680(&item->q10, &zero);
    item->x = 0.0f;
    item->y = 0.0f;
    item->z = 0.0f;
    return index;
}
