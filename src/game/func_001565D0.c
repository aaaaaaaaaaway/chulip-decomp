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
void func_001565D0(unsigned short index, float delta) {
    Entry *e;
    Item *item;
    float a, b;

    if (index == 0xFFFF) return;
    e = D_002ABA40 + index;
    if (e->u.p.owner == 0) {
        a = e->f[1];
        a = a + delta;
        if (a > 3.1415927f) a -= 6.2831855f;
        if (a < -3.1415927f) a += 6.2831855f;
        e->f[1] = a;
        return;
    }
    item = e->u.p.owner->item;
    b = item->v[1];
    b = b + delta;
    if (b > 3.1415927f) b -= 6.2831855f;
    if (b < -3.1415927f) b += 6.2831855f;
    item->v[1] = b;
    e->f[1] = b;
}
