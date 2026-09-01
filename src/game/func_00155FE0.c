typedef struct Vec4 { float x, y, z; int w; } Vec4;

typedef struct Item {
    unsigned char pad00[0x10];
    unsigned char q10[0x10];
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
    unsigned char pad00[0x10];
    unsigned char q10[0x10];
    Slot u;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_0018A5F0(void *dst, const void *a, const void *b);

void func_00155FE0(unsigned short index, Vec4 *v) {
    Node *owner;
    Item *item;

    if (index == 0xFFFF) return;
    owner = D_002ABA40[index].u.p.owner;
    if (owner == 0) {
        func_0018A5F0(&D_002ABA40[index].q10, &D_002ABA40[index].q10, v);
        return;
    }
    item = owner->item;
    v->w = 0;
    func_0018A5F0(&item->q10, &item->q10, v);
    func_0018A5F0(&D_002ABA40[index].q10, &D_002ABA40[index].q10, v);
}
