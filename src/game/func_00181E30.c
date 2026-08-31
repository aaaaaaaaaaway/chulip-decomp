typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern Pair D_001ED99C;
extern unsigned int D_001ED9A0;

int func_00181E30(unsigned int x, unsigned int y) {
    if (D_001ED99C.a < x) {
        return 1;
    }
    return D_001ED9A0 < y;
}
