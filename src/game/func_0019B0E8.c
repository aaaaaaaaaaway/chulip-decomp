struct Slot { int f0; int f4; int f8; int fC; int flags; struct Slot *self; int id; char pad[0x24]; };
struct Pool { int counter; struct Slot *slots; int count; };
extern int func_001A0828(void);
extern int func_001A0870(void);

struct Slot *func_0019B0E8(struct Pool *pool) {
    struct Slot *slot;
    int i;
    func_001A0828();
    slot = pool->slots;
    for (i = 0; i < pool->count; i++) {
        if ((slot->flags & 1) == 0) {
            int id;
            slot->flags = (i << 16) | 5;
            pool->counter = pool->counter + 1;
            if (pool->counter == 1) {
                pool->counter = pool->counter + 1;
                id = 1;
            } else {
                id = pool->counter;
            }
            slot->self = slot;
            slot->id = id;
            func_001A0870();
            return slot;
        }
        slot++;
    }
    func_001A0870();
    return 0;
}
