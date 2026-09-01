extern int D_001E5334[];
extern int D_002E3C28[];
extern int D_001E5B90[];
extern int func_001922B0(int *a, int *b, int size);

int func_0019C6B0(void) {
    int *self;
    int *other;
    int result;

    self = D_001E5334;
    other = D_002E3C28;
    result = 0;
    if (func_001922B0(other, self, 4) != 0) {
        if (func_001922B0(other, (int *)D_001E5B90[0], 4) != 0) {
            result = func_001922B0(self, (int *)D_001E5B90[0], 4) != 0;
        }
    }
    return result;
}
