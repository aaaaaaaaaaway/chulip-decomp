typedef float Vector[4] __attribute__((aligned(16)));
typedef struct Node {
    Vector unknown00, position, rotation;
} Node;
typedef struct Owner {
    unsigned char unknown00[0x10];
    Node *node;
} Owner;
typedef struct Actor {
    Vector rotation, position;
    union {
        long flags;
        struct {
            unsigned int low;
            Owner *owner;
        } link;
    } state;
    unsigned char unknown28[0x18];
} Actor;
extern Actor D_002ABA40[];
void func_0018A5F0(Vector, const float *, const float *);

void func_001566E0(unsigned short index, Vector delta) {
    Actor *actor;
    Node *node;
    if (index == 0xffff)
        return;
    actor = D_002ABA40 + index;
    if (actor->state.link.owner == 0) {
        func_0018A5F0(actor->rotation, actor->rotation, delta);
        if (actor->rotation[0] > 3.1415927f)
            actor->rotation[0] -= 6.2831855f;
        if (actor->rotation[0] < -3.1415927f)
            actor->rotation[0] += 6.2831855f;
        if (actor->rotation[1] > 3.1415927f)
            actor->rotation[1] -= 6.2831855f;
        if (actor->rotation[1] < -3.1415927f)
            actor->rotation[1] += 6.2831855f;
        if (actor->rotation[2] > 3.1415927f)
            actor->rotation[2] -= 6.2831855f;
        if (actor->rotation[2] < -3.1415927f)
            actor->rotation[2] += 6.2831855f;
    } else {
        node = actor->state.link.owner->node;
        func_0018A5F0(node->rotation, node->rotation, delta);
        if (node->rotation[0] > 3.1415927f)
            node->rotation[0] -= 6.2831855f;
        if (node->rotation[0] < -3.1415927f)
            node->rotation[0] += 6.2831855f;
        if (node->rotation[1] > 3.1415927f)
            node->rotation[1] -= 6.2831855f;
        if (node->rotation[1] < -3.1415927f)
            node->rotation[1] += 6.2831855f;
        if (node->rotation[2] > 3.1415927f)
            node->rotation[2] -= 6.2831855f;
        if (node->rotation[2] < -3.1415927f)
            node->rotation[2] += 6.2831855f;
    }
}
