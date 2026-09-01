struct Node {
    struct Node *next;
    int index;
};
struct Table {
    char pad[0x4C];
    struct Node **buckets;
};
void func_00196FB0(struct Table *t, struct Node *n) {
    struct Node **slot;
    int index2;
    struct Node *temp;
    if (n != 0) {
        index2 = n->index;
        n->next = (temp = *(n->index + t->buckets));
        slot = index2 + t->buckets;
        *slot = n;
    }
}
