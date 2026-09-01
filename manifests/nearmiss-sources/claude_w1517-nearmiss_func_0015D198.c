typedef struct Vec { float x, y, z, w; } Vec;
typedef struct Item { Vec v0; Vec v1; Vec v2; } Item;
typedef struct Node { unsigned char pad[0x10]; Item *item; } Node;
typedef union Slot { long flags; struct { int lo; Node *owner; } p; } Slot;
typedef struct Entry {
    Vec v0;
    Vec v1;
    Slot u;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_0018A680(void *dst, void *src);
void func_00105150(Vec *v, int mask);

void func_0015D198(unsigned short index, Vec *out) {
    Vec tmp;
    Node *owner;
    Item *item;

    if (index == 0xFFFF) {
        return;
    }
    owner = (D_002ABA40 + index)->u.p.owner;
    if (owner == 0) {
        return;
    }
    item = owner->item;
    func_0018A680(&tmp, &item->v1);
    func_00105150(&tmp, 0x8000);
    out->y = tmp.y + out->y;
    item->v1.y = out->y;
}
