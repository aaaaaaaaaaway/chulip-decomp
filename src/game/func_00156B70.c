typedef struct Node {
    unsigned char pad[0x20];
    float field[4];
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
extern void func_0018A680(void *target, const void *source);

void func_00156B70(unsigned short index, const void *source) {
    Entry *entry;

    if (index == 0xFFFF) {
        return;
    }
    entry = D_002ABA40 + index;
    if (entry->owner == 0) {
        func_0018A680(entry, source);
    } else {
        func_0018A680(&entry->owner->node->field, source);
    }
}
