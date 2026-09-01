typedef struct Node {
    char pad0[0x10];
    int flags;
    char pad14[4];
    int key;
} Node;

typedef struct Handle {
    Node *node;
    int key;
} Handle;

int func_0019B950(Handle *handle) {
    Node *node;

    node = handle->node;
    if (node != 0 && handle->key == node->key && (node->flags & 1) != 0) {
        return 1;
    }
    return 0;
}
