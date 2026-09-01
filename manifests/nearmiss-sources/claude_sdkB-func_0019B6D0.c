struct Ctx;
struct List { int f0; int f4; int f8; struct Ctx *head; struct Ctx *tail; };
struct Ctx { int f0; int f4; int f8; int fC; int f10; int f14; int f18; int f1C;
             int f20; int f24; int f28; int f2C; int f30; int f34; int f38;
             struct Ctx *next; struct List *list; };
extern void func_00199790(int handle);

void func_0019B6D0(struct Ctx *frame) {
    struct Ctx *node = (struct Ctx *)frame->f34;
    struct List *list = node->list;
    if (list->head == 0) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    node->f20 = frame->f14;
    node->f1C = frame->f1C;
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
