typedef struct Src {
    unsigned char pad[0x28];
    float f28;
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
    unsigned char pad[0x18];
    float f18;
    unsigned char tail[0x4];
} Dst;

extern Entry D_002ABA40[];
extern Dst D_002CFA40[];

float func_00158478(unsigned short index) {
    Dst *dst;
    Node *owner;

    if (index >= 0x1C0) {
        return 0.0f;
    }
    dst = D_002CFA40 + index;
    owner = (D_002ABA40 + index)->owner;
    if (owner == 0) {
        return dst->f18;
    }
    if (owner->src != 0) {
        return owner->src->f28;
    }
    return 0.0f;
}
