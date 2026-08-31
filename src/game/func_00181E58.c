typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern Pair D_001ED99C;
extern Pair D_001ED9A0;

int func_00181E58(unsigned int x, unsigned int xstep, unsigned int y, unsigned int ystep) {
    int cx = (D_001ED99C.a - x) / xstep;
    int cy = (D_001ED9A0.a - y) / ystep;

    if (cy < cx) {
        return cy;
    }
    return cx;
}
