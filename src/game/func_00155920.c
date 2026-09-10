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
extern void func_0015C750(unsigned short);
extern void func_0015A4E0(int);
extern void func_00151878(unsigned short);
extern void func_00151858(unsigned short, int);
void func_00155920(unsigned short index) {
    int active = (int)((D_002ABA40 + index)->state.flags >> 3) & 1;
    if (active != 1)
        return;
    if (index < 0x1C0)
        func_0015C750(index);
    func_0015A4E0(index);
    (D_002ABA40 + index)->state.flags &= ~1L;
    (D_002ABA40 + index)->state.flags &= ~4L;
    (D_002ABA40 + index)->state.flags &= ~0x10L;
    (D_002ABA40 + index)->state.flags &= ~0x20L;
    (D_002ABA40 + index)->state.flags &= ~0x8000L;
    (D_002ABA40 + index)->state.flags &= ~0x4000L;
    (D_002ABA40 + index)->state.flags &= ~0x2000L;
    (D_002ABA40 + index)->state.flags &= ~0x40L;
    (D_002ABA40 + index)->state.flags &= ~0x100L;
    (D_002ABA40 + index)->state.flags &= ~0x1000L;
    (D_002ABA40 + index)->state.flags &= ~0x10000L;
    (D_002ABA40 + index)->state3B = 0xFF;
    if ((int)((D_002ABA40 + index)->state.flags >> 11) & 1) {
        func_00151878(index);
        (D_002ABA40 + index)->state.flags &= ~0x800L;
    } else if (!((int)((D_002ABA40 + index)->state.flags >> 9) & 1)) {
        func_00151858(index, 0);
    }
    if (!((int)((D_002ABA40 + index)->state.flags >> 9) & 1)) {
        (D_002ABA40 + index)->state.flags &= ~8L;
        (D_002ABA40 + index)->kind = 0xFFFF;
    }
    (D_002ABA40 + index)->state.flags &= ~0x400L;
}
