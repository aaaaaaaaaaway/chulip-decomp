typedef struct Node {
    unsigned char pad[0x24];
    float value;
} Node;

typedef struct Owner {
    unsigned char pad[0x10];
    Node *node;
} Owner;

typedef struct {
    unsigned char pad[0x24];
    Owner *owner;
    unsigned char tail[0x18];
} Entry;

extern Entry D_002ABA40[];
extern float func_00158698(unsigned short index, unsigned short other);

float func_00158750(unsigned short index, unsigned short other) {
    Entry *entry;
    Node *node;

    if (index == 0xFFFF) {
        return 0.0f;
    }
    entry = D_002ABA40 + index;
    if (entry->owner == 0) {
        return 0.0f;
    }
    node = entry->owner->node;
    if (node == 0) {
        return 0.0f;
    }
    return node->value = func_00158698(index, other);
}
