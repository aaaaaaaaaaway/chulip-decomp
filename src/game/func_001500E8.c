typedef struct {
    int a;
    int b;
} Pair;

extern volatile Pair D_001ED440;

int func_001500E8(void) {
    return D_001ED440.a;
}
