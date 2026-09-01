typedef struct Src {
    unsigned char pad[0x2C];
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
    unsigned char pad[0x1C];
    float f1C;
} Dst;

extern Entry D_002ABA40[];
extern Dst D_002CFA40[];

void func_00158558(unsigned short index, float value) {
    if (index < 0x1C0) {
        Dst *dst = D_002CFA40 + index;
        Node *owner = (D_002ABA40 + index)->owner;

        if (owner != 0 && owner->src != 0) {
            owner->src->f2C = value;
        }
        dst->f1C = value;
    }
}
