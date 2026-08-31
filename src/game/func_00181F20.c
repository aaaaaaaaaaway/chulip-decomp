typedef struct {
    int a;
    int b;
} Pair;

extern Pair D_001ED9A0;
extern Pair D_001ED9A4;
extern int D_001ED9A8;
extern int func_00181E30(int dx, int dy);

int func_00181F20(int delta) {
    int previous = D_001ED9A8;

    if (delta != 0) {
        func_00181E30(0, delta);
        D_001ED9A0.a -= delta;
        D_001ED9A4.b += delta;
    }
    return previous;
}
