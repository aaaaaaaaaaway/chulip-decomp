typedef struct {
    unsigned int start;
    int end;
} Entry;
extern unsigned int D_001ECF94;
extern Entry D_002DB100[];

void func_0017E528(unsigned int start) {
    int i, j;
    for (i = 0; i < D_001ECF94; ++i) {
        if (start == D_002DB100[i].start)
            break;
    }
    for (j = i; j < D_001ECF94 - 1; ++j) {
        D_002DB100[j].start = D_002DB100[j + 1].start;
        D_002DB100[j].end = D_002DB100[j + 1].end;
    }
    --D_001ECF94;
}
