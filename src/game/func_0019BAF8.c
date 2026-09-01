typedef struct Node {
    char pad0[0x38];
    struct Node *next;
} Node;

typedef struct {
    int unk0;
    int unk4;
    Node *head;
} List;

extern void func_001A0828(void);
extern void func_001A0870(void);

Node *func_0019BAF8(Node *node, List *list) {
    Node *p;

    func_001A0828();
    p = list->head;
    if (p == node) {
        list->head = node->next;
    } else {
        while (p != 0) {
            if (p->next == node) {
                p->next = node->next;
                break;
            }
            p = p->next;
        }
    }
    func_001A0870();
    return p;
}
