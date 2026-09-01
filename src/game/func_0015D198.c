typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector;
typedef struct Node {
    unsigned char pad[0x10];
    float vector[4];
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
extern void func_0018A680(Vector *destination, float *source);
extern void func_00105150(Vector *value, int scale);
void func_0015D198(unsigned short index, Vector *out) {
    Vector local;
    Entry *entry;
    Node *node;
    if (index == 0xFFFF) {
        return;
    }
    entry = D_002ABA40 + index;
    if (entry->owner == 0) {
        return;
    }
    do {
        node = entry->owner->node;
        func_0018A680(&local, node->vector);
        func_00105150(&local, 0x8000);
        out->y += local.y;
        node->vector[1] = out->y;
    } while (0);
}
