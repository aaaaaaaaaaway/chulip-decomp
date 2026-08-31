typedef struct {
    int a;
    int b;
} Pair;

extern Pair D_001ED99C;
extern Pair D_001ED9A0;
extern int D_001ED9A4;
extern int func_00181E30(int dx, int dy);

int func_00181EB8(int delta) {
    int previous = D_001ED9A4;

    if (delta != 0) {
        func_00181E30(delta, 0);
        D_001ED99C.a -= delta;
        D_001ED9A0.b += delta;
    }
    return previous;
}
