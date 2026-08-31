struct Actor_00128A50 { long flags; };

extern struct Actor_00128A50 *func_00136AE8(void);
extern void func_001733A8(int arg0, int arg1);

void func_00128A50(unsigned char enable) {
    struct Actor_00128A50 *actor = func_00136AE8();

    if (enable != 0) {
        actor->flags = actor->flags | 0x80L;
        func_001733A8(1, 1);
    } else {
        actor->flags = actor->flags & ~0x80L;
        func_001733A8(1, 0);
    }
}
