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
    unsigned char unknown38[3];
    unsigned char state3B;
    unsigned char unknown3C[4];
} Actor;
extern Actor D_002ABA40[];
typedef struct Control {
    long flags;
} Control;
extern Control *func_00136AE8(void);
extern unsigned short D_002AAF00[];
extern void func_0015A4E0(int);
extern void func_00155920(unsigned short);
extern void func_00198A20(int);
int func_0015A370(int first, unsigned int count) {
    int index;
    unsigned int removed = 0;
    Control *control = func_00136AE8();
    int release_owner = (int)(control->flags >> 3) & 1;
    for (index = first; D_002AAF00[index] != 0xFFFF && index < 0x1E0;) {
        unsigned short actor = D_002AAF00[index];
        if (!((int)((D_002ABA40 + actor)->state.flags >> 2) & 1)) {
            if (release_owner && (D_002ABA40 + actor)->state.link.owner != 0)
                func_0015A4E0(actor);
            func_00155920(actor);
            ++removed;
        }
        D_002AAF00[index++] = 0xFFFF;
        if (removed >= count)
            return index;
    }
    if (release_owner)
        control->flags &= ~8L;
    func_00198A20(0);
    return 0;
}
