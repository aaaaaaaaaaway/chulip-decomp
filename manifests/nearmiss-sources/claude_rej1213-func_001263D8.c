struct Node_001263D8 { struct Node_001263D8 *next; unsigned short id; };

extern struct Node_001263D8 *D_001FC350[];

struct Node_001263D8 *func_001263D8(unsigned short key) {
    struct Node_001263D8 *node = 0;
    struct Node_001263D8 *entry;
    int hash = (key >> 8) + (key & 0xFF);

    for (entry = D_001FC350[hash % 0x40]; entry != 0; entry = entry->next) {
        if (entry->id == key) {
            node = entry;
            break;
        }
    }
    return node;
}
