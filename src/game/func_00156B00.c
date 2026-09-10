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
void func_00156B00(unsigned short index, unsigned char which, float value) {
    Item *item;
    if (index == 0xFFFF) return;
    if (D_002ABA40[index].u.p.owner == 0) {
        D_002ABA40[index].f[which] = value;
        return;
    }
    item = D_002ABA40[index].u.p.owner->item;
    item->v[which] = value;
    item->f2C = 1.0f;
    D_002ABA40[index].f[which] = value;
}
