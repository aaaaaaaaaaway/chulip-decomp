typedef struct {
    int a;
    int b;
    int c;
    long d;
} Packed;

extern void func_001859D8(long *value, int *out);

extern void func_001858A8(void *out);

void func_001864E0(long value) {
    int out[8];
    long local = value;

    func_001859D8(&local, out);
    out[1] = (out[1] == 0);
    func_001858A8(out);
}

void func_00186518(int a, int b, int c, long d) {
    Packed args;

    args.a = a;
    args.b = b;
    args.c = c;
    args.d = d;
    func_001858A8(&args);
}
