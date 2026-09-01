typedef struct Quad { unsigned char b[0x10]; } Quad;
typedef struct Item { Quad q00; Quad q10; float x, y, z, w; } Item;
typedef struct Node { unsigned char pad[0x10]; Item *item; } Node;
typedef union Slot {
    long flags;
    struct { int lo; Node *owner; } p;
    struct { volatile long l : 8; volatile long v : 32; volatile long h : 24; } b8;
    struct { volatile long l : 12; volatile long v : 32; volatile long h : 20; } b12;
} Slot;
typedef struct Entry {
    float x, y, z, w;
    Quad q10;
    Slot u;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

Node *func_00155AB0(unsigned short index);
void func_0015C7E0(unsigned short index);
void func_0015BE88(unsigned short index, int a, int b);
void func_0018A680(void *dst, void *src);

void func_001548C0(unsigned short index) {
    Node *node = func_00155AB0(index);
    Entry *entry = D_002ABA40 + index;
    Item *item;

    entry->u.p.owner = node;
    if (index < 0x1C0) {
        func_0015C7E0(index);
    }
    if ((int)entry->u.b8.v & 1) {
        func_0015BE88(index, 2, 1);
    }
    if ((int)entry->u.b12.v & 1) {
        func_0015BE88(index, 1, 1);
    }
    entry->u.flags |= 4;
    item = entry->u.p.owner->item;
    func_0018A680(&item->q10, &D_002ABA40[index].q10);
    item->x = 0.0f;
    item->y = entry->y;
    item->z = 0.0f;
    item->w = 1.0f;
}
