extern void func_001859D8(long *value, int *out);
extern void func_001858A8(int *out);

void func_001864E0(long value) {
    int out[8];
    long local = value;

    func_001859D8(&local, out);
    out[1] = (out[1] == 0);
    func_001858A8(out);
}
