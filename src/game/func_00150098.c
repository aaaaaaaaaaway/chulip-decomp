typedef struct {
    int a;
    int b;
} Pair;

extern volatile Pair D_001ED438;

void func_00150098(void) {
    if (D_001ED438.a == 0) {
        D_001ED438.b = 0;
        D_001ED438.a = 3;
    }
}
