typedef struct {
    unsigned int head;
    int f4;
    unsigned char e[512][2];
} Queue;

extern int D_002E05C0[];
extern int D_001EC0F8[];

extern int func_001987E0(int sema);
extern void func_001986D0(int arg);
extern void func_00198650(int arg);
extern void func_00198710(int arg);
extern void func_0019A740(void *fmt);

void func_001995E0(Queue *q) {
    unsigned int i;

    for (;;) {
        func_001987E0(D_002E05C0[0]);
        i = q->head & 0x1FF;
        q->head = i + 1;
        switch (q->e[i][0]) {
        case 0:
            func_001986D0(q->e[i][1]);
            break;
        case 1:
            func_00198650(q->e[i][1]);
            break;
        case 2:
            func_00198710(q->e[i][1]);
            break;
        default:
            func_0019A740(D_001EC0F8);
            break;
        }
    }
}
