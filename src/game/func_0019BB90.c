struct Item { char pad0[0x14]; struct Item *next; };
extern struct Item *D_002E28C0[];
extern int func_001A0828(void);
extern int func_001A0870(void);

struct Item *func_0019BB90(struct Item *target) {
    struct Item *item;
    func_001A0828();
    item = D_002E28C0[10];
    if (item == target) {
        D_002E28C0[10] = item->next;
    } else {
        while (item != 0) {
            if (item->next == target) {
                item->next = target->next;
                break;
            }
            item = item->next;
        }
    }
    func_001A0870();
    return item;
}
