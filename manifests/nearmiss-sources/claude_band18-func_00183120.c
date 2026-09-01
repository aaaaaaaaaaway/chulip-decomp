typedef struct {
    int a;
    int b;
    int pad0[2];
    int c;
    int pad1[7];
} Slot;

extern Slot D_002DB708[];
extern Slot D_002DC9C8[];

void func_00183120(void) {
    int i;

    for (i = 9; i >= 0; i--) {
        D_002DB708[i].a = 0;
    }
    for (i = 0; i < 150; i++) {
        D_002DC9C8[i].a = 0;
        D_002DC9C8[i].b = 0;
        D_002DC9C8[i].c = 0;
    }
}
