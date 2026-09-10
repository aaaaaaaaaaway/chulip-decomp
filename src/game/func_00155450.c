typedef float Vector[4] __attribute__((aligned(16)));
typedef struct Node {
    Vector unknown00, position;
    float rotation[3];
} Node;
typedef struct Owner {
    unsigned char unknown00[0x10];
    Node *node;
} Owner;
typedef struct Actor {
    Vector unknown00, position;
    union {
        long flags;
        struct {
            unsigned int low;
            Owner *owner;
        } link;
    } state;
    unsigned char unknown28[0xE];
    unsigned short kind;
    unsigned char unknown38[8];
} Actor;
extern Actor D_002ABA40[];
extern void func_00155D08(unsigned short, unsigned short, unsigned char);
extern Owner *func_00155AB0(unsigned short);
extern void func_0018A680(Vector, const float *);
unsigned short func_00155450(unsigned short kind, unsigned short slot) {
    Vector zero = {0};
    int i;
    Node *node;
    if (slot == 0xFFFF) {
        for (i = 0x458; i < 0x480; ++i) {
            if (!((int)((D_002ABA40 + i)->state.flags >> 3) & 1))
                break;
        }
        slot = i;
    }
    if ((D_002ABA40 + slot)->state.link.owner == 0) {
        func_00155D08(kind, slot, 1);
        (D_002ABA40 + slot)->state.flags |= 4;
        (D_002ABA40 + slot)->state.flags &= ~1L;
        (D_002ABA40 + slot)->kind = kind;
        (D_002ABA40 + slot)->state.link.owner = func_00155AB0(slot);
    }
    node = (D_002ABA40 + slot)->state.link.owner->node;
    func_0018A680((D_002ABA40 + slot)->position, zero);
    func_0018A680(node->position, zero);
    node->rotation[0] = 0.0f;
    node->rotation[1] = 0.0f;
    node->rotation[2] = 0.0f;
    return slot;
}
