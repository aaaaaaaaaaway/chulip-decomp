struct Item { int f0; int f4; int f8; int fC; int f10; int next; };
extern int D_002E28C0[];
extern int func_001A0828(void);
extern void func_001A0870(void);

void func_0019B990(struct Item *node, int value) {
    struct Item *item;
    func_001A0828();
    node->f0 = value;
    node->f4 = 0;
    node->f8 = 0;
    node->fC = 0;
    node->f10 = 0;
    node->next = 0;
    item = (struct Item *)D_002E28C0[10];
    if (item == 0) {
        D_002E28C0[10] = (int)node;
    } else {
        while (item->next != 0) {
            item = (struct Item *)item->next;
        }
        item->next = (int)node;
    }
    func_001A0870();
}
