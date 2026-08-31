typedef struct {
    int a;
    int b;
} Pair;

extern Pair D_001ED9C4;
extern void func_00182DD0(int arg);
extern int func_00183610(int arg);

int func_00182E58(int arg) {
    int mode;
    int result;

    func_00182DD0(arg);
    mode = D_001ED9C4.a;
    result = 0;
    if (mode < 3) {
        if (mode > 0) {
            result = func_00183610(arg);
        }
    }
    return result;
}
