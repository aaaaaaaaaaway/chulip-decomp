typedef struct Item { unsigned char pad[0x10]; } Item;

typedef struct Node {
    unsigned char pad[0x10];
    Item *item;
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
void func_00133540(Item *item, const float *v, int mode);

void func_0015C8B0(unsigned short index, float angle) {
    Node *owner;
    float v[3];
    int mode;

    mode = func_0015CA60(index, 2);
    owner = D_002ABA40[index].u.p.owner;
    if (owner == 0) {
        return;
    }
    if (angle > 3.1415927f) {
        angle -= 6.2831855f;
    }
    if (angle < -3.1415927f) {
        angle += 6.2831855f;
    }
    v[0] = angle;
    v[1] = -1.0f;
    v[2] = -1.0f;
    func_00133540(owner->item, v, mode);
}
