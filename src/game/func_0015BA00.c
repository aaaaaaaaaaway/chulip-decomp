typedef struct Quad { unsigned char b[0x10]; } Quad;
typedef struct Node { unsigned char pad[0x10]; Quad *quads; } Node;
typedef struct Entry { Quad quads[2]; int pad20; Node *owner; unsigned char tail[0x18]; } Entry;
typedef union Vec4 { long long raw; float f[4]; } Vec4;
extern Entry D_002ABA40[];
void func_0018A680(Quad *dst, Quad *src);

void func_0015BA00(unsigned short index) {
    Vec4 unit;

    unit.raw = 0;
    unit.f[3] = 1.0f;
    if (index != 0xFFFF) {
        Node *owner = (D_002ABA40 + index)->owner;

        if (owner != 0) {
            Quad *quads = &owner->quads[1];

            func_0018A680(&D_002ABA40[index].quads[1], quads);
            func_0018A680(quads, (Quad *)&unit);
        }
    }
}
