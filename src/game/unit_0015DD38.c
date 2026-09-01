typedef struct {
    int a;
    int b;
} Pair;

extern int D_001ED4A0;

extern int D_001ED4A4;

void func_0015DD38(int value) {
    D_001ED4A0 = value;
    D_001ED4A4 = value;
}

int func_0015DD48(void) {
    D_001ED4A4 += D_001ED4A4 + D_001ED4A0 + 1;
    return D_001ED4A4;
}
