extern void func_001866B0(float *value, int *out);
extern void func_001865A0(int *out);
extern void func_001865A0(int *args);

void func_001870D8(float value) {
    int out[4];
    float local = value;
    func_001866B0(&local, out);
    out[1] = (out[1] == 0);
    func_001865A0(out);
}

void func_00187110(int a, int b, int c, int d) {
    int args[4];
    args[0] = a;
    args[1] = b;
    args[2] = c;
    args[3] = d;
    func_001865A0(args);
}
