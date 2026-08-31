typedef struct Node {
    unsigned char pad[0x14];
    float value;
} Node;

typedef struct Owner {
    unsigned char pad[0x10];
    Node *node;
} Owner;

typedef struct {
    unsigned char pad[0x14];
    float fallback;
    unsigned char pad18[0xC];
    Owner *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

void func_00156C90(unsigned short index, float value) {
    Entry *entry = D_002ABA40 + index;

    if (entry->owner == 0) {
        entry->fallback = value;
    } else {
        entry->owner->node->value = value;
    }
}
