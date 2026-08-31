typedef struct {
    int a;
    int b;
} Pair;

extern volatile Pair D_001ED444;

int func_001500D8(void) {
    return D_001ED444.a;
}
