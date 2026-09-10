typedef struct Node {
    int unknown_00;
    struct Node *f04;
    void *f08;
    void *f0C;
    void *f10;
    void *f14;
    void *f18;
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

extern Entry D_002ABA40[];

void func_001518C0(int index);
int func_00151CA8(void *ptr);

void func_0015A4E0(int index) {
    Entry *e = D_002ABA40 + index;
    Node *n = e->u.p.owner;

    if (n == 0) {
        return;
    }
    func_001518C0(index);
    if (n->f04 != 0) {
        func_00151CA8(n->f04->f04);
        func_00151CA8(n->f04);
        n->f04->f04 = 0;
        n->f04 = 0;
    }
    if (n->f0C != 0) { func_00151CA8(n->f0C); n->f0C = 0; }
    if (n->f08 != 0) { func_00151CA8(n->f08); n->f08 = 0; }
    if (n->f10 != 0) { func_00151CA8(n->f10); n->f10 = 0; }
    if (n->f14 != 0) { func_00151CA8(n->f14); n->f14 = 0; }
    if (n->f18 != 0) { func_00151CA8(n->f18); n->f18 = 0; }
    func_00151CA8(n);
    e->u.p.owner = 0;
}
