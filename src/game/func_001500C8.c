typedef struct {
    int a;
    int b;
} Pair;

extern volatile Pair D_001ED43C;

int func_001500C8(void) {
    return D_001ED43C.a;
}
