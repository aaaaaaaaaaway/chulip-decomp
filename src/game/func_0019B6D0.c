typedef struct Node {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
    int f28;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
} Node;

extern void func_00199790(int handle);

void func_0019B6D0(Node *frame) {
    Node *node;
    Node *list;
    int v14;
    int v1c;

    node = (Node *)frame->f34;
    list = (Node *)node->f40;
    if (list->fC == 0) {
        list->fC = (int)node;
    } else {
        ((Node *)list->f10)->f3C = (int)node;
    }
    list->f10 = (int)node;
    v14 = frame->f14;
    v1c = frame->f1C;
    node->f20 = v14;
    node->f1C = v1c;
    node->f24 = frame->f20;
    node->fC = frame->f24;
    node->f28 = frame->f28;
    node->f2C = frame->f2C;
    node->f30 = frame->f30;
    node->f34 = frame->f10;
    if (list->f0 >= 0) {
        if (list->f4 == 0) {
            func_00199790(list->f0);
        }
    }
}
