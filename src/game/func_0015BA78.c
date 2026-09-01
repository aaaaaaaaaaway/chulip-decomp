typedef struct Quad { unsigned char b[0x10]; } Quad;

typedef struct Node {
    unsigned char pad[0x10];
    Quad *quads;
} Node;

typedef struct Entry {
    Quad quads[2];
    int pad20;
    Node *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_0018A680(Quad *dst, Quad *src);

void func_0015BA78(unsigned short index) {
    Node *owner = (D_002ABA40 + index)->owner;

    if (owner != 0) {
        Quad *quads = owner->quads;

        func_0018A680(&D_002ABA40[index].quads[1], &quads[1]);
        func_0018A680(&(D_002ABA40 + index)->quads[0], &quads[2]);
    }
}
