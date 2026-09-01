int func_0014D920();
int func_0014E0B8();
int func_001547A8();

void func_00177F50(unsigned short id, int x, int arg2) {
    int step;
    int n;
    int hi;
    int lo;
    step = func_0014D920();
    n = (char)func_001547A8(id);
    func_0014E0B8(x, arg2, 1);
    if (n > 0) {
        hi = x + n * step;
        func_0014E0B8(hi + n, arg2, 1);
        lo = x - n * step;
        func_0014E0B8(lo + n, arg2, 1);
        func_0014E0B8(hi - n, arg2, 1);
        func_0014E0B8(lo - n, arg2, 1);
    }
}

void func_00178010(unsigned short id, int x, int arg2) {
    int step;
    int n;
    int hi;
    int lo;
    step = func_0014D920();
    n = (char)func_001547A8(id);
    func_0014E0B8(x, arg2, 0);
    if (n > 0) {
        hi = x + n * step;
        func_0014E0B8(hi + n, arg2, 0);
        lo = x - n * step;
        func_0014E0B8(lo + n, arg2, 0);
        func_0014E0B8(hi - n, arg2, 0);
        func_0014E0B8(lo - n, arg2, 0);
    }
}
