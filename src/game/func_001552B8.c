typedef struct Item {
    unsigned char pad00[0x10];
    unsigned char q10[0x10];
    float f20;
    float f24;
    float f28;
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

void func_00155D08(unsigned short id, unsigned short index, unsigned char flag);
Node *func_00155AB0(unsigned short index);
void func_0018A680(void *dst, const void *src);

void func_001552B8(unsigned short id, unsigned short index, const void *src,
                   float value, unsigned char flag) {
    Entry *e = D_002ABA40 + index;
    Item *item;

    if (e->u.p.owner == 0) {
        func_00155D08(id, index, flag);
        e->u.flags |= 4;
        e->slot = id;
        e->u.flags |= 0x400;
        e->u.p.owner = func_00155AB0(index);
    }
    item = e->u.p.owner->item;
    func_0018A680(&item->q10, src);
    func_0018A680(&D_002ABA40[index].q10, src);
    item->f24 = value;
    item->f20 = 0.0f;
    item->f28 = 0.0f;
}
