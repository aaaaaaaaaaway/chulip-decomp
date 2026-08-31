typedef struct {
    int a;
    int b;
} Pair;

extern volatile Pair D_001ED438;
extern volatile Pair D_001ED44C;
extern volatile Pair D_001ED450;
extern volatile Pair D_001ED454;

void func_00150050(int arg0, int arg1, int arg2) {
    if (D_001ED438.a == 0) {
        D_001ED44C.a = arg0;
        D_001ED450.a = arg2;
        D_001ED438.b = 0;
        D_001ED454.a = arg1;
        D_001ED438.a = 1;
    }
}
