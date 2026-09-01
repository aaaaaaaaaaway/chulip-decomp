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

unsigned short func_00155738(unsigned short id, unsigned short index,
                             const void *src, float value) {
    Entry *e = D_002ABA40 + index;
    Entry *p;

    e->u.flags |= 4;
    if (e->u.p.owner != 0) {
        e->u.flags &= ~0x20;
    } else {
        e->u.flags |= 0x20;
    }
    p = D_002ABA40 + index;
    p->id = id;
    p->u.flags &= ~0x10;
    func_0018A680(&D_002ABA40[index].q10, src);
    p->f[0] = 0.0f;
    p->f[1] = value;
    p->f[2] = 0.0f;
    p->f[3] = 1.0f;
    return index;
}
