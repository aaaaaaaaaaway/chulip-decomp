typedef union Quad { long long raw; float f[4]; } Quad;

typedef struct Node { unsigned char pad[0x10]; void *item; } Node;

typedef union Slot {
    long flags;
    struct { int lo; Node *owner; } p;
} Slot;

typedef struct Entry {
    unsigned char pad[0x20];
    Slot u;
    unsigned char tail[0x18];
} Entry;

typedef struct Slot40 { unsigned char b[0x40]; } Slot40;

extern Entry D_002ABA40[];
extern Slot40 D_002BDA40[];

unsigned short func_00155738(unsigned short id, unsigned short index,
                             const void *src, float value);

void func_00155648(unsigned short id, unsigned short index) {
    Quad q;

    q.raw = 0;
    if (D_002ABA40[index].u.p.owner != 0) {
        return;
    }
    func_00155738(id, index, &q, 0.0f);
    D_002BDA40[index] = D_002BDA40[id];
}
