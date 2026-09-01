extern void *func_0019BC20(void *queue);
extern void func_0019BC78(void *item);
extern void func_001986C0(void *item);

void func_0019BE40(void *queue) {
    void *item;
    for (;;) {
        item = func_0019BC20(queue);
        while (item != 0) {
            func_0019BC78(item);
            item = func_0019BC20(queue);
        }
        func_001986C0(item);
    }
}
