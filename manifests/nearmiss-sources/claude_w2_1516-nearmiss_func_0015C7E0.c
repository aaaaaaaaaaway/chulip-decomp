typedef struct Sub {
    unsigned char pad00[0x14];
    int f14;
    int f18;
    int f1C;
    unsigned char pad20[4];
    float f24;
    float f28;
    float f2C;
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
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    float f14;
    float f18;
    float f1C;
} Aux;

extern Entry D_002ABA40[];
extern Aux D_002CFA40[];

void func_0015C7E0(unsigned short index) {
    Node *owner;
    Aux *aux;
    float t;

    if (index >= 0x1C0) {
        return;
    }
    owner = D_002ABA40[index].u.p.owner;
    aux = D_002CFA40 + index;
    if (owner == 0) {
        return;
    }
    if (owner->sub == 0) {
        return;
    }
    owner->sub->f24 = aux->f14;
    owner->sub->f14 = aux->f08;
    owner->sub->f18 = aux->f04;
    owner->sub->f1C = aux->f0C;
    t = aux->f18;
    if (t == 0.0f) {
        t = 1.0f;
    }
    owner->sub->f28 = t;
    t = aux->f1C;
    if (t == 0.0f) {
        owner->sub->f2C = 0.1f;
    } else {
        owner->sub->f2C = t;
    }
}
