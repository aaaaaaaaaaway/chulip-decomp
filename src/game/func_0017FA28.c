extern int D_001ECFA8;

int func_0017F9B8();
int func_0017F9F0();
int func_0017FA28(int arg0, int limit, int next);

int func_0017FA28(int arg0, int limit, int next) {
    if (D_001ECFA8 >= limit) {
        D_001ECFA8 = 0;
        func_0017F9F0(func_0017FA28);
        if (next != 0) {
            func_0017F9B8(next, limit, 0);
        }
    } else {
        D_001ECFA8 = D_001ECFA8 + 1;
    }
    return 0;
}
