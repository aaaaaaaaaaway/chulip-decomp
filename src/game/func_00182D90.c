typedef struct {
    int a;
    int b;
} Pair;

extern Pair D_001ED9D0;
extern int D_001ED9C4;
extern int D_001ED9C8;

void func_00182D90(int mode) {
    D_001ED9D0.a = 0x168;
    D_001ED9C4 = mode;
    switch (mode) {
    case 1:
        D_001ED9C8 = mode;
        break;
    case 2:
        D_001ED9C8 = -1;
        break;
    }
}
