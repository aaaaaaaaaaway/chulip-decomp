typedef struct {
    int a;
    int b;
} Pair;

extern Pair D_001ED9C4;
extern Pair D_001ED9C8;
extern Pair D_001ED9D0;
extern int D_001ED9CC;
extern void func_00182F00(void);
extern void func_00183178(void);

void func_00182DD0(void) {
    int carry = D_001ED9C8.b;
    int step = D_001ED9C4.b;
    int limit = D_001ED9D0.a;
    int total = carry + step;
    int mode;

    D_001ED9CC = total;
    if (limit < total) {
        D_001ED9CC = limit;
    } else if (total < 0) {
        D_001ED9C8.b = 0;
        D_001ED9C4.a = 0;
    }
    func_00182F00();
    mode = D_001ED9C4.a;
    if (mode < 3) {
        if (mode > 0) {
            func_00183178();
        }
    }
}
