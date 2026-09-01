typedef struct Src {
    unsigned char pad[0x1C];
    int value;
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
    unsigned char pad[0xC];
    int value;
    unsigned char tail[0x10];
} Dst;

extern Entry D_002ABA40[];
extern Dst D_002CFA40[];

int func_00154398(unsigned short index);

int func_0015BBA0(unsigned short index, int value) {
    Node *owner;
    Src *src;

    if (index == 0xFFFF) {
        return 0;
    }
    if (func_00154398(index) == 0 && index < 0x1C0) {
        return (D_002CFA40 + index)->value == value;
    }
    owner = (D_002ABA40 + index)->owner;
    if (owner == 0) {
        return 0;
    }
    src = owner->src;
    if (src == 0) {
        return 0;
    }
    return src->value == value;
}
