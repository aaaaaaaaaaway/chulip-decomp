typedef void (*Func)(void);
extern Func D_001ED9E8[];

void func_00185648(void) {
    int n;
    int i;

    n = (int)D_001ED9E8[0];
    if (n == -1) {
        if (D_001ED9E8[1] == 0) {
            n = 0;
        } else {
            n = 1;
            while (D_001ED9E8[n + 1] != 0) {
                n = n + 1;
            }
        }
    }
    i = n;
    while (i != 0) {
        D_001ED9E8[i]();
        i--;
    }
}
