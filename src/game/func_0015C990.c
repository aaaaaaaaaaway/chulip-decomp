typedef struct Node {
    unsigned char pad[0x10];
    void *item;
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

int func_0015CA60(unsigned short index, int mode);
float func_001335A0(void *item, int value);

float func_0015C990(unsigned short index) {
    Node *n = D_002ABA40[index].u.p.owner;

    if (n == 0) {
        return 0.0f;
    }
    return func_001335A0(n->item, func_0015CA60(index, 2));
}
