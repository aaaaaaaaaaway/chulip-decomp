typedef struct {
    int a;
    int b;
} Pair;

extern volatile Pair D_001ED508;
extern int D_001ED510;
extern volatile Pair D_001ED514;
extern volatile Pair D_001ED51C;

void func_0015F1E0(void) {
    D_001ED514.a = 0;
    D_001ED514.b = 0;
    D_001ED51C.a = 0;
    D_001ED51C.b = 0;
    D_001ED508.b = 0;
    D_001ED510 = 0;
}
