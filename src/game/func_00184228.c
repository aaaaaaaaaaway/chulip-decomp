typedef struct {
    int a;
    int b;
} Pair;

extern Pair D_001ED9D0;
extern Pair D_001ED9D8;
extern Pair D_001ED9E0;
extern int D_001ED9D4;
extern int D_001ED9DC;
extern void func_001843E0(int arg, int frame, int b, int c);

void func_00184228(int arg) {
    int total = D_001ED9D8.b + D_001ED9E0.a;
    int frame;

    D_001ED9DC = total;
    if (total < 0) {
        goto reset;
    }
    if (total < 6) {
        frame = D_001ED9D4;
        goto ready;
    }
reset:
    D_001ED9E0.a = 0;
    frame = D_001ED9D0.b;
ready:
    func_001843E0(arg, frame, D_001ED9D8.a, D_001ED9DC);
}
