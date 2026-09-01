typedef struct {
    int key;
    int value;
} Slot0017E528;

extern int D_001ECF94;
extern Slot0017E528 D_002DB100[];

void func_0017E528(int key) {
    unsigned int i;
    unsigned int n;

    n = D_001ECF94;
    i = 0;
    if (n != 0) {
        while (key != D_002DB100[i].key) {
            i++;
            if (i >= n) {
                break;
            }
        }
    }
    while (i < n - 1) {
        D_002DB100[i] = D_002DB100[i + 1];
        i++;
    }
    D_001ECF94 = D_001ECF94 - 1;
}
