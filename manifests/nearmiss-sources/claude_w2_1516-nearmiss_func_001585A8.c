typedef struct Sub {
    unsigned char pad[0x18];
    int flags;
} Sub;

typedef struct Node {
    unsigned char pad[0x14];
    Sub *sub;
} Node;

typedef union Slot {
    long flags;
    struct { int lo; Node *owner; } p;
} Slot;

typedef struct Entry {
    unsigned char pad[0x20];
    Slot u;
    unsigned char tail[0x18];
} Entry;

typedef struct Aux {
    int unknown_00;
    int flags;
    unsigned char tail[0x18];
} Aux;

extern Entry D_002ABA40[];
extern Aux D_002CFA40[];
void func_001585A8(unsigned short index, unsigned short mask, unsigned char set) {
    Node *owner;
    Aux *aux;
    Sub *sub;
    if (index >= 0x1C0) return;
    owner = D_002ABA40[index].u.p.owner;
    aux = D_002CFA40 + index;
    if (owner == 0) {
        if (set != 0) aux->flags |= mask;
        else aux->flags &= ~mask;
        return;
    }
    sub = owner->sub;
    if (sub == 0) return;
    if (set != 0) { sub->flags |= mask; aux->flags |= mask; }
    else { sub->flags &= ~mask; aux->flags &= ~mask; }
}
