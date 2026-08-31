typedef struct {
    int a;
    int b;
} Pair;

extern volatile Pair D_001ED9C4;
extern volatile Pair D_001ED9C8;
extern volatile Pair D_001ED9D0;
extern int D_001ED9CC;
extern void func_00182F00(void);
extern void func_00183178(void);

void func_00182DD0(void) {
    int total = D_001ED9C8.b + D_001ED9C8.a;
    int limit = D_001ED9D0.a;
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
