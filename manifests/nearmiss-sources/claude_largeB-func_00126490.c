extern short D_001ED2BC;
extern short D_001ED2BE;
extern short D_001ED2C0;
extern short D_001ED2C2;
extern short D_001ED2C4;
extern short D_001ED2CA;
extern short D_001ED2CC;
extern unsigned int D_001ED270;

typedef struct {
    char pad0[0xC];
    int flag;
    char pad1[8];
} Item;

extern Item D_001FC450[];

void func_00126490(void) {
    unsigned int i;
    short d;

    D_001ED2BC = (D_001ED2BC + 1) % 360;
    D_001ED2BE = (D_001ED2BE + 1) % 360;
    d = D_001ED2C0;
    D_001ED2C2 = (D_001ED2C2 + d) % 360;
    if (D_001ED2C4 < D_001ED2C2) {
        D_001ED2C2 = D_001ED2C4;
        D_001ED2C0 = -d;
    } else if (D_001ED2C2 < -D_001ED2C4) {
        D_001ED2C2 = -D_001ED2C4;
        D_001ED2C0 = -d;
    }
    if (D_001ED2CC < D_001ED2CA) {
        D_001ED2CC = D_001ED2CC + 1;
    }
    for (i = 0; i < D_001ED270; i++) {
        D_001FC450[i].flag = 0;
    }
}
