typedef struct Src {
    unsigned char pad[0x14];
    int f14;
    int f18;
    int f1C;
    int f20;
    float f24;
    float f28;
    float f2C;
} Src;

typedef struct Node {
    unsigned char pad[0x14];
    Src *src;
} Node;

typedef struct Entry {
    unsigned char pad[0x24];
    Node *owner;
    unsigned char tail[0x18];
} Entry;

typedef struct Dst {
    int f0;
    int f4;
    int f8;
    int fC;
    float f10;
    float f14;
    float f18;
    float f1C;
} Dst;

extern Entry D_002ABA40[];
extern Dst D_002CFA40[];

void func_0015C750(unsigned short index) {
    if (index < 0x1C0) {
        Node *owner = (D_002ABA40 + index)->owner;
        Dst *dst = D_002CFA40 + index;

        if (owner != 0 && owner->src != 0) {
            dst->f14 = owner->src->f24;
            dst->f8 = owner->src->f14;
            dst->f4 = owner->src->f18;
            dst->fC = owner->src->f1C;
            dst->f18 = owner->src->f28;
            dst->f1C = owner->src->f2C;
        }
    }
}
