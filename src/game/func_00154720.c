typedef struct Node {
    unsigned char pad[0x24];
    float value;
} Node;

typedef struct Owner {
    unsigned char pad[0x10];
    Node *node;
} Owner;

typedef struct {
    unsigned char pad[0x4];
    float fallback;
    unsigned char pad8[0x1C];
    Owner *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];

float func_00154720(unsigned short index) {
    Entry *entry = D_002ABA40 + index;

    if (entry->owner == 0) {
        return entry->fallback;
    }
    return entry->owner->node->value;
}
