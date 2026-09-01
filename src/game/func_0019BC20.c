typedef struct QueueNode {
    char padding[0x3C];
    struct QueueNode *next;
} QueueNode;

typedef struct {
    int field_0;
    int active;
    int field_8;
    QueueNode *head;
} Queue;

extern void func_001A0828(void);
extern void func_001A0870(void);

QueueNode *func_0019BC20(Queue *queue) {
    QueueNode *node;

    func_001A0828();
    node = queue->head;
    if (node == 0) {
        queue->active = 0;
    } else {
        queue->active = 1;
        queue->head = node->next;
    }
    func_001A0870();
    return node;
}
