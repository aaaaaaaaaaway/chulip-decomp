typedef struct {
    long flags;
    char pad0[0x66];
    unsigned short f6E;
    char pad1[0x28];
    unsigned short f98;
    char pad2[0x26];
} Ent;

typedef struct {
    char pad[0x10];
    unsigned short count;
} Tbl;

extern Tbl D_002D8840;
extern Ent *D_001ED6C0;

int func_001711A0(int i);
int func_00170C40(unsigned short i, float a);

int func_00171D10(void) {
    int i;
    int best;
    int bestd;
    int d;

    best = -1;
    bestd = 0x384;
    for (i = 1; i < (int)D_002D8840.count; i++) {
        d = func_001711A0(i);
        if (d > 0 && d < bestd) {
            if ((D_001ED6C0[i].f98 & 8) != 0
                && (D_001ED6C0[i].flags & 0x100004000L) == 0
                && func_00170C40((unsigned short)i, 1.5707963705062866f) != 0) {
                bestd = d;
                best = i;
            }
        }
    }
    if (best == -1) {
        return -1;
    }
    return D_001ED6C0[best].f6E;
}
