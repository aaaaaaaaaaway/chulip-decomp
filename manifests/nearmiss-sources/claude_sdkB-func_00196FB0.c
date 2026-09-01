struct Node { struct Node *next; int index; };
struct Table { char pad[0x4C]; struct Node **buckets; };

void func_00196FB0(struct Table *t, struct Node *n) {
    struct Node **slot;
    if (n != 0) {
        slot = n->index + t->buckets;
        n->next = *slot;
        *slot = n;
    }
}
