typedef struct Vec4 { float x, y, z, w; } Vec4;

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
    float f[4];
    unsigned char q10[0x10];
    Slot u;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_0018A680(void *dst, const void *src);
int func_00172FE8(int id);
void func_00101330(Vec4 *v, int mode);

void func_00156BC8(unsigned short index, Vec4 *v) {
    Node *owner;
    Item *item;

    if (index == 0xFFFF) return;
    owner = D_002ABA40[index].u.p.owner;
    if (owner == 0) {
        func_0018A680(&D_002ABA40[index].q10, v);
        return;
    }
    item = owner->item;
    v->w = 1.0f;
    func_0018A680(&item->q10, v);
    func_0018A680(&D_002ABA40[index].q10, v);
    if (index != 0) return;
    if (func_00172FE8(4) & 1) return;
    func_00101330(v, 1);
}
