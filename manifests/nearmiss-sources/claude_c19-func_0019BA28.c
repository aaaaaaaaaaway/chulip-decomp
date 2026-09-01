typedef struct Node {
    int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C;
    int f20; int f24; int f28; int f2C; int f30; int f34;
    struct Node *next;
    int f3C;
    void *owner;
} Node;
typedef struct Head {
    int h0; int h4; Node *first;
} Head;

extern void func_001A0828(void);
extern void func_001A0870(void);

void func_0019BA28(Node *p, int a1, int a2, int a3, int t0, int t1, Head *h) {
    Node *q;
    Node *n;

    func_001A0828();
    p->f3C = 0;
    p->next = 0;
    p->f0 = a1;
    p->f4 = a2;
    p->f8 = a3;
    p->f10 = t0;
    p->f14 = t1;
    p->owner = h;
    q = h->first;
    if (q == 0) {
        h->first = p;
    } else {
        n = q->next;
        while (n != 0) {
            q = n;
            n = q->next;
        }
        q->next = p;
    }
    func_001A0870();
}
