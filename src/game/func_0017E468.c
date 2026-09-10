typedef struct {
    unsigned int key;
    int value;
} Entry;

extern unsigned int D_001ECF94;
extern Entry D_002DB100[];

void func_0017E468(unsigned int key, int value) {
    int i, j;
    for (i = 0; i < D_001ECF94; ++i) {
        if (key < D_002DB100[i].key)
            break;
    }
    if (i < D_001ECF94) {
        for (j = D_001ECF94; j > i; --j) {
            D_002DB100[j].key = D_002DB100[j - 1].key;
            D_002DB100[j].value = D_002DB100[j - 1].value;
        }
    }
    D_002DB100[i].key = key;
    D_002DB100[i].value = value;
    ++D_001ECF94;
}
