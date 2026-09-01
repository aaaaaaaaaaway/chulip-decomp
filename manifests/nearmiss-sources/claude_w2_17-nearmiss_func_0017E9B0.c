typedef struct {
    int key;
    int value;
} Slot0017E9B0;

extern int D_001ECF94;
extern Slot0017E9B0 D_002DB100[];

int func_0017E528();

int func_0017E9B0(int key) {
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
        if (i < n) {
            func_0017E528(key);
        }
    }
    return 0;
}
